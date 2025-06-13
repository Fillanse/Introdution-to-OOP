#include <iostream>
#include <math.h>

#define tab "\t"
#define deliminer "\n------------------------------------------------------------------------------------\n"

using namespace std;

class Point {
private:
	double x;
	double y;

public:
	Point(double other_x, double other_y) : x(other_x), y(other_y) { cout << "Constructor: " << tab << tab << this << endl; }
	Point() : Point(0, 0) {}
	Point(const Point& other) : x(other.x), y(other.y) {}
	~Point() { cout << "Destructor: " << tab << tab << this << endl; }

	Point& operator=(const Point& other) {
		x = other.x;
		y = other.y;
		cout << "CopyAssignment: " << tab << this << endl;

		return *this;
	}
	Point& operator++() {
		x++;
		y++;
		return *this;
	}
	Point operator+(const Point& other) {
		return Point(this->x + other.x, this->y + other.y);
	}

	double distance(const Point& other) const {
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

const double distance(const Point& A, const Point& B) {
	return sqrt(pow((B.get_x() - A.get_x()), 2) + pow((B.get_y() - A.get_y()), 2));
}


//#define STRUCT_POINT
//#define CONSTRUCTORS_CHECK
//#define DISTANCE_CHECK
#define ASSIGNMENT_CHECK

void main() {
#ifdef STRUCT_POINT
	Point A;

	A.x = 2;
	A.y = 3;

	cout << A.x << "\t" << A.y << endl;

	Point* pA = &A;

	cout << pA->x << "\t" << pA->y << endl;
#endif // STRUCT_POINT
#ifdef CONSTRUCTORS_CHECK
	Point A;
	A.print();

	Point B(5, 7);
	B.print();

	Point C;
	C.print();

	Point D(C);
	D.print();
#endif // CONSTRUCTOR_CHECK

#ifdef DISTANCE_CHECK

	Point A;
	//cout << "A :" << tab << A.get_x() << tab << A.get_y() << endl;
	A.print();

	Point B(5, 7);
	//	cout << "B :" << tab << B.get_x() << tab << B.get_y() << endl;
	B.print();

	cout << deliminer << endl;
	cout << "Distance from A to be via method: " << tab << A.distance(B) << endl;
	cout << deliminer << endl;
	cout << "Distance from A to be via function: " << tab << distance(A, B) << endl;
#endif // DISTANCE_CHECK
#ifdef ASSIGNMENT_CHECK


	int a, b, c;
	a = b = c = 0;

	cout << a << tab << b << c << endl;

	Point A, B, C;
	A = B = C = Point(2,3);
	A.print();
	B.print();

	C = A + B;
	C.print();

#endif // ASSIGNMENT_CHECK




}