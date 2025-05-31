#include <iostream>
#include <math.h>

#define tab "\t"

using namespace std;

class Point {
private:
	double x;
	double y;

public:
	Point(double other_x, double other_y) : x(other_x), y(other_y) { cout << "Constructor: " << tab << tab << this << endl; }
	Point() : Point(0, 0) {}
	~Point() { cout << "Destructor: " << tab << tab << this << endl; }

	double distance(Point& other) const {
		return sqrt(pow((other.x - x), 2) + pow((other.y - y), 2));
	}

	void set_x(double value) {
		x = value;
	}
	void set_y(double value) {
		y = value;
	}

	double get_x() const {
		return x;
	}
	double get_y() const {
		return y;
	}

	void print() const {
		cout << "X = " << get_x() << tab << "Y = " << get_y() << endl;
	}
};

const double distance(Point& A, Point& B) {
	return sqrt(pow((B.get_x() - A.get_x()), 2) + pow((B.get_y() - A.get_y()), 2));
}


//#define STRUCT_POINT

void main() {
#ifdef STRUCT_POINT
	Point A;

	A.x = 2;
	A.y = 3;

	cout << A.x << "\t" << A.y << endl;

	Point* pA = &A;

	cout << pA->x << "\t" << pA->y << endl;
#endif // STRUCT_POINT

	Point A;
	//cout << "A :" << tab << A.get_x() << tab << A.get_y() << endl;
	A.print();

	Point B(5, 7);
	//	cout << "B :" << tab << B.get_x() << tab << B.get_y() << endl;
	B.print();


	cout << "Distance from A to be via method: " << tab << A.distance(B) << endl;

	cout << "Distance from A to be via function: " << tab << distance(A, B) << endl;
}