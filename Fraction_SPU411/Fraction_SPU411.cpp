#define _CRT_SECURE_NO_WARNINGS 
#include "Fraction_SPU411.h"

int Fraction::get_integer() const { return integer; }
int Fraction::get_numerator() const { return numerator; }
int Fraction::get_denominator() const { return denominator; }

void Fraction::set_integer(int integer) { this->integer = integer; }
void Fraction::set_numerator(int numerator) { this->numerator = numerator; }
void Fraction::set_denominator(int denominator)
{
    if (denominator == 0) denominator = 1;
    this->denominator = denominator;
}

Fraction::Fraction()
{
    integer = 0;
    numerator = 0;
    denominator = 1;
    std::cout << "DefaultConstructor:\t" << this << std::endl;
}

Fraction::Fraction(int integer)
{
    this->integer = integer;
    numerator = 0;
    denominator = 1;
    std::cout << "SingleArgConstructor:\t" << this << std::endl;
}

Fraction::Fraction(double decimal)
{
    decimal += 1e-10;
    integer = decimal;
    decimal -= integer;
    denominator = 1e+9;
    numerator = decimal * denominator;
    reduce();
}

Fraction::Fraction(int numerator, int denominator)
{
    integer = 0;
    this->numerator = numerator;
    set_denominator(denominator);
    std::cout << "Constructor:\t\t" << this << std::endl;
}

Fraction::Fraction(int integer, int numerator, int denominator)
{
    set_integer(integer);
    set_numerator(numerator);
    set_denominator(denominator);
    std::cout << "Constructor:\t\t" << this << std::endl;
}

Fraction::Fraction(const Fraction& other)
{
    integer = other.integer;
    numerator = other.numerator;
    denominator = other.denominator;
    std::cout << "CopyConstructor:\t" << this << std::endl;
}

Fraction::~Fraction()
{
    std::cout << "Destructor:\t\t" << this << std::endl;
}

Fraction& Fraction::operator=(const Fraction& other)
{
    integer = other.integer;
    numerator = other.numerator;
    denominator = other.denominator;
    std::cout << "CopyAssignment:\t\t" << this << std::endl;
    return *this;
}

Fraction& Fraction::operator*=(const Fraction& other)
{
    return *this = *this * other;
}

Fraction& Fraction::operator/=(const Fraction& other)
{
    return *this = *this / other;
}

Fraction& Fraction::operator++()
{
    integer++;
    return *this;
}

Fraction Fraction::operator++(int)
{
    Fraction old = *this;
    integer++;
    return old;
}

Fraction::operator int() const
{
    return integer + numerator / denominator;
}

Fraction::operator double() const
{
    return integer + (double)numerator / denominator;
}

Fraction& Fraction::reduce()
{
    int more, less, rest;
    if (numerator < denominator)
    {
        less = numerator;
        more = denominator;
    }
    else
    {
        more = numerator;
        less = denominator;
    }
    do
    {
        rest = more % less;
        more = less;
        less = rest;
    } while (rest);
    int GCD = more;
    numerator /= GCD;
    denominator /= GCD;
    return *this;
}

Fraction& Fraction::to_improper()
{
    numerator += integer * denominator;
    integer = 0;
    return *this;
}

Fraction& Fraction::to_proper()
{
    integer += numerator / denominator;
    numerator %= denominator;
    return *this;
}

Fraction Fraction::inverted() const
{
    Fraction inverted = *this;
    inverted.to_improper();
    std::swap(inverted.numerator, inverted.denominator);
    return inverted;
}

void Fraction::print() const
{
    if (integer) std::cout << integer;
    if (numerator)
    {
        if (integer) std::cout << "(";
        std::cout << numerator << "/" << denominator;
        if (integer) std::cout << ")";
    }
    else if (integer == 0) std::cout << 0;
    std::cout << std::endl;
}

Fraction operator*(Fraction left, Fraction right)
{
    left.to_improper();
    right.to_improper();
    return Fraction(
        left.get_numerator() * right.get_numerator(),
        left.get_denominator() * right.get_denominator()
    ).to_proper();
}

Fraction operator/(const Fraction& left, const Fraction& right)
{
    return left * right.inverted();
}

bool operator==(Fraction left, Fraction right)
{
    left.to_improper();
    right.to_improper();
    return
        left.get_numerator() * right.get_denominator() ==
        right.get_numerator() * left.get_denominator();
}

bool operator!=(const Fraction& left, const Fraction& right)
{
    return !(left == right);
}

bool operator>(Fraction left, Fraction right)
{
    left.to_improper();
    right.to_improper();
    return
        left.get_numerator() * right.get_denominator() >
        right.get_numerator() * left.get_denominator();
}

bool operator<(Fraction left, Fraction right)
{
    left.to_improper();
    right.to_improper();
    return
        left.get_numerator() * right.get_denominator() <
        right.get_numerator() * left.get_denominator();
}

bool operator>=(const Fraction& left, const Fraction& right)
{
    return !(left < right);
}

bool operator<=(const Fraction& left, const Fraction& right)
{
    return !(left > right);
}

std::ostream& operator<<(std::ostream& os, const Fraction& obj)
{
    if (obj.get_integer()) os << obj.get_integer();
    if (obj.get_numerator())
    {
        if (obj.get_integer()) os << "(";
        os << obj.get_numerator() << "/" << obj.get_denominator();
        if (obj.get_integer()) os << ")";
    }
    else if (obj.get_integer() == 0) os << 0;
    return os;
}

std::istream& operator>>(std::istream& is, Fraction& obj)
{
    const int SIZE = 32;
    char sz_input[SIZE] = {};
    is.getline(sz_input, SIZE);
    const char delimiters[] = { '(', '/', ')', ' ', '.', ',', 0 };
    int numbers[3] = {};
    int n = 0;

    for (char* pch = strtok(sz_input, delimiters); pch && n < 3; pch = strtok(NULL, delimiters))
        numbers[n++] = atoi(pch);

    switch (n)
    {
    case 1: obj = Fraction(numbers[0]); break;
    case 2: obj = Fraction(numbers[0], numbers[1]); break;
    case 3: obj = Fraction(numbers[0], numbers[1], numbers[2]); break;
    }

    return is;
}