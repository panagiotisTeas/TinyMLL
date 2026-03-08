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
            ""
        );
        return NULL;
    }

    void* ptr = malloc(size);
    if (ptr == NULL)
    {
        tinymll_set_error(
            error,
            TINYMLL_ALLOCATION_FAILED,
            ""
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
            ""
        );
        return NULL;
    }

    if (alignment == 0 || (alignment & (alignment - 1)) != 0)
    {
        tinymll_set_error(
            error,
            TINYMLL_ALLOCATION_ALIGNMENT,
            ""
        );
        return NULL;
    }

    void* ptr = aligned_alloc(alignment, size);
    if (ptr == NULL)
    {
        tinymll_set_error(
            error,
            TINYMLL_ALLOCATION_FAILED,
            ""
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
            ""
        );
        return NULL;
    }

    if (ptr == NULL)
    {
        tinymll_set_error(
            error,
            TINYMLL_NULL_PTR,
            ""
        );
        return NULL;
    }

    void* new_ptr = realloc(ptr, size);
    if (new_ptr == NULL)
    {
        tinymll_set_error(
            error,
            TINYMLL_ALLOCATION_FAILED,
            ""
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
            ""
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