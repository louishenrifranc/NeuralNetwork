========================================================================
    CONSOLE APPLICATION : NeuralNetwork Project Overview
========================================================================

AppWizard has created this NeuralNetwork application for you.

This file contains a summary of what you will find in each of the files that
make up your NeuralNetwork application.

TODO
	Choose the activation function
	Parallel as much
	Improve random
	Add regularization
	Get back the coefficient of the NN in a nice form
	Read the paper of Yann le Cun
/////////////////////////////////////////////////////////////////////////////

## Build with Armadillo

Armadillo is a C++ template library for linear algebra. It is built upon LAPACK and BLAS. It offers a simple API that is similar to that of Matlab.

1. Download the source code of Armadillo from here. Unzip the source code of Armadillo to a directory.

2. Create an environment variable named ARMADILLO_ROOT with a value of the Armadillo directory.

3. Armadillo requires LAPACK and BLAS libraries for any non-trivial matrix operation. To enable it to use these libraries, open $(ARMADILLO_ROOT)/include/armadillo_bits/config.hpp and uncomment the defines of ARMA_USE_LAPACK and ARMA_USE_BLAS.

4. To use Armadillo in your Visual C++ project, add $(ARMADILLO_ROOT)/include as an Include directory.

5. Since Armadillo source code uses LAPACK and BLAS, your project needs to link with these libraries. Armadillo ships with pre-built 32-bit .lib and .dll files for LAPACK and BLAS. Add $(ARMADILLO_ROOT)/examples/lib_win32 as Library directory to your project. Add blas_win32_MT.lib and lapack_win32_MT.lib as additional dependencies to your project.

6. Include the armadillo header file in your source code. Use the Armadillo classes and methods in your code. Remember to use the namespace arma:: Your code should compile to an EXE file without any further problems.

7. Copy the blas_win32_MT.dll and lapack_win32_MT.dll files from $(ARMADILLO_ROOT)/examples/lib_win32 to the directory that contains your EXE file. Your program should execute successfully now.