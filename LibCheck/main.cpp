#include <iostream>
#include <Fraction_SPU411.h>
using namespace std;

#define CONSTRUCTORS_CHECK
#define ASSIGNMENT_CHECK
//#define ARITHMETICAL_OPERATORS
//#define INCREMENT_DECREMENT
//#define COMPARISON_OPERATORS
//#define ISTREAM_OPERATOR
//#define CONVERSIONS_BASICS
//#define CONVERSION_FROM_OTHER_TO_CLASS
//#define CONVERSIONS_FROM_CLASS_TO_OTHER

void main()
{
	setlocale(LC_ALL, "");

#ifdef CONSTRUCTORS_CHECK
	Fraction A;			//Default constructor
	A.print();

	Fraction B = 5;		//Single-argument constructor (Конструктор с одним параметром)
	B.print();

	Fraction C(1, 2);	//Constructor
	C.print();

	Fraction D(2, 3, 4);//Constructor
	D.print();

	Fraction E = D;		//Copy constructor
	E.print();

	Fraction F;
	F = E;				//Copy assignment
	F.print();
#endif // CONSTRUCTORS_CHECK

#ifdef ASSIGNMENT_CHECK
	int a, b, c;

	a = b = c = 0;

	cout << a << "\t" << b << "\t" << c << endl;

	Fraction A, B, C;
	cout << delimiter << endl;
	A = B = C = Fraction(2, 3, 4);
	//Fraction(2, 3, 4); // Явный вызов конструктора, который создает временный безымянный объект.
	//Временные безымянные объекты существуют в пределах одного выражения
	cout << delimiter << endl;
#endif // ASSIGNMENT_CHECK

#ifdef ARITHMETICAL_OPERATORS
	Fraction A(1, 2);
	Fraction B(2, 3, 4);
	Fraction C = A / B;
	A.print();
	B.print();
	C.print();
	cout << delimiter << endl;
	A /= B;
	A.print();
	B.print();
#endif // ARITHMETICAL_OPERATORS

#ifdef INCREMENT_DECREMENT
	Fraction A(1, 2);
	Fraction B = A++;
	A.print();
	B.print();
#endif // INCREMENT_DECREMENT

#ifdef COMPARISON_OPERATORS
	cout << (Fraction(1, 3) <= Fraction(5, 11)) << endl;
#endif // COMPARISON_OPERATORS

	//Fraction A(1, 2, 3);
	//Fraction B(2, 3, 4);

#ifdef ISTREAM_OPERATOR
	Fraction A;
	cout << "Введите простую дробь: "; cin >> A;
	cout << delimiter << endl;
	cout << A << endl;
	cout << delimiter << endl;
#endif // ISTREAM_OPERATOR

#ifdef CONVERSIONS_BASICS
	//(type)value;	//C-like notation
//type(value);	//Functional notation
//C4244: ... possible loss of data

	int a = 2;		//No conversions
	double b = 3;	//Implicit conversion from less to more ('int' to 'double')
	int c = b;		//Implicit conversion from more to less without data loss
	int d = 4.5;	//Implicit conversion from more to less with data loss  
#endif // CONVERSIONS_BASICS

	/*
	------------------------------
	1. From other to Class:
		1.1. SingleArgumentConstrictor;
		1.2. Assignment operator (Copy assignment);
	2. From Class to other;
	------------------------------
	*/

#ifdef CONVERSION_FROM_OTHER_TO_CLASS
	Fraction A = (Fraction)5;		//Conversion from less to more
	cout << A << endl;

	Fraction B;
	cout << delimiter << endl;
	B = Fraction(8);
	cout << delimiter << endl;
	cout << B << endl;
#endif // CONVERSION_FROM_OTHER_TO_CLASS

#ifdef CONVERSIONS_FROM_CLASS_TO_OTHER
	/*operator type()
{
	....;
	....;
	....;
}*/

	Fraction A(2, 3, 4);
	cout << A << endl;

	int a = A;
	cout << a << endl;
	double b = A;
	cout << b << endl;
#endif // CONVERSIONS_FROM_CLASS_TO_OTHER

	/*int i = 0;
	i += 1;*/

	Fraction A = 2.76;
	cout << A << endl;
}