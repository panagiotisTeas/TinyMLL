#include "core/tensor.h"

#include "utils/tensor_checks.h"
#include "core/random.h"

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
tinymll_create_random_tensor(rng_state* rng, TType data_type, u64 data_size, i64 shape[5], Tensor** tensor_out, Allocator* allocator, Error** error)
{
    if (shape == NULL || tensor_out == NULL || allocator == NULL)
    {
        tinymll_set_error(
            error,
            TINYMLL_NULL_PTR,
            "`shape`, `tensor_out` or `allocator` are NULL."
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

    //TODO Refactor code
    switch (data_type)
    {
    case  TINYMLL_F32:
        size_of_bytes =  sizeof(f32);
        (*tensor_out)->data = allocator->malloc(size_of_bytes * data_size, allocator->ctx, error);
        
        if ((*tensor_out)->data == NULL) 
        {
            allocator->free(*tensor_out, allocator->ctx, error);
            return TINYMLL_FALSE;
        }

        for (u64 i = 0; i < data_size; ++i)
            ((f32*)(*tensor_out)->data)[i] = tinymll_real_bounded_random(rng, -1.0, 1.0);

        break;
    case  TINYMLL_F64:
        size_of_bytes = sizeof(f64);
        (*tensor_out)->data = allocator->malloc(size_of_bytes * data_size, allocator->ctx, error);

        if ((*tensor_out)->data == NULL) 
        {
            allocator->free(*tensor_out, allocator->ctx, error);
            return TINYMLL_FALSE;
        }

        for (u64 i = 0; i < data_size; ++i)
            ((f64*)(*tensor_out)->data)[i] = (f64)tinymll_real_bounded_random(rng, -1.0, 1.0);

        break;
    case  TINYMLL_I32:
        size_of_bytes = sizeof(i32);
        (*tensor_out)->data = allocator->malloc(size_of_bytes * data_size, allocator->ctx, error);

        if ((*tensor_out)->data == NULL) 
        {
            allocator->free(*tensor_out, allocator->ctx, error);
            return TINYMLL_FALSE;
        }

        for (u64 i = 0; i < data_size; ++i)
            ((i32*)(*tensor_out)->data)[i] = (i32)tinymll_real_bounded_random(rng, -10.0, 10.0);

        break;
    case  TINYMLL_I64:
        size_of_bytes = sizeof(i64);
        (*tensor_out)->data = allocator->malloc(size_of_bytes * data_size, allocator->ctx, error);

        if ((*tensor_out)->data == NULL) 
        {
            allocator->free(*tensor_out, allocator->ctx, error);
            return TINYMLL_FALSE;
        }

        for (u64 i = 0; i < data_size; ++i)
            ((i64*)(*tensor_out)->data)[i] = (i64)tinymll_real_bounded_random(rng, -10.0, 10.0);

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

    memcpy(
        (*tensor_out)->shape,
        shape,
        sizeof(i64) * 5
    );

    return TINYMLL_TRUE;
}

b8 
tinymll_create_zeroes_tensor(TType data_type, u64 data_size, i64 shape[5], Tensor** tensor_out, Allocator* allocator, Error** error)
{
    if (shape == NULL || tensor_out == NULL || allocator == NULL)
    {
        tinymll_set_error(
            error,
            TINYMLL_NULL_PTR,
            "`shape`, `tensor_out` or `allocator` are NULL."
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

    //TODO Refactor code
    switch (data_type)
    {
    case  TINYMLL_F32:
        size_of_bytes =  sizeof(f32);
        (*tensor_out)->data = allocator->malloc(size_of_bytes * data_size, allocator->ctx, error);
        
        if ((*tensor_out)->data == NULL) 
        {
            allocator->free(*tensor_out, allocator->ctx, error);
            return TINYMLL_FALSE;
        }

        for (u64 i = 0; i < data_size; ++i)
            ((f32*)(*tensor_out)->data)[i] = 0.0f;

        break;
    case  TINYMLL_F64:
        size_of_bytes = sizeof(f64);
        (*tensor_out)->data = allocator->malloc(size_of_bytes * data_size, allocator->ctx, error);

        if ((*tensor_out)->data == NULL) 
        {
            allocator->free(*tensor_out, allocator->ctx, error);
            return TINYMLL_FALSE;
        }

        for (u64 i = 0; i < data_size; ++i)
            ((f64*)(*tensor_out)->data)[i] = 0.0;

        break;
    case  TINYMLL_I32:
        size_of_bytes = sizeof(i32);
        (*tensor_out)->data = allocator->malloc(size_of_bytes * data_size, allocator->ctx, error);

        if ((*tensor_out)->data == NULL) 
        {
            allocator->free(*tensor_out, allocator->ctx, error);
            return TINYMLL_FALSE;
        }

        for (u64 i = 0; i < data_size; ++i)
            ((i32*)(*tensor_out)->data)[i] = 0;

        break;
    case  TINYMLL_I64:
        size_of_bytes = sizeof(i64);
        (*tensor_out)->data = allocator->malloc(size_of_bytes * data_size, allocator->ctx, error);

        if ((*tensor_out)->data == NULL) 
        {
            allocator->free(*tensor_out, allocator->ctx, error);
            return TINYMLL_FALSE;
        }

        for (u64 i = 0; i < data_size; ++i)
            ((i32*)(*tensor_out)->data)[i] = 0;

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

    memcpy(
        (*tensor_out)->shape,
        shape,
        sizeof(i64) * 5
    );

    return TINYMLL_TRUE;
}

b8 
tinymll_create_ones_tensor(TType data_type, u64 data_size, i64 shape[5], Tensor** tensor_out, Allocator* allocator, Error** error)
{
    if (shape == NULL || tensor_out == NULL || allocator == NULL)
    {
        tinymll_set_error(
            error,
            TINYMLL_NULL_PTR,
            "`shape`, `tensor_out` or `allocator` are NULL."
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

    //TODO Refactor code
    switch (data_type)
    {
    case  TINYMLL_F32:
        size_of_bytes =  sizeof(f32);
        (*tensor_out)->data = allocator->malloc(size_of_bytes * data_size, allocator->ctx, error);
        
        if ((*tensor_out)->data == NULL) 
        {
            allocator->free(*tensor_out, allocator->ctx, error);
            return TINYMLL_FALSE;
        }

        for (u64 i = 0; i < data_size; ++i)
            ((f32*)(*tensor_out)->data)[i] = 1.0f;

        break;
    case  TINYMLL_F64:
        size_of_bytes = sizeof(f64);
        (*tensor_out)->data = allocator->malloc(size_of_bytes * data_size, allocator->ctx, error);

        if ((*tensor_out)->data == NULL) 
        {
            allocator->free(*tensor_out, allocator->ctx, error);
            return TINYMLL_FALSE;
        }

        for (u64 i = 0; i < data_size; ++i)
            ((f64*)(*tensor_out)->data)[i] = 1.0;

        break;
    case  TINYMLL_I32:
        size_of_bytes = sizeof(i32);
        (*tensor_out)->data = allocator->malloc(size_of_bytes * data_size, allocator->ctx, error);

        if ((*tensor_out)->data == NULL) 
        {
            allocator->free(*tensor_out, allocator->ctx, error);
            return TINYMLL_FALSE;
        }

        for (u64 i = 0; i < data_size; ++i)
            ((i32*)(*tensor_out)->data)[i] = 1;

        break;
    case  TINYMLL_I64:
        size_of_bytes = sizeof(i64);
        (*tensor_out)->data = allocator->malloc(size_of_bytes * data_size, allocator->ctx, error);

        if ((*tensor_out)->data == NULL) 
        {
            allocator->free(*tensor_out, allocator->ctx, error);
            return TINYMLL_FALSE;
        }

        for (u64 i = 0; i < data_size; ++i)
            ((i32*)(*tensor_out)->data)[i] = 1;

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

    memcpy(
        (*tensor_out)->shape,
        shape,
        sizeof(i64) * 5
    );

    return TINYMLL_TRUE;
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
