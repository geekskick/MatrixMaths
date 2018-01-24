//
//  matrix.hpp
//  MatrixMaths
//

#ifndef matrix_hpp
#define matrix_hpp

#include <iostream>
#include <vector>
#include <exception>
#include <numeric>
#include <valarray>

class matrix_exception : public std::exception{
public:
	matrix_exception(const std::string msg) : m_msg(msg) {}
	const char* what(void) const throw();
private:
	const std::string m_msg;
};

class matrix{
public:
	matrix(void)
	:	m_cdimension(0),
		m_rdimension(0),
		m_values(0, std::vector<double>(0, 0.0))
	{}
	
	matrix(const int row_dimension, const int col_dimension)
	: 	m_cdimension(col_dimension),
		m_rdimension(row_dimension),
		m_values(m_rdimension, std::vector<double>(m_cdimension, 0.0))
	{}
	
	matrix(const std::vector<std::vector<double>>& values)
	: 	m_cdimension((int)values[0].size()),
		m_rdimension((int)values.size()),
		m_values(values)
	{}
	
	~matrix(){}
	
	static matrix identity(const int dimension);
	void 	clear(void);
	void 	fill(const double value);
	matrix& add_row(std::vector<double> &values);
	matrix&	add_col(std::vector<double> &values);
	double 	determinant(void) 						const;
	int 	rows(void) 								const;
	int 	cols(void) 								const;
	std::vector<double> column(const int c) 		const;
	matrix 	transpose(void) 						const;
	matrix 	inverse(void) 							const;
	matrix 	adj(void) 								const;
	matrix 	cofactors(void) 						const;
	matrix 	minors(void) 							const;

	matrix 	operator*=	(const double& 	scalar	);
	matrix 	operator/=	(const double& 	scalar	);
	matrix& operator=	(const matrix& 	rhs		);
	matrix 	operator*=	(const matrix& 	rhs		);
	matrix 	operator+=	(const matrix& 	rhs		);
	matrix 	operator-=	(const matrix& 	rhs		);
	matrix 	operator-	(const matrix& 	rhs		) 	const;
	matrix 	operator*	(const double& 	scalar	) 	const;
	matrix 	operator+	(const matrix& 	rhs		) 	const;
	matrix 	operator/	(const double& 	scalar	) 	const;
	matrix 	operator*	(const matrix& 	rhs		) 	const;
	bool 	operator==	(const matrix& 	rhs		) 	const;
	bool 	operator!=	(const matrix& 	rhs		) 	const;
	std::vector<double>& operator[](const int x);
	
	friend std::ostream& operator<<(std::ostream& os, const matrix& mat){
		for(auto row : mat.m_values){
			os << " [ ";
			for(auto col : row){
				os << col << " ";
			}
			os << " ] " << std::endl;
		}
		return os;
	}
	
protected:
	int m_cdimension;
	int m_rdimension;
	std::vector<std::vector<double>> m_values;
	
	double recur_determinant(matrix sub_matrix) const;
	
};

#endif /* matrix_hpp */
