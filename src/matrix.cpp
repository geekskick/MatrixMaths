//
//  matrix.cpp
//  MatrixMaths
//

#include "matrix.hpp"

const char* matrix_exception::what(void) const throw(){
	return (std::string("Matrix Exception: ") + m_msg).c_str();
}

std::vector<double>& matrix::operator[](const int x){
	return m_values[x];
}

matrix matrix::identity(const int dimension){
	matrix result(dimension, dimension);
	for(int i = 0; i < dimension; i++){
		result[i][i] = 1;
	}
	return result;
}

void matrix::clear(void){
	fill(0);
}

void matrix::fill(const double value){
	for( int r = 0; r < m_rdimension; r++){
		for(int c = 0; c < m_cdimension; c++){
			m_values[r][c] = value;
		}
	}
}

matrix matrix::operator+(const matrix& rhs) const{
	if(rhs.m_rdimension != m_rdimension ||
	   rhs.m_cdimension != m_cdimension) { throw matrix_exception("Dimensions don't match for + operator") ;}
	
	matrix result(rhs.m_cdimension, rhs.m_rdimension);
	for(int r = 0; r < m_rdimension; r++){
		for(int c = 0; c < m_cdimension; c++){
			result.m_values[r][c] = m_values[r][c] + rhs.m_values[r][c];
		}
	}
	return result;
}

double matrix::determinant(void) const{
	if(m_cdimension != m_rdimension) { throw matrix_exception("Rows and Columns must be equal to get the determinant");}
	return recur_determinant(*this);
}

matrix matrix::operator+=(const matrix& rhs){
	if(rhs.m_rdimension != m_rdimension ||
	   rhs.m_cdimension != m_cdimension) { throw matrix_exception("Dimensions don't match for += operator") ;}
	
	for(int r = 0; r < m_rdimension; r++){
		for(int c = 0; c < m_cdimension; c++){
			m_values[r][c] = m_values[r][c] + rhs.m_values[r][c];
		}
	}
	return *this;
}

matrix matrix::operator-=(const matrix& rhs){
	if(rhs.m_rdimension != m_rdimension ||
	   rhs.m_cdimension != m_cdimension) { throw matrix_exception("Dimensions don't match for -= operator") ;}
	
	for(int r = 0; r < m_rdimension; r++){
		for(int c = 0; c < m_cdimension; c++){
			m_values[r][c] = m_values[r][c] - rhs.m_values[r][c];
		}
	}
	return *this;
}

matrix matrix::operator-(const matrix& rhs) const{
	if(rhs.m_rdimension != m_rdimension ||
	   rhs.m_cdimension != m_cdimension) { throw matrix_exception("Dimensions don't match for - operator") ;}
	
	matrix result(rhs.m_cdimension, rhs.m_rdimension);
	for(int r = 0; r < m_rdimension; r++){
		for(int c = 0; c < m_cdimension; c++){
			result.m_values[r][c] = m_values[r][c] - rhs.m_values[r][c];
		}
	}
	return result;
}
matrix matrix::operator*(const double& scalar) const{
	matrix result = *this;
	for(int r = 0; r < m_rdimension; r++){
		for(int c = 0; c < m_cdimension; c++){
			result.m_values[r][c] *= scalar;
		}
	}
	return result;
}

matrix matrix::operator*=(const double& scalar){
	for(int r = 0; r < m_rdimension; r++){
		for(int c = 0; c < m_cdimension; c++){
			m_values[r][c] *= scalar;
		}
	}
	return *this;
}

matrix matrix::operator/(const double& scalar) const{
	matrix result = *this;
	for(int r = 0; r < m_rdimension; r++){
		for(int c = 0; c < m_cdimension; c++){
			result.m_values[r][c] /= scalar;
		}
	}
	return result;
}

matrix matrix::operator/=(const double& scalar){
	for(int r = 0; r < m_rdimension; r++){
		for(int c = 0; c < m_cdimension; c++){
			m_values[r][c] /= scalar;
		}
	}
	return *this;
}
matrix& matrix::operator=(const matrix&rhs){
	if(this != & rhs){
		this->m_values = rhs.m_values;
		this->m_cdimension = rhs.m_cdimension;
		this->m_rdimension = rhs.m_rdimension;
	}
	return *this;
}

bool matrix::operator==(const matrix&rhs) const {
	if(rhs.m_rdimension != m_rdimension ||
	   rhs.m_cdimension != m_cdimension) {
		return false;
	}
	if(this != &rhs){
		for(int r = 0; r < m_rdimension; r++){
			for(int c = 0; c < m_cdimension; c++){
				if(!(m_values[r][c] == rhs.m_values[r][c])){
					return false;
				}
			}
		}
	}
	return true;
}

bool matrix::operator!=(const matrix&rhs) const {
	return !(*this == rhs);
}


matrix matrix::operator*(const matrix& rhs) const{
	if(m_cdimension != rhs.m_rdimension) { throw matrix_exception("Dimensions not compatible for * operator [" + std::to_string(m_cdimension) + " vs. " + std::to_string(rhs.m_cdimension) + "]"); }
	matrix result(rhs.cols(), rows());
	for(int r = 0; r < result.rows(); r++){
		const std::valarray<double> first_matrix_row(m_values[r].data(), m_values[r].size());
		
		for(int c = 0; c < result.cols(); c++){
			const auto 					column 		= rhs.column(c);
			const std::valarray<double> 	second_matrix_column(column.data(), column.size());
			const std::valarray<double> 	mulitplier 	= first_matrix_row * second_matrix_column;
			result[r][c] = mulitplier.sum();
		}
	}
	return result;
}

matrix matrix::operator*=(const matrix& rhs){
	matrix result = *this * rhs;
	*this = result;
	return *this;
}

int matrix::rows(void) const {
	return m_rdimension;
}

int matrix::cols(void) const {
	return m_cdimension;
}
std::vector<double> matrix::column(const int c) const {
	std::vector<double> col;
	for(int r = 0; r < rows(); r++){
		col.push_back(m_values[r][c]);
	}
	return col;
}

matrix matrix::transpose(void) const{
	matrix result(m_cdimension, m_rdimension);
	for(int r = 0; r < m_rdimension; r++){
		for(int c = 0; c < m_cdimension; c++){
			result[c][r] = m_values[r][c];
		}
	}
	return result;
}

matrix matrix::inverse(void) const {
	const double det = determinant();
	if(det == 0.0) { throw matrix_exception("Unable to invert as the determinant is 0"); }
	return (adj()/det);
}

matrix matrix::adj(void) const{
	if(m_cdimension == 2 && m_rdimension == 2){
		matrix result = *this;
		result[0][0] = m_values[1][1];
		result[1][1] = m_values[0][0];
		//std::cout << result.cofactors();
		return result.cofactors();
	}
	return minors().cofactors().transpose();
}

double matrix::recur_determinant(matrix sub_matrix) const{
	if(sub_matrix.rows() == 2){
		return (sub_matrix[0][0] * sub_matrix[1][1]) - (sub_matrix[1][0]*sub_matrix[0][1]);
	}
	double sum = 0;
	for(int s = 0; s < sub_matrix.m_cdimension; s++){
		matrix temp(sub_matrix.m_cdimension-1, sub_matrix.m_rdimension-1);
		for(int r = 0; r < sub_matrix.m_rdimension - 1; r++){
			for(int c = 0; c < sub_matrix.m_cdimension -1; c++){
				int upper_c = (c >= s) ? (c + 1) : c;
				int upper_r = r + 1;
				temp[r][c] = sub_matrix[upper_r][upper_c];
			}
		}
		//std::cout << "Determinant temp" << std::endl << sub_matrix[0][s] << "x" << temp << std::endl;
		if(s % 2 == 0 ){sum += recur_determinant(temp) * sub_matrix[0][s];}
		else{sum -= recur_determinant(temp) * sub_matrix[0][s];}
		
	}
	return sum;
}

matrix matrix::minors(void) const {
	matrix result(m_cdimension, m_rdimension);
	for(int c = 0; c < m_cdimension; c++){
		for(int r = 0; r < m_rdimension; r++){
			matrix temp(m_cdimension-1, m_rdimension-1);
			
			// populate determinant matrix
			for(int ic = 0; ic < m_cdimension -1; ic++){
				for(int ir = 0; ir < m_rdimension -1; ir++){
					//std::cout << "[" << (ir >= r ? ir + 1 : ir) << ", " << (ic >= c ? ic + 1 : ic) << "]" <<std::endl;
					temp[ir][ic] = m_values[ir >= r ? ir + 1 : ir][ic >= c ? ic + 1 : ic];
				}
			}
			//std::cout << "matrix of minors calculatation: " << temp << std::endl;
			result[r][c] = temp.determinant();
		}
	}
	return result;
}

matrix matrix::cofactors(void) const{
	matrix result = *this;
	for(int r = 1; r <= m_rdimension; r++){
		for(int c = r % 2; c < m_cdimension; c+=2){
			//std::cout << "[" << r-1 << ", " << c << "]" << std::endl;
			result.m_values[r-1][c] *= -1;
		}
	}
	return result;
}

matrix& matrix::add_row(std::vector<double> &values){
	if(values.size() != m_cdimension) { throw matrix_exception("Row to append isn't the same size as the matrix dimensions [" + std::to_string(values.size()) + " vs. " + std::to_string(m_cdimension) + "]"); }
	m_values.push_back(values);
	m_rdimension++;
	return *this;
}
matrix& matrix::add_col(std::vector<double> &values){
	if(values.size() != m_rdimension) { throw matrix_exception("Column to append isn't the same size as the matrix dimensions [" + std::to_string(values.size()) + " vs. " + std::to_string(m_rdimension) + "]"); }
	for(int row = 0; row < m_rdimension; row++){
		m_values[row].push_back(values[row]);
	}
	m_cdimension++;
	return *this;
}
