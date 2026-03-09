#ifndef TINYMLL_TENSOR_H
#define TINYMLL_TENSOR_H

#include "core/types.h"
#include "core/error.h"
#include "core/allocator.h"

#include <stdio.h>

typedef enum TinyMLLDataType
{
    TINYMLL_F32,
    TINYMLL_F64,
    TINYMLL_I32,
    TINYMLL_I64,
} TinyMLLDataType;

typedef struct TinyMLLTensor
{
    void*           data;
    u64             size;
    i64             shape[5]; // Maximum tensor dimensions = 5
    TinyMLLDataType type;
} TinyMLLTensor;

#define TType   TinyMLLDataType
#define Tensor  TinyMLLTensor

b8 tinymll_create_tensor(void* data, TType data_type, u64 data_size, i64 shape[5], Tensor** tensor_out, Allocator* allocator, Error** error);
b8 tinymll_create_random_tensor(TType data_type, u64 data_size, i64 shape[5], Tensor** tensor_out, Allocator* allocator, Error** error);
b8 tinymll_create_zeroes_tensor(TType data_type, u64 data_size, i64 shape[5], Tensor** tensor_out, Allocator* allocator, Error** error);
b8 tinymll_create_ones_tensor(TType data_type, u64 data_size, i64 shape[5], Tensor** tensor_out, Allocator* allocator, Error** error);
b8 tinymll_create_identity_tensor(TType data_type, u64 data_size, i64 shape[5], Tensor** tensor_out, Allocator* allocator, Error** error);
b8 tinymll_create_tensor_from_file(FILE* file, Tensor** tensor_out, Allocator* allocator, Error** error);

#define create_tensor           tinymll_create_tensor
#define create_random_tensor    tinymll_create_random_tensor
#define create_zeroes_tensor    tinymll_create_zeroes_tensor
#define create_ones_tensor      tinymll_create_ones_tensor
#define create_identity_tensor  tinymll_create_identity_tensor
#define create_tensor_from_file tinymll_create_tensor_from_file

#endif // TINYMLL_TENSOR_H