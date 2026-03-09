#include "utils/tensor_checks.h"

#include <math.h>

b8 
tinymll__check_tensor_shape(i64 shape[5], Error** error)
{
    b8 is_shape_valid = TINYMLL_TRUE;
    for (u8 i = 0; i < 5; ++i)
    {
        if (shape[i] > 0) continue;
        if (shape[i] == 0 && i == 0) { is_shape_valid = TINYMLL_FALSE; break; }
        if (shape[i] == 0 && i > 0) break;
        if (shape[i] == -1) break;
        if (shape[i] < -1) { is_shape_valid = TINYMLL_FALSE; break; }
    }

    if (is_shape_valid == TINYMLL_FALSE)
        tinymll_set_error(
            error,
            TINYMLL_TENSOR_SHAPE_INVALID,
            "Invalid tensor shape."
        );

    return is_shape_valid;
}

b8 
tinymll__check_tensor_shape_size_match(i64 shape[5], u64 data_size, Error** error)
{
    b8 shape_size_match     = TINYMLL_TRUE;
    b8 is_last_minus_one    = TINYMLL_FALSE;

    u8 i        = 0;
    u64 size    = 1;

    for (; i < 5; ++i)
    {
        if (shape[i] == 0) break;
        if (shape[i] == -1) { is_last_minus_one = TINYMLL_TRUE; break; }

        size *= shape[i];
    }

    if (is_last_minus_one == TINYMLL_TRUE)
    {
        if (data_size % size != 0) shape_size_match = TINYMLL_FALSE;

        shape[i] = data_size / size;
    }
    else if (size != data_size) shape_size_match = TINYMLL_FALSE;
        

    if (shape_size_match == TINYMLL_FALSE)
        tinymll_set_error(
            error,
            TINYMLL_TENSOR_SHAPE_SIZE_MISMATCH,
            "Tensor size does not match its dimensions."
        );

    return shape_size_match;
}