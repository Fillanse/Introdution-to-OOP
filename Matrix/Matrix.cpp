#include <iostream>
#include <cstdlib>
#include <ctime>
#define delimiter "---------------------\n"
using namespace std;

class Matrix
{
public:
	Matrix(size_t rows, size_t cols) : _rows(rows), _cols(cols) { initialize(_rows, _cols); }
	template<size_t rows, size_t cols>
	Matrix(const int (&arr)[rows][cols]) : Matrix(rows, cols) { // type mismatch for initialize(**,int,int)?
		initialize(_rows, _cols);
		for (size_t i = 0; i < _rows; i++) {
			for (size_t j = 0; j < _cols; j++) {
				_matrix[i][j] = arr[i][j];
			}
		}
	}
	Matrix() : Matrix(2, 2) {}
	Matrix(initializer_list<initializer_list<int>> l) : _rows(l.size()), _cols(l.begin()->size()){
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
	Matrix(const Matrix& other) : Matrix(other._rows, other._cols) { initialize(other._matrix, _rows, _cols); }
	Matrix(Matrix&& other) {
		_rows = other._rows;
		_cols = other._cols;
		_matrix = other._matrix;
		other._rows = 0;
		other._cols = 0;
		other._matrix = nullptr;
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
		return *this;
	}
	Matrix& operator=(Matrix&& other) {
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
	void initialize(int** arr, size_t rows, size_t cols) {
		_matrix = new int* [rows];
		for (size_t i = 0; i < rows; i++) {
			_matrix[i] = new int[cols];
			for (size_t j = 0; j < cols; j++) {
				_matrix[i][j] = arr[i][j];
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

void main() {
	srand((unsigned)time(0));

	Matrix m1;
	m1.print();
	cout << delimiter;

	Matrix m2 = { {1, 2, 3}, {4, 5, 6}, {7, 8, 9} };
	cout << "m2:" << endl << m2;
	cout << "Determinant: " << m2.determinant() << endl;
	cout << delimiter;

	Matrix A(3, 3);
	A.random();
	Matrix B(3, 3);
	B.random();

	cout << "Matrix A:" << endl << A;
	cout << "Matrix B:" << endl << B;
	cout << delimiter;

	cout << "A + B:" << endl << (A + B);
	cout << "A - B:" << endl << (A - B);
	cout << "A * B:" << endl << (A * B);
	cout << "A * 5:" << endl << (A * 5);
	cout << "-A:" << endl << (-A);
	cout << delimiter;

	Matrix C = A;
	C += B;
	cout << "C += B:" << endl << C;

	C = A;
	C -= B;
	cout << "C -= B:" << endl << C;

	C = A;
	C *= B;
	cout << "C *= B:" << endl << C;
	cout << delimiter;

	cout << "Transpose of A:" << endl << A.transposed();
	cout << "Determinant of A: " << A.determinant() << endl;
	cout << "Inverse of A:" << endl << A.inverse();
	cout << "A * inv(A):" << endl << (A * A.inverse());
	cout << delimiter;

	Matrix empty(0, 0);
	cout << "Empty matrix:" << endl << empty;
	cout << "Determinant of empty: " << empty.determinant() << endl;

	Matrix nonSquare(2, 3);
	nonSquare.random();
	cout << "Non-square matrix (2x3):" << endl << nonSquare;
	cout << "Attempting inverse (should fail):" << endl << nonSquare.inverse();
	cout << delimiter;

	Matrix copy = A;
	cout << "Copy of A:" << endl << copy;

	Matrix moved = std::move(A);
	cout << "Moved from A:" << endl << moved;
	cout << "Original A (should be empty):" << endl << A;
	cout << delimiter;

	int arr[2][2] = { {1, 2}, {3, 4} };
	Matrix fromArr(arr);
	cout << "From array:" << endl << fromArr;
	cout << "Determinant: " << fromArr.determinant() << endl;
	cout << "Inverse:" << endl << fromArr.inverse();
	cout << delimiter;

}
