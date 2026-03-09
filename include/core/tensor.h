#ifndef TINYMLL_TENSOR_H
#define TINYMLL_TENSOR_H

#include "core/types.h"
#include "core/error.h"
#include "core/random.h"
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
b8 tinymll_create_random_tensor(rng_state* rng, TType data_type, u64 data_size, i64 shape[5], Tensor** tensor_out, Allocator* allocator, Error** error);
b8 tinymll_create_zeroes_tensor(TType data_type, u64 data_size, i64 shape[5], Tensor** tensor_out, Allocator* allocator, Error** error);
b8 tinymll_create_ones_tensor(TType data_type, u64 data_size, i64 shape[5], Tensor** tensor_out, Allocator* allocator, Error** error);
b8 tinymll_create_tensor_from_file(FILE* file, Tensor** tensor_out, Allocator* allocator, Error** error);

#define create_tensor           tinymll_create_tensor
#define create_random_tensor    tinymll_create_random_tensor
#define create_zeroes_tensor    tinymll_create_zeroes_tensor
#define create_ones_tensor      tinymll_create_ones_tensor
#define create_tensor_from_file tinymll_create_tensor_from_file

#define get_0d_tensor(tensor, type)                 (((type*)(tensor)->data)[0])            
#define get_1d_tensor(tensor, type, i)              (((type*)(tensor)->data)[i])
#define get_2d_tensor(tensor, type, i, j)           (((type*)(tensor)->data)[j + i * (tensor)->shape[1]])
#define get_3d_tensor(tensor, type, i, j, k)        (((type*)(tensor)->data)[k + j * (tensor)->shape[2] + i * (tensor)->shape[2] * (tensor)->shape[1]])
#define get_4d_tensor(tensor, type, i, j, k, l)     (((type*)(tensor)->data)[l + k * (tensor)->shape[3] + j * (tensor)->shape[3] * (tensor)->shape[2] + i * (tensor)->shape[3] * (tensor)->shape[2] * (tensor)->shape[1]])
#define get_5d_tensor(tensor, type, i, j, k, l, m)  (((type*)(tensor)->data)[m + l * (tensor)->shape[4] + k * (tensor)->shape[4] * (tensor)->shape[3] + j * (tensor)->shape[4] * (tensor)->shape[3] * (tensor)->shape[2] + i * (tensor)->shape[4] * (tensor)->shape[3] * (tensor)->shape[2] * (tensor)->shape[1]])

#endif // TINYMLL_TENSOR_H