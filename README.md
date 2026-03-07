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
├── tests/        # Test suite
└── CMakeLists.txt
```

## Building

TinyMLL uses CMake. Requires CMake 3.22+ and a C11-compatible compiler.

### Default (CPU)

```bash
mkdir build && cd build
cmake ..
make
```

### Build Targets

> SIMD, multithreading, and GPU targets are planned but not yet available.

| Target            | CMake Flag              | Description                           |
|-------------------|-------------------------|---------------------------------------|
| CPU               | —                       | Plain C, no extras                    |
| CPU + SIMD        | `-DTINYMLL_CPU_SIMD=ON` | Vectorized ops                        |
| CPU + MT (+ SIMD) | `-DTINYMLL_CPU_MT=ON`   | Parallel execution (+ Vectorized ops) |
| GPU               | `-DTINYMLL_GPU=ON`      | OpenCL backend                        |

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

[MIT](LICENSE)