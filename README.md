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

I used the library when I didn't have access to MATLAB and didn't want to do matrix operations by hand.

## Build
There are no dependancies.
```
> mkdir build
> cd build
> cmake .. 
```

## Use
The matrix library is built into the `build/src` directory, along with it's interface in `matrix.hpp`. This is linked using cmake's `target_include_directories(matrix PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})` command, so when you build your application using the command `target_link_libraries(MyApp LINK_PUBLIC matrix)` and the header file will be added to your application's include path.

## Test
Run tests from the build directory using 
```
./test/matrix_test
```

