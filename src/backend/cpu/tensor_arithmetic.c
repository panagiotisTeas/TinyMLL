#include "backend/cpu/tensor_arithmetic.h"

b8 
tinymll_cpu_tensor_addition(Tensor* tensor_a, Tensor* tensor_b, Tensor** tensor_out, Allocator* allocator, Error** error)
{
    if (tensor_a == NULL || tensor_b == NULL || tensor_out == NULL || allocator == NULL)
    {
        tinymll_set_error(
            error,
            TINYMLL_NULL_PTR,
            "`tensor_a`, `tensor_b`, `tensor_out` or `allocator` are NULL."
        );
        return TINYMLL_FALSE;
    }

    tinymll_set_error(
        error,
        TINYMLL_NOT_IMPLEMENTED,
        "`tinymll_cpu_tensor_addition` not implemented yet."
    );
    return TINYMLL_FALSE;
}

b8 
tinymll_cpu_tensor_subtraction(Tensor* tensor_a, Tensor* tensor_b, Tensor** tensor_out, Allocator* allocator, Error** error)
{
    (void)tensor_a;
    (void)tensor_b;
    (void)tensor_out;
    (void)allocator;
    
    tinymll_set_error(
        error,
        TINYMLL_NOT_IMPLEMENTED,
        "`tinymll_cpu_tensor_subtraction` not implemented yet."
    );
    return TINYMLL_FALSE;
}

b8 
tinymll_cpu_tensor_hadamard(Tensor* tensor_a, Tensor* tensor_b, Tensor** tensor_out, Allocator* allocator, Error** error)
{
    (void)tensor_a;
    (void)tensor_b;
    (void)tensor_out;
    (void)allocator;
    
    tinymll_set_error(
        error,
        TINYMLL_NOT_IMPLEMENTED,
        "`tinymll_cpu_tensor_hadamard` not implemented yet."
    );
    return TINYMLL_FALSE;
}

b8 
tinymll_cpu_tensor_division(Tensor* tensor_a, Tensor* tensor_b, Tensor** tensor_out, Allocator* allocator, Error** error)
{
    (void)tensor_a;
    (void)tensor_b;
    (void)tensor_out;
    (void)allocator;
    
    tinymll_set_error(
        error,
        TINYMLL_NOT_IMPLEMENTED,
        "`tinymll_cpu_tensor_division` not implemented yet."
    );
    return TINYMLL_FALSE;
}