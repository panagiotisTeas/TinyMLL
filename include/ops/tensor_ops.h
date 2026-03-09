#ifndef TINYMLL_TENSOR_OPS_H
#define TINYMLL_TENSOR_OPS_H

#include "backend/cpu/tensor_arithmetic.h"

#if defined(CPU_NAIVE)
// Tensor arithmetic
#define tensor_addition     tinymll_cpu_tensor_addition
#define tensor_subtraction  tinymll_cpu_tensor_subtraction
#define tensor_hadamrd      tinymll_cpu_tensor_hadamard
#define tensor_division     tinymll_cpu_tensor_division

#elif defined(CPU_SIMD)
#define tensor_addition     tinymll_cpu_simd_tensor_addition
#define tensor_subtraction  tinymll_cpu_simd_tensor_subtraction
#define tensor_hadamrd      tinymll_cpu_simd_tensor_hadamard
#define tensor_division     tinymll_cpu_simd_tensor_division
//TODO

#elif defined(CPU_MT)
#define tensor_addition     tinymll_cpu_mt_tensor_addition
#define tensor_subtraction  tinymll_cpu_mt_tensor_subtraction
#define tensor_hadamrd      tinymll_cpu_mt_tensor_hadamard
#define tensor_division     tinymll_cpu_mt_tensor_division
//TODO

#elif defined(GPU)
#define tensor_addition     tinymll_gpu_tensor_addition
#define tensor_subtraction  tinymll_gpu_tensor_subtraction
#define tensor_hadamrd      tinymll_gpu_tensor_hadamard
#define tensor_division     tinymll_gpu_tensor_division
//TODO

#endif

#endif // TINYMLL_TENSOR_OPS_H