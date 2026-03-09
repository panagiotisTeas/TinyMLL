#ifndef TINYMLL_TYPES_H
#define TINYMLL_TYPES_H

#include <stdint.h>

typedef uint8_t     b8;
typedef uint16_t    b16;
typedef uint32_t    b32;
typedef uint64_t    b64;

typedef uint8_t     u8;
typedef uint16_t    u16;
typedef uint32_t    u32;
typedef uint64_t    u64;

typedef int8_t      i8;
typedef int16_t     i16;
typedef int32_t     i32;
typedef int64_t     i64;

typedef float       f32;
typedef double      f64;

typedef uintptr_t   uptr;

#define KiB(x) (u64)((x) << 10)
#define MiB(x) (u64)((x) << 20)
#define GiB(x) (u64)((x) << 30)

#define TINYMLL_TRUE   1
#define TINYMLL_FALSE  0

#endif // TINYMLL_TYPES_H