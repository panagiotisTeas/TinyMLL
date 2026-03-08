#include "core/arena.h"

#include <stdlib.h>

b8 
tinymll_create_arena(u64 size, Arena** arena_out, Error** error)
{
    if (size == 0)
    {
        tinymll_set_error(
            error,
            TINYMLL_ALLOCATION_ZERO_SIZE,
            "Trying to allocate a zero memory block."
        );
        return TINYMLL_FALSE;
    }

    u64 reserved_size = (size + PAGE_SIZE - 1) / PAGE_SIZE * PAGE_SIZE;

    Arena* arena = (Arena*)tinymll_clib_malloc(sizeof(Arena), error);
    if (arena == NULL)
    {
        tinymll_set_error(
            error,
            TINYMLL_ALLOCATION_FAILED,
            "`malloc` failed to allocate memory."
        );
        return TINYMLL_FALSE;
    }

    #if defined(__linux__) || defined(__APPLE__)
    void* memory_ptr = mmap(NULL, reserved_size, PROT_NONE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    if (memory_ptr == MAP_FAILED)
    {
        tinymll_set_error(
            error,
            TINYMLL_ALLOCATION_FAILED,
            "`mmap` failed to allocate memory."
        );
        tinymll_clib_free(arena, NULL);
        return TINYMLL_FALSE;
    }

    #elif defined(_WIN32)
    //TODO malloc is used
    void* memory_ptr = tinymll_clib_malloc(reserved_size, error);
    if (memory_ptr == NULL)
    {
        tinymll_clib_free(arena, NULL);
        return TINYMLL_FALSE;
    }

    #endif

    arena->memory_ptr       = (u8*)memory_ptr;
    arena->reserved_size    = reserved_size;
    arena->commited_size    = 0;
    arena->offset           = 0;

    *arena_out = arena;
    return TINYMLL_TRUE;
}

b8 
tinymll_reset_arena(Arena** arena, Error** error)
{
    if (arena == NULL || *arena == NULL)
    {
        tinymll_set_error(
            error,
            TINYMLL_NULL_PTR,
            "`arena` is NULL."
        );
        return TINYMLL_FALSE;
    }

    (*arena)->offset = 0;

    return TINYMLL_TRUE;
}

b8 
tinymll_destroy_arena(Arena** arena, Error** error)
{
    if (arena == NULL || *arena == NULL)
    {
        tinymll_set_error(
            error,
            TINYMLL_NULL_PTR,
            "`arena` is NULL."
        );
        return TINYMLL_FALSE;
    }

    #if defined(__linux__) || defined(__APPLE__)
    if(munmap((*arena)->memory_ptr, (*arena)->reserved_size) == -1)
    {
        tinymll_set_error(
            error,
            TINYMLL_ALLOCATION_FAILED,
            "`munmap` failed to deallocate memory."
        );
        return TINYMLL_FALSE;
    }

    #elif defined(_WIN32)
    tinymll_clib_free((*arena)->memory_ptr, error);

    #endif

    (*arena)->memory_ptr = NULL;

    tinymll_clib_free(*arena, error);
    *arena = NULL;

    return TINYMLL_TRUE;
}

void* 
tinymll__arena_allocate(Arena* arena, u64 size, u64 alignment, Error** error)
{
    if (arena == NULL)
    {
        tinymll_set_error(
            error,
            TINYMLL_NULL_PTR,
            "`arena` is NULL."
        );
        return NULL;
    }

    if (size == 0)
    {
        tinymll_set_error(
            error,
            TINYMLL_ALLOCATION_ZERO_SIZE,
            "Trying to allocate a zero memory block."
        );
        return NULL;
    }

    if (alignment == 0 || (alignment & (alignment - 1)) != 0)
    {
        tinymll_set_error(
            error,
            TINYMLL_ALLOCATION_ALIGNMENT,
            "Alignment is not a power of 2."
        );
        return NULL;
    }

    uptr curr_ptr       = (uptr)arena->memory_ptr + arena->offset;
    uptr aligned_ptr    = (curr_ptr + alignment - 1) & ~(alignment - 1);
    u64 padding         = (u64)(aligned_ptr - curr_ptr);
    u64 new_offset      = arena->offset + padding + size;

    if (new_offset > arena->reserved_size)
    {
        tinymll_set_error(
            error,
            TINYMLL_ALLOCATION_OVERFLOW,
            "Allocation overflow."
        );
        return NULL;
    }

    if (new_offset > arena->commited_size)
    {
        u64 commit_size_needed  = new_offset - arena->commited_size;
        u64 commit_size_rounded = (commit_size_needed + PAGE_SIZE - 1) & ~(PAGE_SIZE - 1);

        void* commit_start = (u8*)arena->memory_ptr + arena->commited_size;

        #if defined(__linux__) || defined(__APPLE__)
        if (mprotect(commit_start, commit_size_rounded, PROT_READ | PROT_WRITE) != 0)
        {
            tinymll_set_error(
                error,
                TINYMLL_ALLOCATION_FAILED,
                ""
            );
            return NULL;
        }

        #elif defined(_WIN32)
            //TODO

        #endif

        arena->commited_size += commit_size_rounded;
    }

    void* new_memory    = (void*)aligned_ptr;
    arena->offset       = new_offset;

    return new_memory;
}

static void* 
tinymll__arena_malloc_wrapper(u64 size, void* ctx, Error** error) 
{
    ASSERT_WITH_MESSAGE(ctx != NULL, "Allocator ctx is NULL.");
    Arena* arena = (Arena*)ctx;
    return tinymll__arena_allocate(arena, size, 8, error); 
}

static void* 
tinymll__arena_aligned_alloc_wrapper(u64 alignment, u64 size, void* ctx, Error** error) 
{
    ASSERT_WITH_MESSAGE(ctx != NULL, "Allocator ctx is NULL.");
    Arena* arena = (Arena*)ctx;
    return tinymll__arena_allocate(arena, size, alignment, error);
}

static void* 
tinymll__arena_realloc_wrapper(void* ptr, u64 size, void* ctx, Error** error) 
{
    (void)ptr;
    (void)size;
    (void)ctx;
    tinymll_set_error(
        error, 
        TINYMLL_UNSUPPORTED, 
        "Arena does not support reallocation."
    );
    return NULL;
}

static void 
tinymll__arena_free_wrapper(void* ptr, void* ctx, Error** error) 
{
    (void)ptr;
    (void)ctx;
    (void)error;
    return;
}

b8 
tinymll_create_arena_allocator(Arena* arena, Allocator* arena_allocator_out, Error** error)
{
    if (arena == NULL || arena_allocator_out == NULL)
    {
        tinymll_set_error(
            error, 
            TINYMLL_NULL_PTR, 
            "`arena` or `arena_allocator_out` are NULL."
        );
        return TINYMLL_FALSE;
    }

    arena_allocator_out->malloc         = tinymll__arena_malloc_wrapper;
    arena_allocator_out->aligned_alloc  = tinymll__arena_aligned_alloc_wrapper;
    arena_allocator_out->realloc        = tinymll__arena_realloc_wrapper;
    arena_allocator_out->free           = tinymll__arena_free_wrapper;
    arena_allocator_out->ctx            = arena;

    return TINYMLL_TRUE;
}

static Allocator* g_tinymll_arena_allocator = &(Allocator){
    .malloc         = tinymll__arena_malloc_wrapper,
    .aligned_alloc  = tinymll__arena_aligned_alloc_wrapper,
    .realloc        = tinymll__arena_realloc_wrapper,
    .free           = tinymll__arena_free_wrapper,
    .ctx            = NULL,
};

b8 
tinymll_set_global_arena_allocator(Arena* arena, Error** error)
{
    if (arena == NULL)
    {
        tinymll_set_error(
            error,
            TINYMLL_NULL_PTR,
            "`arena` is NULL."
        );
        return TINYMLL_FALSE;
    }

    g_tinymll_arena_allocator->ctx = arena;

    return TINYMLL_TRUE;
}

Allocator* 
tinymll__get_global_arena_allocator(void)
{
    return g_tinymll_arena_allocator;
}