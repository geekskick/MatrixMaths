//
//  main.cpp
//  MatrixMaths
//

#include <iostream>
#include "matrix.hpp"

int main(int argc, const char * argv[]) {
	
	auto m = matrix<double>::identity(2);

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

	m = matrix<double>::identity(2);
	
	try{
		m *= matrix<double>::identity(4);
	}
	catch (matrix_exception &e){
		std::cerr << e.what() << std::endl;
	}
	return 0;
}
