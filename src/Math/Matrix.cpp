#include <stdexcept>
#include <Float_compare.hpp>
#include <Math/Matrix.hpp>

namespace
{
    bool is_odd(std::size_t num)
    {
        return num % 2 == 1;
    }
};

const Matrix<4> IDENTITY({1, 0, 0, 0,
                          0, 1, 0, 0,
                          0, 0, 1, 0,
                          0, 0, 0, 1});

template <std::size_t N>
Matrix<N>::Matrix() : values{{0}}
{
}

template <std::size_t N>
Matrix<N>::Matrix(const std::array<double, N * N> &init_values)
{
    std::size_t count = 0;
    for (auto &row : values)
    {
        for (auto &value : row)
        {
            value = init_values[count++];
        }
    }
}

template <std::size_t N>
double Matrix<N>::operator()(std::size_t row, std::size_t col) const
{
    return values[row][col];
}

template <std::size_t N>
double &Matrix<N>::operator()(std::size_t row, std::size_t col)
{
    return values[row][col];
}

template <std::size_t N>
bool operator==(const Matrix<N> &lhs, const Matrix<N> &rhs)
{
    bool is_equal = true;
    for (std::size_t row = 0; is_equal && row < N; ++row)
    {
        for (std::size_t col = 0; is_equal && col < N; ++col)
        {
            is_equal = float_equals(lhs(row, col), rhs(row, col));
        }
    }

    return is_equal;
}

template <std::size_t N>
bool operator!=(const Matrix<N> &lhs, const Matrix<N> &rhs)
{
    return !(lhs == rhs);
}

Matrix<4> operator*(const Matrix<4> &lhs, const Matrix<4> &rhs)
{
    auto M = Matrix<4>();

    for (std::size_t row = 0; row < Matrix<4>::SIZE; ++row)
    {
        for (std::size_t col = 0; col < Matrix<4>::SIZE; ++col)
        {
            M(row, col) = lhs(row, 0) * rhs(0, col) +
                          lhs(row, 1) * rhs(1, col) +
                          lhs(row, 2) * rhs(2, col) +
                          lhs(row, 3) * rhs(3, col);
        }
    }

    return M;
}

Tuple operator*(const Matrix<4> &matrix, const Tuple &tuple)
{
    return Tuple(dot(Tuple(matrix.values[0]), tuple),
                 dot(Tuple(matrix.values[1]), tuple),
                 dot(Tuple(matrix.values[2]), tuple),
                 dot(Tuple(matrix.values[3]), tuple));
}

Matrix<4> transpose(const Matrix<4> &matrix)
{
    Matrix<4> transposed(matrix);

    for (std::size_t i = 0; i < Matrix<4>::SIZE; ++i)
    {
        for (std::size_t j = i; j < Matrix<4>::SIZE; ++j)
        {
            std::swap(transposed(i, j), transposed(j, i));
        }
    }

    return transposed;
}

double determinant(const Matrix<2> &matrix)
{
    return matrix(0, 0) * matrix(1, 1) - matrix(0, 1) * matrix(1, 0);
}

template <std::size_t N>
double determinant(const Matrix<N> &matrix)
{
    double result = 0;

    for (std::size_t col = 0; col < N; ++col)
    {
        result += matrix(0, col) * cofactor(matrix, 0, col);
    }

    return result;
}

template <std::size_t N>
Matrix<N - 1> submatrix(
    const Matrix<N> &matrix, std::size_t row, std::size_t col)
{
    std::array<double, (N - 1) * (N - 1)> vals{};

    auto val_it = vals.begin();
    for (std::size_t i = 0; i < N; ++i)
    {
        if (i != row)
        {
            for (std::size_t j = 0; j < N; ++j)
            {
                if (j != col)
                {
                    *(val_it++) = matrix(i, j);
                }
            }
        }
    }

    return Matrix<N - 1>(vals);
}

template <std::size_t N>
double minor(const Matrix<N> &matrix, std::size_t row, std::size_t col)
{
    return determinant(submatrix(matrix, row, col));
}

template <std::size_t N>
double cofactor(const Matrix<N> &matrix, std::size_t row, std::size_t col)
{
    return (is_odd(row + col) ? -1 : 1) * minor(matrix, row, col);
}

Matrix<4> inverse(const Matrix<4> &matrix)
{
    const auto DET = determinant(matrix);
    if (float_equals(DET, 0))
    {
        throw std::invalid_argument(
            "Attempted to get inverse of non-invertible matrix");
    }

    Matrix result;
    for (std::size_t row = 0; row < Matrix<4>::SIZE; ++row)
    {
        for (std::size_t col = 0; col < Matrix<4>::SIZE; ++col)
        {
            result(col, row) = cofactor(matrix, row, col) / DET;
        }
    }

    return result;
}

// Explicit instantiation for 4x4, 3x3, & 2x2 matrices
template class Matrix<4>;
template class Matrix<3>;
template class Matrix<2>;
template bool operator==(const Matrix<4> &, const Matrix<4> &);
template bool operator==(const Matrix<3> &, const Matrix<3> &);
template bool operator==(const Matrix<2> &, const Matrix<2> &);
template bool operator!=(const Matrix<4> &, const Matrix<4> &);
template double determinant(const Matrix<4> &);
template double determinant(const Matrix<3> &);
template Matrix<3> submatrix(const Matrix<4> &, std::size_t, std::size_t);
template Matrix<2> submatrix(const Matrix<3> &, std::size_t, std::size_t);
template double minor(const Matrix<4> &, std::size_t, std::size_t);
template double minor(const Matrix<3> &, std::size_t, std::size_t);
template double cofactor(const Matrix<4> &, std::size_t, std::size_t);
template double cofactor(const Matrix<3> &, std::size_t, std::size_t);
