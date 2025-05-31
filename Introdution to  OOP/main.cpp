#include <iostream>
#include <math.h>

#define tab "\t"

using namespace std;

class Point {
private:
	double x;
	double y;

public:
	Point() : x(0), y(0) {}
	Point(double other_x, double other_y) : x(other_x), y(other_y) {}
	~Point(){}

	double distance(Point& other) {
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
	double get_y() const{
		return y;
	}
};

double distance(Point& A, Point& B) {
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
	A.set_x(2);
	A.set_y(3);

	Point B;
	B.set_x(5);
	B.set_y(7);

	cout << A.get_x() << tab << A.get_y() << endl;

	cout << A.distance(B) << endl;

	cout << distance(A, B) << endl;

	// . - Оператор прямого доступа (По имени)
	// -> - Оператор косвенного доступа (По адрессу)
}