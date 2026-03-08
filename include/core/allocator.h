#ifndef TINYMLL_ALLOCATOR_H
#define TINYMLL_ALLOCATOR_H

#include "core/types.h"
#include "core/error.h"

typedef struct TinyMLLAllocator
{
    void* (*malloc)(u64 size, void* ctx, Error** error);
    void* (*aligned_alloc)(u64 alignment, u64 size, void* ctx, Error** error);
    void* (*realloc)(void* ptr, u64 size, void* ctx, Error** error);
    void  (*free)(void* ptr, void* ctx, Error** error);
    void* ctx;
} TinyMLLAllocator;

#define Allocator TinyMLLAllocator

Allocator* tinymll__get_clib_allocator(void);

#define tinymll_clib_malloc(size, error)                   tinymll__get_clib_allocator()->malloc((size), NULL, (error))
#define tinymll_clib_aligned_alloc(alignment, size, error) tinymll__get_clib_allocator()->aligned_alloc((alignment), (size), NULL, (error))
#define tinymll_clib_realloc(ptr, size, error)             tinymll__get_clib_allocator()->realloc((ptr), (size), NULL, (error))
#define tinymll_clib_free(ptr, error)                      tinymll__get_clib_allocator()->free((ptr), NULL, (error))

#define clib_malloc         tinymll_clib_malloc
#define clib_aligned_alloc  tinymll_clib_aligned_alloc
#define clib_realloc        tinymll_clib_realloc
#define clib_free           tinymll_clib_free 

#endif // TINYMLL_ALLOCATOR_H