#ifndef TINYMLL_CPU_TENSOR_ARITHMETIC_H
#define TINYMLL_CPU_TENSOR_ARITHMETIC_H

#include "core/types.h"
#include "core/error.h"
#include "core/tensor.h"
#include "core/allocator.h"

b8 tinymll_cpu_tensor_addition(Tensor* tensor_a, Tensor* tensor_b, Tensor** tensor_out, Allocator* allocator, Error** error);
b8 tinymll_cpu_tensor_subtraction(Tensor* tensor_a, Tensor* tensor_b, Tensor** tensor_out, Allocator* allocator, Error** error);
b8 tinymll_cpu_tensor_hadamard(Tensor* tensor_a, Tensor* tensor_b, Tensor** tensor_out, Allocator* allocator, Error** error);
b8 tinymll_cpu_tensor_division(Tensor* tensor_a, Tensor* tensor_b, Tensor** tensor_out, Allocator* allocator, Error** error);

#endif // TINYMLL_CPU_TENSOR_ARITHMETIC_H