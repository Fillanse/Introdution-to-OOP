#pragma once
#include <iostream>

class Fraction
{
    int integer;
    int numerator;
    int denominator;

public:
    int get_integer() const;
    int get_numerator() const;
    int get_denominator() const;
    void set_integer(int integer);
    void set_numerator(int numerator);
    void set_denominator(int denominator);

    Fraction();
    explicit Fraction(int integer);
    Fraction(double decimal);
    Fraction(int numerator, int denominator);
    Fraction(int integer, int numerator, int denominator);
    Fraction(const Fraction& other);
    ~Fraction();

    Fraction& operator=(const Fraction& other);
    Fraction& operator*=(const Fraction& other);
    Fraction& operator/=(const Fraction& other);
    Fraction& operator++();
    Fraction operator++(int);
    operator int() const;
    operator double() const;

    Fraction& reduce();
    Fraction& to_improper();
    Fraction& to_proper();
    Fraction inverted() const;
    void print() const;
};

Fraction operator*(Fraction left, Fraction right);
Fraction operator/(const Fraction& left, const Fraction& right);
bool operator==(Fraction left, Fraction right);
bool operator!=(const Fraction& left, const Fraction& right);
bool operator>(Fraction left, Fraction right);
bool operator<(Fraction left, Fraction right);
bool operator>=(const Fraction& left, const Fraction& right);
bool operator<=(const Fraction& left, const Fraction& right);
std::ostream& operator<<(std::ostream& os, const Fraction& obj);
std::istream& operator>>(std::istream& is, Fraction& obj);