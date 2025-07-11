#include <iostream>
#include <Matrix.h>
#define delimiter "---------------------\n"

using namespace std;

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
