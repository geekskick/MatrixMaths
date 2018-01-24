//
//  main.cpp
//  MatrixMaths
//

#include <iostream>
#include "matrix.hpp"

int main(int argc, const char * argv[]) {
	
	matrix m = matrix::identity(4);

	std::cout << "Hello, World!\n";
	std::cout << m 		<< std::endl;
	std::cout << m * 4 	<< std::endl;
	
	matrix a({{0,1},{-8,-6}});
	matrix b(1,2);
	b[0] = {0};
	b[1] = {1};
	std::cout << "A*B = " << std::endl << a * b << std::endl;
	
	matrix lhs(2,2);
	lhs[0] = {1, 2};
	lhs[1] = {3, 4};
	std::cout << "lhs:" 		<< std::endl << lhs 				<< std::endl;
	std::cout << "det(lhs):" 	<< std::endl << lhs.determinant() 	<< std::endl << std::endl;
	std::cout << "adj(lhs):" 	<< std::endl << lhs.adj() 			<< std::endl;
	std::cout << "lhsT:" 		<< std::endl << lhs.transpose() 	<< std::endl;
	try{
		std::cout << "lhs^-1:" 	<< std::endl << lhs.inverse() 	<< std::endl;
	}
	catch (matrix_exception &e){
		std::cout << e.what() << std::endl;
	}
	
	matrix n(3,3);
	n[0] = {1,2,3};
	n[1] = {4,5,6};
	n[2] = {7,8,9};
	std::cout << "n:" 		<< std::endl << n 				<< std::endl;
	std::cout << "det(n):" 	<< std::endl << n.determinant() 	<< std::endl << std::endl;
	std::cout << "adj(n):" 	<< std::endl << n.adj() 		<< std::endl;
	std::cout << "nT:" 		<< std::endl << n.transpose() 	<< std::endl;
	std::cout << "nT * I"	<< std::endl << n.transpose() * matrix::identity(n.rows()) << std::endl;
	try{
		std::cout << "n^-1:" << std::endl << n.inverse() 	<< std::endl;
	}
	catch (matrix_exception &e){
		std::cout << e.what() << std::endl;
	}
	
	try{
		std::cout << "m * n:" << std::endl << m * n << std::endl;
	}
	catch (matrix_exception &e){
		std::cout << e.what() << std::endl;
	}
	std::vector<double> n_row = { 0, 1, 2, 3 };
	std::vector<double> n_col = { 0, 1 ,2, 3, 4 };
	
	m.add_row(n_row);
	std::cout << m << std::endl;

	m.add_col(n_col);
	std::cout << m << std::endl;
	
	try{
		std::cout << "Adding to m:" << std::endl << m.add_row(n_row) << std::endl;
	}
	catch(matrix_exception &e){
		std::cout << e.what() << std::endl;
	}
	
	matrix l(3,1);
	l[0] = { 1, 2, 3 };
	
	matrix r(4,3);
	r[0] = { 4 ,3, 2, 1 };
	r[1] = { 5, 4, 3, 2 };
	r[2] = { 6, 5, 4, 3 };
	
	try{
		std::cout << "r * l:" << std::endl << r * l << std::endl;
	}
	catch(matrix_exception &e){
		std::cout << e.what() << std::endl;
	}
	try{
		std::cout << "l * r:" << std::endl << l * r << std::endl;
	}
	catch(matrix_exception &e){
		std::cout << e.what() << std::endl;
	}
	
	matrix in_place({{4,3},{2,1}});
	std::cout << "in_place:" 		<< std::endl << in_place 				<< std::endl;
	std::cout << "det(in_place):" 	<< std::endl << in_place.determinant() 	<< std::endl << std::endl;
	std::cout << "adj(in_place):" 	<< std::endl << in_place.adj() 			<< std::endl;
	std::cout << "in_placeT:" 		<< std::endl << in_place.transpose() 	<< std::endl;
	std::cout << "in_placeT * I"	<< std::endl << in_place.transpose() * matrix::identity(in_place.rows()) << std::endl;
	try{
		std::cout << "in_place^-1:" << std::endl << in_place.inverse() 		<< std::endl;
	}
	catch (matrix_exception &e){
		std::cout << e.what() << std::endl;
	}
	return 0;
}
