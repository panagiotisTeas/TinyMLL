#include "core/allocator.h"

// Standard lib allocator (Default)

#include <stdlib.h>

static void* 
tinymll__clib_malloc(u64 size, void* ctx, Error** error)
{
    (void)ctx;

    if (size == 0)
    {
        tinymll_set_error(
            error,
            TINYMLL_ALLOCATION_ZERO_SIZE,
            "Trying to allocate a zero memory block."
        );
        return NULL;
    }

    void* ptr = malloc(size);
    if (ptr == NULL)
    {
        tinymll_set_error(
            error,
            TINYMLL_ALLOCATION_FAILED,
            "`malloc` failed to allocate memory."
        );
        return NULL;
    }

    return ptr;
}

static void* 
tinymll__clib_aligned_alloc(u64 alignment, u64 size, void* ctx, Error** error)
{
    (void)ctx;

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

    void* ptr = aligned_alloc(alignment, size);
    if (ptr == NULL)
    {
        tinymll_set_error(
            error,
            TINYMLL_ALLOCATION_FAILED,
            "`aligned_alloc` failed to aligned allocate memory."
        );
        return NULL;
    }

    return ptr;
}

static void* 
tinymll__clib_realloc(void* ptr, u64 size, void* ctx, Error** error)
{
    (void)ctx;

    if (size == 0)
    {
        tinymll_set_error(
            error,
            TINYMLL_ALLOCATION_ZERO_SIZE,
            "Trying to allocate a zero memory block."
        );
        return NULL;
    }

    if (ptr == NULL)
    {
        tinymll_set_error(
            error,
            TINYMLL_NULL_PTR,
            "`ptr` is NULL."
        );
        return NULL;
    }

    void* new_ptr = realloc(ptr, size);
    if (new_ptr == NULL)
    {
        tinymll_set_error(
            error,
            TINYMLL_ALLOCATION_FAILED,
            "`realloc` failed to reallocate memory."
        );
        return NULL;
    }

    return new_ptr;
}

static void
tinymll__clib_free(void* ptr, void* ctx, Error** error)
{
    (void)ctx;

    if (ptr == NULL)
    {
        tinymll_set_error(
            error,
            TINYMLL_NULL_PTR,
            "`ptr` is NULL."
        );
        return;
    }

    free(ptr);
}

static Allocator* g_tinymll_clib_allocator = &(Allocator){
    .malloc         = tinymll__clib_malloc,
    .aligned_alloc  = tinymll__clib_aligned_alloc,
    .realloc        = tinymll__clib_realloc,
    .free           = tinymll__clib_free,
    .ctx            = NULL
};

Allocator* 
tinymll__get_clib_allocator(void)
{
    return g_tinymll_clib_allocator;
}