#pragma once

#include <array>
#include <Math/Tuple.hpp>

/**
 * @brief Template for a square matrix of size N
 *
 */
template <std::size_t N = 4>
class Matrix
{
public:
    /**
     * @brief The matrix size, which can be referenced
     *
     */
    static constexpr std::size_t SIZE = N;

    /**
     * @brief Construct a zero-initialized matrix
     *
     */
    Matrix();

    /**
     * @brief Construct a matrix with user-defined values
     *
     * @param init_values The array of (N*N) initial values
     */
    Matrix(const std::array<double, N * N> &init_values);

    /**
     * @brief Element access operator, read-only
     *
     * @param row The row index
     * @param col The column index
     * @return double The accessed element
     */
    double operator()(std::size_t row, std::size_t col) const;

    /**
     * @brief Element access operator, by reference
     *
     * @param row The row index
     * @param col The column index
     * @return double& The accessed element
     */
    double &operator()(std::size_t row, std::size_t col);

    /**
     * @brief Friend function declaration; allow component access for
     * convenience
     *
     */
    friend Tuple operator*(const Matrix<4> &, const Tuple &);

private:
    /**
     * @brief An array containing the matrix's values
     *
     */
    std::array<std::array<double, N>, N> values;
};

/**
 * @brief The identity matrix for size N = 4
 *
 */
extern const Matrix<4> IDENTITY;

/**
 * @brief Overload the == operator
 *
 * @tparam N The size of the matrix
 * @param lhs The left-hand side matrix
 * @param rhs The right-hand side matrix
 * @return true If all corresponding components are equal
 * @return false If any corresponding components are not equal
 */
template <std::size_t N>
bool operator==(const Matrix<N> &lhs, const Matrix<N> &rhs);

/**
 * @brief Overload the != operator
 *
 * @tparam N The size of the matrix
 * @param lhs The left-hand side matrix
 * @param rhs The right-hand side matrix
 * @return true If any corresponding components are not equal
 * @return false If all corresponding components are equal
 */
template <std::size_t N>
bool operator!=(const Matrix<N> &lhs, const Matrix<N> &rhs);

/**
 * @brief Overload the * operator to perform matrix multiplication
 *
 * @param lhs The left-hand side matrix
 * @param rhs The right-hand side matrix
 * @return Matrix<4> The product matrix
 */
Matrix<4> operator*(const Matrix<4> &lhs, const Matrix<4> &rhs);

/**
 * @brief Overload the * operator to multiply a matrix by a tuple
 *
 * @param matrix The matrix to be multiplied
 * @param tuple The tuple to be multiplied
 * @return Tuple The resulting tuple
 */
Tuple operator*(const Matrix<4> &matrix, const Tuple &tuple);

/**
 * @brief Create a matrix that is the transpose of the given matrix
 *
 * @param matrix The matrix to be transposed
 * @return Matrix<4> The transposed matrix
 */
Matrix<4> transpose(const Matrix<4> &matrix);

/**
 * @brief Calculate the determinant of a 2x2 matrix
 *
 * @param matrix The input matrix
 * @return double The determinant value
 */
double determinant(const Matrix<2> &matrix);

/**
 * @brief Calculate the determinant of an NxN matrix
 *
 * @tparam N The size of the matrix
 * @param matrix The input matrix
 * @return double The determinant value
 * @note The determinant is calculated using the cofactor expansion method.
 */
template <std::size_t N>
double determinant(const Matrix<N> &matrix);

/**
 * @brief Create a submatrix by removing the specified row and column
 *
 * @tparam N The size of the matrix
 * @param matrix The input matrix
 * @param row The row index to be removed
 * @param col The column index to be removed
 * @return Matrix<N - 1> The resulting submatrix
 */
template <std::size_t N>
Matrix<N - 1> submatrix(
    const Matrix<N> &matrix, std::size_t row, std::size_t col);

/**
 * @brief Calculate the minor of a matrix at the specified row and column
 *
 * @tparam N The size of the matrix
 * @param matrix The input matrix
 * @param row The row index
 * @param col The column index
 * @return double The minor value
 */
template <std::size_t N>
double minor(const Matrix<N> &matrix, std::size_t row, std::size_t col);

/**
 * @brief Calculate the cofactor of a matrix at the specified row and column
 *
 * @tparam N The size of the matrix
 * @param matrix The input matrix
 * @param row The row index
 * @param col The column index
 * @return double The cofactor value
 */
template <std::size_t N>
double cofactor(const Matrix<N> &matrix, std::size_t row, std::size_t col);

/**
 * @brief Calculate the inverse of a 4x4 matrix
 *
 * @param matrix The input matrix
 * @return Matrix<4> The inverse matrix
 * @throw std::invalid_argument If the matrix is not invertible
 */
Matrix<4> inverse(const Matrix<4> &matrix);
