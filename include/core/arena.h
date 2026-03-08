#ifndef AMLL_ARENA_H
#define AMLL_ARENA_H

#include "core/types.h"
#include "core/error.h"
#include "core/allocator.h"

#if defined(__linux__) || defined(__APPLE__)
#include <sys/mman.h>
#include <unistd.h>

#define PAGE_SIZE sysconf(_SC_PAGESIZE)

#elif defined(_WIN32)
//TODO malloc is used

#endif

typedef struct TinyMLLArena
{
    u8* memory_ptr;
    u64 reserved_size;
    u64 commited_size;
    u64 offset;
} TinyMLLArena;

#define Arena TinyMLLArena

b8 tinymll_create_arena(u64 size, Arena** arena_out, Error** error);
b8 tinymll_reset_arena(Arena** arena, Error** error);
b8 tinymll_destroy_arena(Arena** arena, Error** error);

void* tinymll__arena_allocate(Arena* arena, u64 size, u64 alignment, Error** error); // Don't use this

b8 tinymll_create_arena_allocator(Arena* arena, Allocator* arena_allocator_out, Error** error); // Allocator is created in the stack by the user and it is initialized by using this function

b8 tinymll_set_global_arena_allocator(Arena* arena, Error** error);
Allocator* tinymll__get_global_arena_allocator(void);

#define tinymll_arena_malloc(arena_allocator, size, error)                     (arena_allocator)->malloc((size), (arena_allocator)->ctx, (error))
#define tinymll_arena_aligned_alloc(arena_allocator, alignment, size, error)   (arena_allocator)->aligned_alloc((alignment), (size), (arena_allocator)->ctx, (error))
#define tinymll_arena_realloc(arena_allocator, ptr, size, error)               (arena_allocator)->realloc((ptr), (size), (arena_allocator)->ctx, (error))
#define tinymll_arena_free(arena_allocator, ptr, error)                        (arena_allocator)->free((ptr), (arena_allocator)->ctx, (error))

#define tinymll_global_arena_malloc(size, error)                                tinymll__get_global_arena_allocator()->malloc((size), NULL, (error))
#define tinymll_global_arena_aligned_alloc(alignment, size, error)              tinymll__get_global_arena_allocator()->aligned_alloc((alignment), (size), NULL, (error))
#define tinymll_global_arena_realloc(ptr, size, error)                          tinymll__get_global_arena_allocator()->realloc((ptr), (size), NULL, (error))
#define tinymll_global_arena_free(ptr, error)                                   tinymll__get_global_arena_allocator()->free((ptr), NULL, (error))

#define create_arena                tinymll_create_arena
#define reset_arena                 tinymll_reset_arena
#define destroy_arena               tinymll_destroy_arena
#define create_arena_allocator      tinymll_create_arena_allocator

#define set_global_arena_allocator  tinymll_set_global_arena_allocator

#define arena_malloc                tinymll_arena_malloc
#define arena_aligned_alloc         tinymll_arena_aligned_alloc
#define arena_realloc               tinymll_arena_realloc
#define arena_free                  tinymll_arena_free

#define global_arena_malloc         tinymll_global_arena_malloc
#define global_arena_aligned_alloc  tinymll_global_arena_aligned_alloc
#define global_arena_realloc        tinymll_global_arena_realloc
#define global_arena_free           tinymll_global_arena_free

#endif // AMLL_ARENA_H