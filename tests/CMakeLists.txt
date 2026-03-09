# Build tests

message(STATUS "")
message(STATUS "===============================")
message(STATUS "Building TinyMLL tests ...")

message(STATUS "Tensor creation test ...")
add_executable(tensor_creation 
    ../external/unity/unity.c
    tensors/tensor_creation_test.c
)
target_compile_options(tensor_creation PRIVATE
    -Wall
    -Wextra
    -pedantic
)
target_include_directories(tensor_creation PRIVATE 
    ../external/unity 
    ../include
)
target_link_libraries(tensor_creation PRIVATE tinymll)

message(STATUS "Tensor arithmetic test ...")
add_executable(tensor_arithmetic 
    ../external/unity/unity.c
    tensors/tensor_arithmetic_test.c
)
target_compile_options(tensor_arithmetic PRIVATE
    -Wall
    -Wextra
    -pedantic
)
target_include_directories(tensor_arithmetic PRIVATE 
    ../external/unity 
    ../include
)
target_link_libraries(tensor_arithmetic PRIVATE tinymll)

message(STATUS "===============================")
message(STATUS "")