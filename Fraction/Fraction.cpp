#include <iostream>
#include <numeric>

#define delimiter "\n----------------------------------------------\n";

using namespace std;

class Fraction {
private:
	int numerator;
	int	denominator;
	int whole;
	
	int gcd(int a, int b) {
		while (b != 0) {
			int temp = b;
			b = a % b;
			a = temp;
		}
		return a;
	}

	int lcm(int a, int b) {
		return (a / gcd(a, b)) * b;
	}

	void Normalize() {

		if (denominator < 0) {
			denominator = -denominator;
			numerator = -numerator;
		}

		if (abs(numerator) >= denominator) {
			whole += numerator / denominator;
			numerator = numerator % denominator;
		}

		int divisor = gcd(numerator, denominator);
		if (divisor > 0) {
			numerator /= divisor;
			denominator /= divisor;
		}

		if (numerator < 0 && whole != 0) {
			whole--;
			numerator += denominator;
		}
	}

	void Denormalize() {
		numerator = whole * denominator + numerator;
		whole = 0;
	}
	
public:
	Fraction(int other_numerator, int other_denominator, int other_whole) : numerator(other_numerator), denominator(other_denominator), whole(other_whole){}
	Fraction(int other_numerator, int other_denominator) : Fraction(other_numerator, other_denominator, 0){}
	Fraction() : Fraction(1, 2, 0){}
	~Fraction(){}

	Fraction& operator++() {
		Denormalize();

		numerator++;

		Normalize();

		return *this;
	}
	Fraction operator++(int) {
		Fraction temp = *this;

		++(*this);      

		return temp;          
	}
	Fraction& operator--() {
		Denormalize();

		numerator--;

		Normalize();

		return *this;
	}
	Fraction operator--(int) {
		Fraction temp = *this;

		--(*this);

		return temp;
	}
	Fraction& operator=(const Fraction& other)  {
		numerator = other.numerator;
		denominator = other.denominator;
		whole = other.whole;

		return *this;
	}
	Fraction& operator+=(const Fraction& other) {
		if (denominator == other.denominator) {

			numerator += other.numerator;
			whole += other.whole;

			Normalize();

			return *this;
		}
		int common_den = lcm(denominator, other.denominator);
		numerator = numerator * (common_den / denominator) + other.numerator * (common_den / other.denominator);
		denominator = common_den;

		Normalize();

		return *this;
	}
	Fraction operator+(const Fraction& other) const {
		Fraction result = *this;
		
		result += other;

		return result;
	}
	Fraction& operator-=(const Fraction& other)  {
		if (denominator == other.denominator) {

			numerator -= other.numerator;
			whole -= other.whole;

			Normalize();

			return *this;
		}
		int common_den = lcm(denominator, other.denominator);
		numerator = numerator * (common_den / denominator) - other.numerator * (common_den / other.denominator);
		denominator = common_den;

		Normalize();

		return *this;
	}
	Fraction operator-(const Fraction& other) const {
		Fraction result = *this;

		result -= other;

		return result;
	}	
	Fraction& operator*=(const Fraction& other) {
		Denormalize();

		numerator *= other.numerator;
		denominator *= other.denominator;

		Normalize();

		return *this;
	}
	Fraction operator*(const Fraction& other) const {
		Fraction result = *this;

		result *= other;

		return result;
	}
	Fraction& operator/=(const Fraction& other) {
		Denormalize();

		numerator *= other.denominator;
		denominator *= other.numerator;

		Normalize();

		return *this;
	}
	Fraction operator/(const Fraction& other) const{
		Fraction result = *this;

		result /= other;

		return result;
	}
	bool operator>(Fraction other) {
		Denormalize();
		other.Denormalize();

		int common_den = lcm(denominator, other.denominator);
		return numerator * (common_den / denominator) > other.numerator * (common_den / other.denominator);
	}
	bool operator<(Fraction other) {
		Denormalize();
		other.Denormalize();

		int common_den = lcm(denominator, other.denominator);
		return numerator * (common_den / denominator) < other.numerator * (common_den / other.denominator);
	}
	bool operator==(Fraction other) {
		Normalize();
		other.Normalize();

		return whole == other.whole && numerator == other.numerator && denominator == other.denominator;
	}
	bool operator>=(Fraction other) {
		return *this > other || *this == other;
	}
	bool operator<=(Fraction other) {
		return *this < other || *this == other;

	}
	bool operator!=(Fraction other) {
		return !(*this == other);
	}
	void Print() const{
		if (whole != 0) cout << whole << " ";
		cout << numerator << "/" << denominator << " ";
	}
};
int main()
{
	Fraction A(2, 7, 5);
	Fraction B(3, 5);     

	cout << "A: ";
	A.Print();
	cout << endl;

	cout << "B: ";
	B.Print();
	cout << endl;

	cout << delimiter;

	Fraction add = A + B;
	cout << "A + B = ";
	add.Print();
	cout << endl;

	Fraction sub = A - B;
	cout << "A - B = ";
	sub.Print();
	cout << endl;

	Fraction mul = A * B;
	cout << "A * B = ";
	mul.Print();
	cout << endl;

	Fraction div = A / B;
	cout << "A / B = ";
	div.Print();
	cout << endl;

	cout << delimiter;

	++A;
	cout << "++A = ";
	A.Print();
	cout << endl;

	--A;
	cout << "--A = ";
	A.Print();
	cout << endl;

	B++;
	cout << "B++ = ";
	B.Print();
	cout << endl;

	B--;
	cout << "B-- = ";
	B.Print();
	cout << endl;

	cout << delimiter;

	cout << "A == B: " << (A == B) << endl;
	cout << "A != B: " << (A != B) << endl;
	cout << "A > B:  " << (A > B) << endl;
	cout << "A < B:  " << (A < B) << endl;
	cout << "A >= B: " << (A >= B) << endl;
	cout << "A <= B: " << (A <= B) << endl;

	cout << delimiter;

	Fraction C;
	C = A;
	cout << "C = A -> ";
	C.Print();
	cout << endl;

	C += B;
	cout << "C += B -> ";
	C.Print();
	cout << endl;

	C -= B;
	cout << "C -= B -> ";
	C.Print();
	cout << endl;

	C *= B;
	cout << "C *= B -> ";
	C.Print();
	cout << endl;

	C /= B;
	cout << "C /= B -> ";
	C.Print();
	cout << endl;
}
