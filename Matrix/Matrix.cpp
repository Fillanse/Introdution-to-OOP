#include "Matrix.h"

Matrix::Matrix(size_t rows, size_t cols) : _rows(rows), _cols(cols)
{
    initialize(_rows, _cols);
}

template<size_t rows, size_t cols>
Matrix::Matrix(const int(&arr)[rows][cols]) : Matrix(rows, cols)
{
    for (size_t i = 0; i < _rows; i++) {
        for (size_t j = 0; j < _cols; j++) {
            _matrix[i][j] = arr[i][j];
        }
    }
}

Matrix::Matrix() : Matrix(2, 2) {}

Matrix::Matrix(std::initializer_list<std::initializer_list<int>> l) : _rows(l.size()), _cols(l.begin()->size())
{
    initialize(_rows, _cols);
    size_t i = 0;
    for (auto& row : l) {
        size_t j = 0;
        for (auto& elem : row) {
            _matrix[i][j++] = elem;
        }
        i++;
    }
}

Matrix::Matrix(const Matrix& other) : Matrix(other._rows, other._cols)
{
    for (size_t i = 0; i < _rows; i++) {
        for (size_t j = 0; j < _cols; j++) {
            _matrix[i][j] = other._matrix[i][j];
        }
    }
}

Matrix::Matrix(Matrix&& other)
{
    _rows = other._rows;
    _cols = other._cols;
    _matrix = other._matrix;
    other._rows = 0;
    other._cols = 0;
    other._matrix = nullptr;
}

Matrix::~Matrix()
{
    clear();
}

int Matrix::get_rows() const { return _rows; }
int Matrix::get_cols() const { return _cols; }

Matrix& Matrix::operator=(const Matrix& other)
{
    if (this == &other) return *this;
    clear();
    _rows = other._rows;
    _cols = other._cols;
    initialize(_rows, _cols);
    for (size_t i = 0; i < _rows; i++) {
        for (size_t j = 0; j < _cols; j++) {
            _matrix[i][j] = other._matrix[i][j];
        }
    }
    return *this;
}

Matrix& Matrix::operator=(Matrix&& other)
{
    if (this != &other) {
        clear();
        _rows = other._rows;
        _cols = other._cols;
        _matrix = other._matrix;
        other._rows = 0;
        other._cols = 0;
        other._matrix = nullptr;
    }
    return *this;
}

Matrix Matrix::operator+(const Matrix& other) const
{
    if (_rows != other._rows || _cols != other._cols) return Matrix(0, 0);

    Matrix temp(_rows, _cols);
    for (size_t i = 0; i < _rows; i++) {
        for (size_t j = 0; j < _cols; j++) {
            temp[i][j] = _matrix[i][j] + other[i][j];
        }
    }
    return temp;
}

Matrix Matrix::operator-(const Matrix& other) const
{
    if (_rows != other._rows || _cols != other._cols) return Matrix(0, 0);

    Matrix temp(_rows, _cols);
    for (size_t i = 0; i < _rows; i++) {
        for (size_t j = 0; j < _cols; j++) {
            temp[i][j] = _matrix[i][j] - other[i][j];
        }
    }
    return temp;
}

Matrix Matrix::operator-() const
{
    Matrix temp(_rows, _cols);
    for (size_t i = 0; i < _rows; i++) {
        for (size_t j = 0; j < _cols; j++) {
            temp[i][j] = -_matrix[i][j];
        }
    }
    return temp;
}

Matrix Matrix::operator*(const Matrix& other) const
{
    if (_cols != other._rows) return Matrix(0, 0);

    Matrix temp(_rows, other._cols);
    for (size_t i = 0; i < _rows; i++) {
        for (size_t j = 0; j < other._cols; j++) {
            for (size_t k = 0; k < _cols; k++) {
                temp[i][j] += _matrix[i][k] * other[k][j];
            }
        }
    }
    return temp;
}

Matrix Matrix::operator*(int value) const
{
    Matrix temp(_rows, _cols);
    for (size_t i = 0; i < _rows; i++) {
        for (size_t j = 0; j < _cols; j++) {
            temp[i][j] = _matrix[i][j] * value;
        }
    }
    return temp;
}

Matrix& Matrix::operator+=(const Matrix& other)
{
    *this = *this + other;
    return *this;
}

Matrix& Matrix::operator-=(const Matrix& other)
{
    *this = *this - other;
    return *this;
}

Matrix& Matrix::operator*=(const Matrix& other)
{
    *this = *this * other;
    return *this;
}

int* Matrix::operator[](size_t index)
{
    return _matrix[index];
}

const int* Matrix::operator[](size_t index) const
{
    return _matrix[index];
}

int Matrix::determinant() const
{
    if (_rows != _cols || _rows == 0) return 0;
    if (_rows == 1) return _matrix[0][0];
    if (_rows == 2) return _matrix[0][0] * _matrix[1][1] - _matrix[0][1] * _matrix[1][0];

    int det = 0;
    int sign = 1;
    for (size_t j = 0; j < _cols; j++) {
        int minor_det = minor(0, j);
        det += sign * _matrix[0][j] * minor_det;
        sign = -sign;
    }
    return det;
}

int Matrix::minor(size_t row, size_t col) const
{
    if (_rows <= 1 || _cols <= 1) return 0;

    Matrix temp(_rows - 1, _cols - 1);
    size_t r = 0;
    for (size_t i = 0; i < _rows; i++) {
        if (i == row) continue;
        size_t c = 0;
        for (size_t j = 0; j < _cols; j++) {
            if (j == col) continue;
            temp[r][c] = _matrix[i][j];
            c++;
        }
        r++;
    }
    return temp.determinant();
}

Matrix Matrix::inverse() const
{
    if (_rows != _cols || _rows == 0) return Matrix(0, 0);

    int det = determinant();
    if (det == 0) return Matrix(0, 0);

    Matrix cofactor(_rows, _cols);
    for (size_t i = 0; i < _rows; i++) {
        for (size_t j = 0; j < _cols; j++) {
            cofactor[i][j] = ((i + j) % 2 ? -1 : 1) * minor(i, j);
        }
    }

    Matrix attached = cofactor.transposed();
    Matrix result(_rows, _cols);
    for (size_t i = 0; i < _rows; i++) {
        for (size_t j = 0; j < _cols; j++) {
            result[i][j] = attached[i][j] / det;
        }
    }
    return result;
}

Matrix Matrix::transposed() const
{
    Matrix temp(_cols, _rows);
    for (size_t i = 0; i < _rows; i++) {
        for (size_t j = 0; j < _cols; j++) {
            temp[j][i] = _matrix[i][j];
        }
    }
    return temp;
}

void Matrix::random()
{
    for (size_t i = 0; i < _rows; i++) {
        for (size_t j = 0; j < _cols; j++) {
            _matrix[i][j] = rand() % 10;
        }
    }
}

void Matrix::print() const
{
    for (size_t i = 0; i < _rows; i++) {
        for (size_t j = 0; j < _cols; j++) {
            std::cout << _matrix[i][j] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

void Matrix::clear()
{
    if (_matrix) {
        for (size_t i = 0; i < _rows; i++) {
            delete[] _matrix[i];
        }
        delete[] _matrix;
        _matrix = nullptr;
    }
}

void Matrix::initialize(size_t rows, size_t cols)
{
    _matrix = new int* [rows];
    for (size_t i = 0; i < rows; i++) {
        _matrix[i] = new int[cols];
        for (size_t j = 0; j < cols; j++) {
            _matrix[i][j] = {};
        }
    }
}

void Matrix::initialize(int** arr, size_t rows, size_t cols)
{
    _matrix = new int* [rows];
    for (size_t i = 0; i < rows; i++) {
        _matrix[i] = new int[cols];
        for (size_t j = 0; j < cols; j++) {
            _matrix[i][j] = arr[i][j];
        }
    }
}

std::ostream& operator<<(std::ostream& os, const Matrix& obj)
{
    for (int i = 0; i < obj.get_rows(); i++) {
        for (int j = 0; j < obj.get_cols(); j++) {
            os << obj[i][j] << " ";
        }
        os << std::endl;
    }
    os << std::endl;
    return os;
}