#ifndef TINYMLL_ERROR_H
#define TINYMLL_ERROR_H

#include <assert.h>

#define ASSERT(expression)                          assert((expression))
#define ASSERT_WITH_MESSAGE(expression, message)    assert((expression) && (message))

#include <stdarg.h>

typedef enum TinyMLLErrorCode
{
    TINYMLL_OK = 0,                 // everythings ok
    // Allocation Errors
    TINYMLL_ALLOCATION_FAILED,      // some allocation function (malloc, ...) returned a null pointer instead of an address
    TINYMLL_ALLOCATION_ZERO_SIZE,   // allocation of a zero size block of memory
    TINYMLL_ALLOCATION_ALIGNMENT,   // allication alignment is not a power of 2
    // General Errors
    TINYMLL_NULL_PTR,               // null pointer passed as a parameter
} TinyMLLErrorCode;

typedef struct TinyMLLError
{
    TinyMLLErrorCode    code;
    char*               message;
} TinyMLLError;

#define ErrorCode   TinyMLLErrorCode
#define Error       TinyMLLError

void tinymll_set_error(Error** error, ErrorCode code, const char* message, ...);
void tinymll_clear_error(Error** error);

#define set_error   tinymll_set_error
#define clear_error tinymll_clear_error

#endif // TINYMLL_ERROR_H