#include <iostream>
#include <cstdlib>
#include <ctime>
#define delimiter "---------------------\n"
using namespace std;

class Matrix
{
public:
    Matrix(size_t rows, size_t cols) : _rows(rows), _cols(cols) { initialize(_rows, _cols); }
    Matrix() : Matrix(2, 2) {}
    Matrix(const Matrix& other) {
        _rows = other._rows;
        _cols = other._cols;
        initialize(_rows, _cols);
        for (size_t i = 0; i < _rows; i++) {
            for (size_t j = 0; j < _cols; j++) {
                _matrix[i][j] = other._matrix[i][j];
            }
        }
    }
    ~Matrix() { clear(); }

    int get_rows() const { return _rows; }
    int get_cols() const { return _cols; }

    Matrix& operator=(const Matrix& other) {
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
    }
    Matrix operator+(const Matrix& other) const {
		if (_rows != other._rows || _cols != other._cols) return Matrix(0, 0);

		Matrix temp(_rows, _cols);
		for (size_t i = 0; i < _rows; i++) {
			for (size_t j = 0; j < _cols; j++) {
			    temp[i][j] = _matrix[i][j] + other[i][j];
            }
		}
		return temp;
	}
    Matrix operator-(const Matrix& other) const {
        if (_rows != other._rows || _cols != other._cols) return Matrix(0, 0);

        Matrix temp(_rows, _cols);
        for (size_t i = 0; i < _rows; i++) {
            for (size_t j = 0; j < _cols; j++) {

                temp[i][j] = _matrix[i][j] - other[i][j];
            }
        }
        return temp;
    }
    Matrix operator-() const {
        Matrix temp(_rows, _cols);
        for (size_t i = 0; i < _rows; i++) {
            for (size_t j = 0; j < _cols; j++) {
                temp[i][j] = -_matrix[i][j];
            }
        }
        return temp;
    }
    Matrix operator*(const Matrix& other) const {
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
    Matrix operator*(int value) const {
        Matrix temp(_rows, _cols);
        for (size_t i = 0; i < _rows; i++) {
            for (size_t j = 0; j < _cols; j++) {
                temp[i][j] = _matrix[i][j] * value;
            }
        }
        return temp;
    }
    Matrix& operator+=(const Matrix& other) {
        *this = *this + other;
        return *this;
    }
    Matrix& operator-=(const Matrix& other) {
        *this = *this - other;
        return *this;
    }
    Matrix& operator*=(const Matrix& other) {
        *this = *this * other;
        return *this;
    }
    int* operator[](size_t index) {
        return _matrix[index];
    }
    const int* operator[](size_t index) const {
        return _matrix[index];
    }

    int determinant() const {
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

    int minor(size_t row, size_t col) const {
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

    Matrix inverse() const {
        if (_rows != _cols || _rows == 0)return Matrix(0, 0);

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

    Matrix transposed() const {
        Matrix temp(_cols, _rows);
        for (size_t i = 0; i < _rows; i++) {
            for (size_t j = 0; j < _cols; j++) {
                temp[j][i] = _matrix[i][j];
            }
        }
        return temp;
    }

    void random() {
        for (size_t i = 0; i < _rows; i++) {
            for (size_t j = 0; j < _cols; j++) {
                _matrix[i][j] = rand() % 10;
            }
        }
    }
    void print() const {
        for (size_t i = 0; i < _rows; i++) {
            for (size_t j = 0; j < _cols; j++) {
                cout << _matrix[i][j] << " ";
            }
            cout << endl;
        }
        cout << endl;
    }
private:
    void clear() {
        if (_matrix) {
            for (size_t i = 0; i < _rows; i++) {
                delete[] _matrix[i];
            }
            delete[] _matrix;
            _matrix = nullptr;
        }
    }
    void initialize(size_t rows, size_t cols) {
        _matrix = new int* [rows];
        for (size_t i = 0; i < rows; i++) {
            _matrix[i] = new int[cols];
            for (size_t j = 0; j < cols; j++) {
                _matrix[i][j] = {};
            }
        }
    }

    size_t _cols;
    size_t _rows;
    int** _matrix = nullptr;
};
ostream& operator<<(ostream& os, const Matrix& obj) {
    for (int i = 0; i < obj.get_rows(); i++) {
        for (int j = 0; j < obj.get_cols(); j++) {
            os << obj[i][j] << " ";
        }
        os << endl;
    }
    os << endl;
    return os;
}

int main()
{
    srand((unsigned)time(0));
    Matrix A;
    A.random();
    cout << "A" << endl;
    cout << A;
    cout << delimiter;

    Matrix B;
    B.random();
    cout << "B" << endl;
    cout << B;
    cout << delimiter;

    cout << "A + B" << endl;
    Matrix C = A + B;
    C.print();
    cout << delimiter;

    cout << "A - B" << endl;
    (A - B).print();
    cout << delimiter;

    cout << "A * B" << endl;
    (A * B).print();
    cout << delimiter;

    cout << "A * 2" << endl;
    (A * 2).print();
    cout << delimiter;

    cout << "Determinant of A: " << A.determinant() << endl;
    cout << delimiter;

    cout << "Inverse of A:" << endl;
    Matrix invA = A.inverse();
    invA.print();
    cout << delimiter;
}
