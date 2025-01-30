[![SIDEMADE CI/CD](https://github.com/heidrifx/testing-boost-exercise/actions/workflows/sidemade.yaml/badge.svg)](https://github.com/heidrifx/testing-boost-exercise/actions/workflows/sidemade.yaml)

# SIDEMADE - Simple Dense Matrix Decomposition

A simple demo code to read dense matrices from files and solve linear systems with them.

## Folder Structure

- `cmake`: Third-party CMake modules
- `CMakeLists.txt`: CMake configuration file
- `data`: Various dense matrices
  - `config.yml`: SIDEMADE configuration file
  - `m3.csv`: A 3x3 matrix with randomly generated entries
  - `m10.csv`: An ill-conditioned 10x10 [Hilbert matrix](https://math.nist.gov/MatrixMarket/deli/Hilbert/)
  - `m50.csv`: A 50x50 FEM **mass matrix** for a [1D problem with Lagrange basis](https://people.sc.fsu.edu/~jburkardt/m_src/fem1d_lagrange/fem1d_lagrange.html)
  - `m100.csv`: A 100x100 FEM **stiffness matrix** for a [1D problem with Lagrange basis](https://people.sc.fsu.edu/~jburkardt/m_src/fem1d_lagrange/fem1d_lagrange.html)
  - `m250.csv`: A 250x250 matrix with randomly generated entries
- `LICENSE`: MIT license file
- `src`: Source code
  - `Configuration.hpp/cpp`: A yaml configuration reader
  - `MatrixSolver.hpp/cpp`: A convenience hull to solve dense matrix systems by matrix decompositions
  - `matrixIO.hpp/cpp`: IO methods to read Eigen matrices from or write them to csv files
  - `main.cpp`: Main file
- `tests`: Unit tests
  
## Building

You can build the code using CMake:

```bash
$ mkdir build
$ cd build
$ cmake ..
$ make -j
```

### Dependencies

- A C++ compiler supporting at least C++11
- [CMake](https://cmake.org/): At least version 3.12
- [Eigen](https://eigen.tuxfamily.org/index.php): At least version 3.2
- [yaml-cpp](https://github.com/jbeder/yaml-cpp): At least version 0.6

For unit testing moreover:

- [Boost Unit Test Framework](https://www.boost.org/doc/libs/1_78_0/libs/test/doc/html/index.html): Should work with most recent versions. The code was tested with 1.71.

## Running

You need to call the code with a configuration file, e.g. `config.yml`.
If you call the program from the build folder:

```bash
$ ./sidemade ../data/config.yml
```

### Configuration

An example configuration file:

```yml
DecompositionType: QR
MatrixFileName: ../data/m250.csv
MatrixSize: 250
```

## Tools

### Formatting

You can format the code base using [clang-format](https://clang.llvm.org/docs/ClangFormat.html):

```bash
$ clang-format -i src/*
```
