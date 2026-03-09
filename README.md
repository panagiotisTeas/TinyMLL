# TinyMLL
A minimal machine learning library written in C, built for learning. TinyMLL implements core ML primitives from scratch — tensors, activations, layers, and losses — with a clean API and no heavy dependencies.

## Status
> Under active development. The API is unstable and subject to change.

| Component       | Status      |
|-----------------|-------------|
| Tensors         | In progress |
| ...             | ...         |

## Features
- Tensor operations in pure C (TODO)
- Multiple build targets (TODO)

## Project Structure
```
TinyMLL/
├── external/     # Third-party testing framework
├── include/      # Header files
├── src/          # C source files
│   ├── core/     # allocator, arena, error, random, tensor
│   └── utils/    # tensor_checks
├── tests/        # Test suite
└── CMakeLists.txt
```

## Building
TinyMLL uses CMake. Requires CMake 3.22+ and a C11-compatible compiler.

The default build type is **Debug**. Pass `-DCMAKE_BUILD_TYPE=Release` for an optimized build.
```bash
mkdir build && cd build
cmake ..
make
```

### Backend Selection

The backend is controlled via the `TINYMLL_BACKEND` CMake cache variable:

| Backend            | CMake Flag                              | Description                  |
|--------------------|-----------------------------------------|------------------------------|
| CPU (default)      | `-DTINYMLL_BACKEND=TINYMLL_CPU`         | Plain C, no extras           |
| CPU + SIMD         | `-DTINYMLL_BACKEND=TINYMLL_CPU_SIMD`    | Vectorized ops               |
| CPU + MT (+ SIMD)  | `-DTINYMLL_BACKEND=TINYMLL_CPU_MT`      | Parallel execution           |
| GPU                | `-DTINYMLL_BACKEND=TINYMLL_GPU`         | OpenCL backend               |

> SIMD, multithreading, and GPU backends are planned but not yet implemented.

### Library Type

TinyMLL can be built as a static or shared library via `TINYMLL_LIB_TYPE`:

| Type              | CMake Flag                        |
|-------------------|-----------------------------------|
| Static (default)  | `-DTINYMLL_LIB_TYPE=STATIC`       |
| Shared            | `-DTINYMLL_LIB_TYPE=SHARED`       |

### Tests

Tests are built by default. To disable:
```bash
cmake .. -DBUILD_TESTS=OFF
```

## Roadmap
- [x] Tensors
- [ ] Activations
- [ ] Layers
- [ ] Losses
- [ ] DataLoader
- [ ] AutoGrad
- [ ] Optimizers
- [ ] Training

## License
[MIT](__LICENSE__)