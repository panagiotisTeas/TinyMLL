#ifndef TINYMLL_TENSOR_CHECKS_H
#define TINYMLL_TENSOR_CHECKS_H

#include "core/types.h"
#include "core/error.h"

b8 tinymll__check_tensor_shape(i64 shape[5], Error** error);
b8 tinymll__check_tensor_shape_size_match(i64 shape[5], u64 data_size, Error** error);

#endif // TINYMLL_TENSOR_CHECKS_H