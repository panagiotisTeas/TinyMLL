#include "core/error.h"

#include "core/types.h"

#include <stdlib.h>
#include <stdio.h>

#define TINYMLL_ERROR_MESSAGE_BUFFER_SIZE 1024

void 
tinymll_set_error(Error** error, ErrorCode code, const char* message, ...)
{
    if (error == NULL) return;

    if (*error != NULL) tinymll_clear_error(error);

    *error = (Error*)malloc(sizeof(Error));
    if (*error == NULL) exit(EXIT_FAILURE);

    (*error)->code = code;
    (*error)->message = (char*)malloc(sizeof(char) * TINYMLL_ERROR_MESSAGE_BUFFER_SIZE);
    if ((*error)->message == NULL) { free(*error); exit(EXIT_FAILURE); }
    u32 message_buffer_offset = 0;

    va_list args;
    va_start(args, message);

    message_buffer_offset += vsnprintf(
        (*error)->message + message_buffer_offset, 
        TINYMLL_ERROR_MESSAGE_BUFFER_SIZE - message_buffer_offset, 
        message, 
        args);
        
    va_end(args);
}

void 
tinymll_clear_error(Error** error)
{
    if (error == NULL || *error == NULL) return;

    free((*error)->message);
    free(*error);
    *error = NULL;
}