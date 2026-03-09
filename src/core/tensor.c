#include "core/tensor.h"

#include "core/random.h"
#include "utils/tensor_checks.h"

#include <memory.h>

b8 
tinymll_create_tensor(void* data, TType data_type, u64 data_size, i64 shape[5], Tensor** tensor_out, Allocator* allocator, Error** error)
{
    if (data == NULL || shape == NULL || tensor_out == NULL || allocator == NULL)
    {
        tinymll_set_error(
            error,
            TINYMLL_NULL_PTR,
            "`data`, `shape`, `tensor_out` or `allocator` are NULL."
        );
        return TINYMLL_FALSE;
    }

    // check shape
    b8 is_shape_valid = tinymll__check_tensor_shape(shape, error);
    if (is_shape_valid == TINYMLL_FALSE) return TINYMLL_FALSE;

    // check shape-size match
    b8 shape_size_match = tinymll__check_tensor_shape_size_match(shape, data_size, error);
    if (shape_size_match == TINYMLL_FALSE) return TINYMLL_FALSE;
    
    *tensor_out = (Tensor*)allocator->malloc(sizeof(Tensor), allocator->ctx, error);
    if (*tensor_out == NULL) return TINYMLL_FALSE;

    (*tensor_out)->size = data_size;
    (*tensor_out)->type = data_type;
    u64 size_of_bytes = 0;
    switch (data_type)
    {
    case  TINYMLL_F32:
        size_of_bytes =  sizeof(f32);
        (*tensor_out)->data = allocator->malloc(size_of_bytes * data_size, allocator->ctx, error);
        break;
    case  TINYMLL_F64:
        size_of_bytes = sizeof(f64);
        (*tensor_out)->data = allocator->malloc(size_of_bytes * data_size, allocator->ctx, error);
        break;
    case  TINYMLL_I32:
        size_of_bytes = sizeof(i32);
        (*tensor_out)->data = allocator->malloc(size_of_bytes * data_size, allocator->ctx, error);
        break;
    case  TINYMLL_I64:
        size_of_bytes = sizeof(i64);
        (*tensor_out)->data = allocator->malloc(size_of_bytes * data_size, allocator->ctx, error);
        break;

    default:
        allocator->free(*tensor_out, allocator->ctx, error);
        tinymll_set_error(
            error,
            TINYMLL_UNDEFINED,
            "Undefined type for tensor type."
        );
        return TINYMLL_FALSE;
    }
    if ((*tensor_out)->data == NULL) 
    {
        allocator->free(*tensor_out, allocator->ctx, error);
        return TINYMLL_FALSE;
    }

    memcpy(
        (*tensor_out)->data,
        data,
        size_of_bytes * data_size
    );

    memcpy(
        (*tensor_out)->shape,
        shape,
        sizeof(i64) * 5
    );

    return TINYMLL_TRUE;
}

b8 
tinymll_create_random_tensor(TType data_type, u64 data_size, i64 shape[5], Tensor** tensor_out, Allocator* allocator, Error** error)
{
    (void)data_type;
    (void)data_size;
    (void)shape;
    (void)tensor_out;
    (void)allocator;
    
    tinymll_set_error(
        error,
        TINYMLL_NOT_IMPLEMENTED,
        "`tinymll_create_random_tensor` not implemented yet."
    );
    return TINYMLL_FALSE;
}

b8 
tinymll_create_zeroes_tensor(TType data_type, u64 data_size, i64 shape[5], Tensor** tensor_out, Allocator* allocator, Error** error)
{
    (void)data_type;
    (void)data_size;
    (void)shape;
    (void)tensor_out;
    (void)allocator;
    
    tinymll_set_error(
        error,
        TINYMLL_NOT_IMPLEMENTED,
        "`tinymll_create_zeroes_tensor` not implemented yet."
    );
    return TINYMLL_FALSE;
}

b8 
tinymll_create_ones_tensor(TType data_type, u64 data_size, i64 shape[5], Tensor** tensor_out, Allocator* allocator, Error** error)
{
    (void)data_type;
    (void)data_size;
    (void)shape;
    (void)tensor_out;
    (void)allocator;
    
    tinymll_set_error(
        error,
        TINYMLL_NOT_IMPLEMENTED,
        "`tinymll_create_ones_tensor` not implemented yet."
    );
    return TINYMLL_FALSE;
}

b8 
tinymll_create_identity_tensor(TType data_type, u64 data_size, i64 shape[5], Tensor** tensor_out, Allocator* allocator, Error** error)
{
    (void)data_type;
    (void)data_size;
    (void)shape;
    (void)tensor_out;
    (void)allocator;
    
    tinymll_set_error(
        error,
        TINYMLL_NOT_IMPLEMENTED,
        "`tinymll_create_identity_tensor` not implemented yet."
    );
    return TINYMLL_FALSE;
}

b8 
tinymll_create_tensor_from_file(FILE* file, Tensor** tensor_out, Allocator* allocator, Error** error)
{
    (void)file;
    (void)tensor_out;
    (void)allocator;
    
    tinymll_set_error(
        error,
        TINYMLL_NOT_IMPLEMENTED,
        "`tinymll_create_tensor_from_file` not implemented yet."
    );
    return TINYMLL_FALSE;
}
