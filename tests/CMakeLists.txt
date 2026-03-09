# Build tests

message(STATUS "")
message(STATUS "===============================")
message(STATUS "Building TinyMLL tests ...")

message(STATUS "Matrix creation test ...")
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

message(STATUS "===============================")
message(STATUS "")