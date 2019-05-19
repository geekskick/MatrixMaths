//
//  matrix.hpp
//  MatrixMaths
//

#ifndef matrix_hpp
#define matrix_hpp

#include <exception>
#include <iostream>
#include <numeric>
#include <valarray>
#include <vector>

class matrix_exception : public std::exception {
public:
    matrix_exception(const std::string msg) : m_msg(msg) {}
    const char *what(void) const throw() { return (std::string("Matrix Exception: ") + m_msg).c_str(); }

private:
    const std::string m_msg;
};

template <typename T> class matrix {
public:
    matrix(void) : m_cdimension(0), m_rdimension(0), m_values(0, std::vector<T>(0, 0.0)) {}

    matrix(const int row_dimension, const int col_dimension)
        : m_cdimension(col_dimension), m_rdimension(row_dimension), m_values(m_rdimension, std::vector<T>(m_cdimension, 0.0)) {}

    matrix(const std::vector<std::vector<T>> &values) : m_cdimension((int)values[0].size()), m_rdimension((int)values.size()), m_values(values) {}

    ~matrix() {}

    static matrix identity(const int dimension) {
        matrix result(dimension, dimension);
        for (int i = 0; i < dimension; i++) {
            result[i][i] = 1;
        }
        return result;
    }

    void clear(void) { fill(0); }

    void fill(const T value) {
        for (int r = 0; r < m_rdimension; r++) {
            for (int c = 0; c < m_cdimension; c++) {
                m_values[r][c] = value;
            }
        }
    }

    matrix &add_row(std::vector<T> &values) {
        if (values.size() != m_cdimension) {
            throw matrix_exception("Row to append isn't the same size as the matrix dimensions [" + std::to_string(values.size()) + " vs. " +
                                   std::to_string(m_cdimension) + "]");
        }
        m_values.push_back(values);
        m_rdimension++;
        return *this;
    }

    matrix &add_col(std::vector<T> &values) {
        if (values.size() != m_rdimension) {
            throw matrix_exception("Column to append isn't the same size as the matrix dimensions [" + std::to_string(values.size()) + " vs. " +
                                   std::to_string(m_rdimension) + "]");
        }
        for (int row = 0; row < m_rdimension; row++) {
            m_values[row].push_back(values[row]);
        }
        m_cdimension++;
        return *this;
    }

    double determinant(void) const {
        if (m_cdimension != m_rdimension) {
            throw matrix_exception("Rows and Columns must be equal to get the determinant");
        }
        return recur_determinant(*this);
    }

    int rows(void) const { return m_rdimension; }

    int cols(void) const { return m_cdimension; }

    std::vector<T> column(const int c) const {
        std::vector<T> col;
        for (int r = 0; r < rows(); r++) {
            col.push_back(m_values[r][c]);
        }
        return col;
    }

    matrix transpose(void) const {
        matrix result(m_cdimension, m_rdimension);
        for (int r = 0; r < m_rdimension; r++) {
            for (int c = 0; c < m_cdimension; c++) {
                result[c][r] = m_values[r][c];
            }
        }
        return result;
    }

    matrix inverse(void) const {
        const double det = determinant();
        if (det == 0.0) {
            throw matrix_exception("Unable to invert as the determinant is 0");
        }
        return (adj() / det);
    }

    matrix adj(void) const {
        if (m_cdimension == 2 && m_rdimension == 2) {
            matrix result = *this;
            result[0][0] = m_values[1][1];
            result[1][1] = m_values[0][0];
            // std::cout << result.cofactors();
            return result.cofactors();
        }
        return minors().cofactors().transpose();
    }

    matrix cofactors(void) const {
        matrix result = *this;
        for (int r = 1; r <= m_rdimension; r++) {
            for (int c = r % 2; c < m_cdimension; c += 2) {
                // std::cout << "[" << r-1 << ", " << c << "]" << std::endl;
                result.m_values[r - 1][c] *= -1;
            }
        }
        return result;
    }

    matrix minors(void) const {
        matrix result(m_cdimension, m_rdimension);
        for (int c = 0; c < m_cdimension; c++) {
            for (int r = 0; r < m_rdimension; r++) {
                matrix temp(m_cdimension - 1, m_rdimension - 1);

                // populate determinant matrix
                for (int ic = 0; ic < m_cdimension - 1; ic++) {
                    for (int ir = 0; ir < m_rdimension - 1; ir++) {
                        // std::cout << "[" << (ir >= r ? ir + 1 : ir) << ", " << (ic >= c ? ic + 1 : ic) << "]" <<std::endl;
                        temp[ir][ic] = m_values[ir >= r ? ir + 1 : ir][ic >= c ? ic + 1 : ic];
                    }
                }
                // std::cout << "matrix of minors calculatation: " << temp << std::endl;
                result[r][c] = temp.determinant();
            }
        }
        return result;
    }

    matrix operator*=(const double &scalar) {
        for (int r = 0; r < m_rdimension; r++) {
            for (int c = 0; c < m_cdimension; c++) {
                m_values[r][c] *= scalar;
            }
        }
        return *this;
    }

    matrix operator/=(const double &scalar) {
        for (int r = 0; r < m_rdimension; r++) {
            for (int c = 0; c < m_cdimension; c++) {
                m_values[r][c] /= scalar;
            }
        }
        return *this;
    }

    matrix &operator=(const matrix &rhs) {
        if (this != &rhs) {
            this->m_values = rhs.m_values;
            this->m_cdimension = rhs.m_cdimension;
            this->m_rdimension = rhs.m_rdimension;
        }
        return *this;
    }

    matrix operator*=(const matrix &rhs) {
        matrix result = *this * rhs;
        *this = result;
        return *this;
    }

    matrix operator+=(const matrix &rhs) {
        if (rhs.m_rdimension != m_rdimension || rhs.m_cdimension != m_cdimension) {
            throw matrix_exception("Dimensions don't match for += operator");
        }

        for (int r = 0; r < m_rdimension; r++) {
            for (int c = 0; c < m_cdimension; c++) {
                m_values[r][c] = m_values[r][c] + rhs.m_values[r][c];
            }
        }
        return *this;
    }

    matrix operator-=(const matrix &rhs) {
        if (rhs.m_rdimension != m_rdimension || rhs.m_cdimension != m_cdimension) {
            throw matrix_exception("Dimensions don't match for -= operator");
        }

        for (int r = 0; r < m_rdimension; r++) {
            for (int c = 0; c < m_cdimension; c++) {
                m_values[r][c] = m_values[r][c] - rhs.m_values[r][c];
            }
        }
        return *this;
    }

    matrix operator-(const matrix &rhs) const {
        if (rhs.m_rdimension != m_rdimension || rhs.m_cdimension != m_cdimension) {
            throw matrix_exception("Dimensions don't match for - operator");
        }

        matrix result(rhs.m_cdimension, rhs.m_rdimension);
        for (int r = 0; r < m_rdimension; r++) {
            for (int c = 0; c < m_cdimension; c++) {
                result.m_values[r][c] = m_values[r][c] - rhs.m_values[r][c];
            }
        }
        return result;
    }

    matrix operator*(const double &scalar) const {
        matrix result = *this;
        for (int r = 0; r < m_rdimension; r++) {
            for (int c = 0; c < m_cdimension; c++) {
                result.m_values[r][c] *= scalar;
            }
        }
        return result;
    }

    matrix operator+(const matrix &rhs) const {
        if (rhs.m_rdimension != m_rdimension || rhs.m_cdimension != m_cdimension) {
            throw matrix_exception("Dimensions don't match for + operator");
        }

        matrix result(rhs.m_cdimension, rhs.m_rdimension);
        for (int r = 0; r < m_rdimension; r++) {
            for (int c = 0; c < m_cdimension; c++) {
                result.m_values[r][c] = m_values[r][c] + rhs.m_values[r][c];
            }
        }
        return result;
    }

    matrix operator/(const double &scalar) const {
        matrix result = *this;
        for (int r = 0; r < m_rdimension; r++) {
            for (int c = 0; c < m_cdimension; c++) {
                result.m_values[r][c] /= scalar;
            }
        }
        return result;
    }

    matrix operator*(const matrix &rhs) const {
        if (m_cdimension != rhs.m_rdimension) {
            throw matrix_exception("Dimensions not compatible for * operator [" + std::to_string(m_cdimension) + " vs. " + std::to_string(rhs.m_cdimension) +
                                   "]");
        }
        matrix result(rhs.cols(), rows());
        for (int r = 0; r < result.rows(); r++) {
            const std::valarray<T> first_matrix_row(m_values[r].data(), m_values[r].size());

            for (int c = 0; c < result.cols(); c++) {
                const auto column = rhs.column(c);
                const std::valarray<T> second_matrix_column(column.data(), column.size());
                const std::valarray<T> mulitplier = first_matrix_row * second_matrix_column;
                result[r][c] = mulitplier.sum();
            }
        }
        return result;
    }

    bool operator==(const matrix &rhs) const {
        if (rhs.m_rdimension != m_rdimension || rhs.m_cdimension != m_cdimension) {
            return false;
        }
        if (this != &rhs) {
            for (int r = 0; r < m_rdimension; r++) {
                for (int c = 0; c < m_cdimension; c++) {
                    if (!(m_values[r][c] == rhs.m_values[r][c])) {
                        return false;
                    }
                }
            }
        }
        return true;
    }

    bool operator!=(const matrix &rhs) const { return !(rhs == *this); }
    std::vector<T> &operator[](const int x) { return m_values[x]; }
    const std::vector<T> &operator[](const int x) const { return m_values[x]; }

    friend std::ostream &operator<<(std::ostream &os, const matrix &mat) {
        for (auto row : mat.m_values) {
            os << " [ ";
            for (auto col : row) {
                os << col << " ";
            }
            os << " ] " << std::endl;
        }
        return os;
    }

protected:
    int m_cdimension;
    int m_rdimension;
    std::vector<std::vector<T>> m_values;

    double recur_determinant(matrix sub_matrix) const {
        if (sub_matrix.rows() == 2) {
            return (sub_matrix[0][0] * sub_matrix[1][1]) - (sub_matrix[1][0] * sub_matrix[0][1]);
        }
        double sum = 0;
        for (int s = 0; s < sub_matrix.m_cdimension; s++) {
            matrix temp(sub_matrix.m_cdimension - 1, sub_matrix.m_rdimension - 1);
            for (int r = 0; r < sub_matrix.m_rdimension - 1; r++) {
                for (int c = 0; c < sub_matrix.m_cdimension - 1; c++) {
                    int upper_c = (c >= s) ? (c + 1) : c;
                    int upper_r = r + 1;
                    temp[r][c] = sub_matrix[upper_r][upper_c];
                }
            }
            // std::cout << "Determinant temp" << std::endl << sub_matrix[0][s] << "x" << temp << std::endl;
            if (s % 2 == 0) {
                sum += recur_determinant(temp) * sub_matrix[0][s];
            } else {
                sum -= recur_determinant(temp) * sub_matrix[0][s];
            }
        }
        return sum;
    }
};
#endif
