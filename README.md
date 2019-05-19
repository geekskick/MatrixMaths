# Matrix Library
The matrix library allows for some matrix operations to be performed. 

* Add
* Subtract
* Multiply
* Divide
* Test for equality and inequality
* Invert
* Transpose
* Find the Adjunct
* Find the Determinant
* Find the cofactors
* Add a row or column
* Stream the matrix to stdout

I used the library when I didn't have access to MATLAB and didn't want to do matrix operations by hand.

## Usage

```c++
// Make a 2x2 identity matrix.
matrix m = matrix::identity(2);

// Add a row to the matrix
std::vector<double> coeffs = { 0.5, 4 };
m.add_row(coeffs);

// Add a column to the matrix
// Note the matrix is currently a 3x2, so the column needs to have 3 items.
coeffs.emplace_back(8.0);
m.add_col(coeffs);

// Transpose the matrix
// Note the .transpose() method is const, it doesn't alter the contents of the matrix.
m = m.transpose();

// Find the determinant
// Note the .determinant() method is const, it doesn't alter the contents of the matrix.
const double det = m.determinant();

std::cout << m << "Determinant is " << det << std::endl;
```

### Exceptions

If you try to do something which is illegal a `matrix_exception` will be thrown. Using it's `.what()` method will give a clue as to what was illegal.

Example:
```c++
matrix m = matrix::identity(2);
try{
    m += matrix::identity(4);
}
catch(matrix_exception &e){
    std::cerr << e.what() << std::endl;
}
```

Gives the output: `Matrix Exception: Dimensions not compatible for * operator [2 vs. 4]`.

## Build
There are no dependancies.
```
> mkdir build
> cd build
> cmake .. 
```

## Including

The matrix library is in the `build/src` directory, in it's interface `matrix.hpp`.

## Test

Run tests from the build directory using 
```
make test
```
The tests are run using the `catch2` tool's header: `catch.hpp`.
