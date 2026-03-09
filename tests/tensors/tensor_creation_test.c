#include "unity.h"
#include "core/arena.h"
#include "core/allocator.h"
#include "core/tensor.h"

#include <time.h>

void 
setUp(void) {}

void 
tearDown(void) {}

void scalar_creation(void)
{
    Arena* arena = NULL;
    create_arena(KiB(1), &arena, NULL);
    set_global_arena_allocator(arena, NULL);

    Tensor* scalar = NULL;
    create_tensor(
        (f32[]){5.0f},
        TINYMLL_F32,
        1,
        (i64[]){1, 0, 0, 0, 0},
        &scalar,
        get_global_arena_allocator(),
        NULL
    );

    TEST_ASSERT_EQUAL_FLOAT(5.0f, get_0d_tensor(scalar, f32));
    destroy_arena(&arena, NULL);
}

void vector_creation(void)
{
    Arena* arena = NULL;
    create_arena(KiB(1), &arena, NULL);
    set_global_arena_allocator(arena, NULL);

    Tensor* vector = NULL;
    create_tensor(
        (f32[]){1.0f, 2.0f, 3.0f},
        TINYMLL_F32,
        3,
        (i64[]){3, 0, 0, 0, 0},
        &vector,
        get_global_arena_allocator(),
        NULL
    );

    TEST_ASSERT_EQUAL_FLOAT(1.0f, get_1d_tensor(vector, f32, 0));
    TEST_ASSERT_EQUAL_FLOAT(2.0f, get_1d_tensor(vector, f32, 1));
    TEST_ASSERT_EQUAL_FLOAT(3.0f, get_1d_tensor(vector, f32, 2));
    destroy_arena(&arena, NULL);
}

void matrix_creation(void)
{
    Arena* arena = NULL;
    create_arena(KiB(1), &arena, NULL);
    set_global_arena_allocator(arena, NULL);

    Tensor* matrix = NULL;
    create_tensor(
        (f32[]){1.0f, 2.0f, 3.0f, 4.0f},
        TINYMLL_F32,
        4,
        (i64[]){2, -1, 0, 0, 0},
        &matrix,
        get_global_arena_allocator(),
        NULL
    );

    TEST_ASSERT_EQUAL_FLOAT(1.0f, get_2d_tensor(matrix, f32, 0, 0));
    TEST_ASSERT_EQUAL_FLOAT(2.0f, get_2d_tensor(matrix, f32, 0, 1));
    TEST_ASSERT_EQUAL_FLOAT(3.0f, get_2d_tensor(matrix, f32, 1, 0));
    TEST_ASSERT_EQUAL_FLOAT(4.0f, get_2d_tensor(matrix, f32, 1, 1));
    destroy_arena(&arena, NULL);
}

void cube_creation(void)
{
    Arena* arena = NULL;
    create_arena(KiB(1), &arena, NULL);
    set_global_arena_allocator(arena, NULL);

    Tensor* cube = NULL;
    create_tensor(
        (f32[]){1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f},
        TINYMLL_F32,
        8,
        (i64[]){2, 2, -1, 0, 0},
        &cube,
        get_global_arena_allocator(),
        NULL
    );

    TEST_ASSERT_EQUAL_FLOAT(1.0f, get_3d_tensor(cube, f32, 0, 0, 0));
    TEST_ASSERT_EQUAL_FLOAT(2.0f, get_3d_tensor(cube, f32, 0, 0, 1));
    TEST_ASSERT_EQUAL_FLOAT(3.0f, get_3d_tensor(cube, f32, 0, 1, 0));
    TEST_ASSERT_EQUAL_FLOAT(4.0f, get_3d_tensor(cube, f32, 0, 1, 1));
    TEST_ASSERT_EQUAL_FLOAT(5.0f, get_3d_tensor(cube, f32, 1, 0, 0));
    TEST_ASSERT_EQUAL_FLOAT(6.0f, get_3d_tensor(cube, f32, 1, 0, 1));
    TEST_ASSERT_EQUAL_FLOAT(7.0f, get_3d_tensor(cube, f32, 1, 1, 0));
    TEST_ASSERT_EQUAL_FLOAT(8.0f, get_3d_tensor(cube, f32, 1, 1, 1));
    destroy_arena(&arena, NULL);
}

void random_creation(void)
{
    Arena* arena = NULL;
    create_arena(KiB(1), &arena, NULL);
    set_global_arena_allocator(arena, NULL);
    rng_state* rng = &(rng_state){.inc=0, .state=0};
    seed_rng(rng, time(NULL), time(NULL));

    Tensor* matrix = NULL;
    create_random_tensor(
        rng,
        TINYMLL_F32,
        6,
        (i64[]){2, -1, 0, 0, 0},
        &matrix,
        get_global_arena_allocator(),
        NULL
    );

    for (u8 row = 0; row < matrix->shape[0]; ++row)
    {
        printf("[");
        for (u8 col = 0; col < matrix->shape[1]; ++col)
        {
            printf("%f ", get_2d_tensor(matrix, f32, row, col));
        }
        printf("]\n");
    }
    destroy_arena(&arena, NULL);
}

void zeroes_creation(void)
{
    Arena* arena = NULL;
    create_arena(KiB(1), &arena, NULL);
    set_global_arena_allocator(arena, NULL);

    Tensor* cube = NULL;
    create_zeroes_tensor(
        TINYMLL_F32,
        12,
        (i64[]){2, 2, -1, 0, 0},
        &cube,
        get_global_arena_allocator(),
        NULL
    );

    TEST_ASSERT_EQUAL_FLOAT(0.0f, get_3d_tensor(cube, f32, 0, 0, 0));
    TEST_ASSERT_EQUAL_FLOAT(0.0f, get_3d_tensor(cube, f32, 0, 0, 1));
    TEST_ASSERT_EQUAL_FLOAT(0.0f, get_3d_tensor(cube, f32, 0, 0, 2));
    TEST_ASSERT_EQUAL_FLOAT(0.0f, get_3d_tensor(cube, f32, 0, 1, 0));
    TEST_ASSERT_EQUAL_FLOAT(0.0f, get_3d_tensor(cube, f32, 0, 1, 1));
    TEST_ASSERT_EQUAL_FLOAT(0.0f, get_3d_tensor(cube, f32, 0, 1, 2));
    TEST_ASSERT_EQUAL_FLOAT(0.0f, get_3d_tensor(cube, f32, 1, 0, 0));
    TEST_ASSERT_EQUAL_FLOAT(0.0f, get_3d_tensor(cube, f32, 1, 0, 1));
    TEST_ASSERT_EQUAL_FLOAT(0.0f, get_3d_tensor(cube, f32, 1, 0, 2));
    TEST_ASSERT_EQUAL_FLOAT(0.0f, get_3d_tensor(cube, f32, 1, 1, 0));
    TEST_ASSERT_EQUAL_FLOAT(0.0f, get_3d_tensor(cube, f32, 1, 1, 1));
    TEST_ASSERT_EQUAL_FLOAT(0.0f, get_3d_tensor(cube, f32, 1, 1, 2));

    for (u8 row = 0; row < cube->shape[0]; ++row)
    {
        printf("[");
        for (u8 col = 0; col < cube->shape[1]; ++col)
        {
            printf("[");
            for (u8 thd = 0; thd < cube->shape[2]; ++thd)
            {
                printf("%f ", get_3d_tensor(cube, f32, row, col, thd));
            }
            printf("]\n");
        }
        printf("]\n");
    }
    destroy_arena(&arena, NULL);

    destroy_arena(&arena, NULL);
}

void ones_creation(void)
{
    Arena* arena = NULL;
    create_arena(KiB(1), &arena, NULL);
    set_global_arena_allocator(arena, NULL);

    Tensor* hcube = NULL;
    create_ones_tensor(
        TINYMLL_F32,
        16,
        (i64[]){2, 2, 2, 2, 0},
        &hcube,
        get_global_arena_allocator(),
        NULL
    );

    TEST_ASSERT_EQUAL_FLOAT(1.0f, get_4d_tensor(hcube, f32, 0, 0, 0, 0));
    TEST_ASSERT_EQUAL_FLOAT(1.0f, get_4d_tensor(hcube, f32, 0, 0, 0, 1));
    TEST_ASSERT_EQUAL_FLOAT(1.0f, get_4d_tensor(hcube, f32, 0, 0, 1, 0));
    TEST_ASSERT_EQUAL_FLOAT(1.0f, get_4d_tensor(hcube, f32, 0, 0, 1, 1));
    TEST_ASSERT_EQUAL_FLOAT(1.0f, get_4d_tensor(hcube, f32, 0, 1, 0, 0));
    TEST_ASSERT_EQUAL_FLOAT(1.0f, get_4d_tensor(hcube, f32, 0, 1, 0, 1));
    TEST_ASSERT_EQUAL_FLOAT(1.0f, get_4d_tensor(hcube, f32, 0, 1, 1, 0));
    TEST_ASSERT_EQUAL_FLOAT(1.0f, get_4d_tensor(hcube, f32, 0, 1, 1, 1));
    TEST_ASSERT_EQUAL_FLOAT(1.0f, get_4d_tensor(hcube, f32, 1, 0, 0, 0));
    TEST_ASSERT_EQUAL_FLOAT(1.0f, get_4d_tensor(hcube, f32, 1, 0, 0, 1));
    TEST_ASSERT_EQUAL_FLOAT(1.0f, get_4d_tensor(hcube, f32, 1, 0, 1, 0));
    TEST_ASSERT_EQUAL_FLOAT(1.0f, get_4d_tensor(hcube, f32, 1, 0, 1, 1));
    TEST_ASSERT_EQUAL_FLOAT(1.0f, get_4d_tensor(hcube, f32, 1, 1, 0, 0));
    TEST_ASSERT_EQUAL_FLOAT(1.0f, get_4d_tensor(hcube, f32, 1, 1, 0, 1));
    TEST_ASSERT_EQUAL_FLOAT(1.0f, get_4d_tensor(hcube, f32, 1, 1, 1, 0));
    TEST_ASSERT_EQUAL_FLOAT(1.0f, get_4d_tensor(hcube, f32, 1, 1, 1, 1));

    for (u8 i = 0; i < hcube->shape[0]; ++i)
    {
        printf("[");
        for (u8 j = 0; j < hcube->shape[1]; ++j)
        {
            printf("[");
            for (u8 k = 0; k < hcube->shape[2]; ++k)
            {
                printf("[");
                for (u8 l = 0; l < hcube->shape[3]; ++l)
                {
                    printf("%f ", get_4d_tensor(hcube, f32, i, j, k, l));
                }
                printf("]\n");
            }
            printf("]\n");
        }
        printf("]\n");
    }
    destroy_arena(&arena, NULL);

    destroy_arena(&arena, NULL);
}

int main(void)
{
UNITY_BEGIN();
RUN_TEST(scalar_creation);
RUN_TEST(vector_creation);
RUN_TEST(matrix_creation);
RUN_TEST(cube_creation);
RUN_TEST(random_creation);
RUN_TEST(zeroes_creation);
RUN_TEST(ones_creation);
return UNITY_END();
}