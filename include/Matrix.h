#pragma once
#include <iostream>
#include <initializer_list>

class Matrix
{
    size_t _cols;
    size_t _rows;
    int** _matrix;

    void clear();
    void initialize(size_t rows, size_t cols);
    void initialize(int** arr, size_t rows, size_t cols);

public:
    Matrix(size_t rows, size_t cols);
    template<size_t rows, size_t cols>
    Matrix(const int(&arr)[rows][cols]);
    Matrix();
    Matrix(std::initializer_list<std::initializer_list<int>> l);
    Matrix(const Matrix& other);
    Matrix(Matrix&& other);
    ~Matrix();

    int get_rows() const;
    int get_cols() const;

    Matrix& operator=(const Matrix& other);
    Matrix& operator=(Matrix&& other);
    Matrix operator+(const Matrix& other) const;
    Matrix operator-(const Matrix& other) const;
    Matrix operator-() const;
    Matrix operator*(const Matrix& other) const;
    Matrix operator*(int value) const;
    Matrix& operator+=(const Matrix& other);
    Matrix& operator-=(const Matrix& other);
    Matrix& operator*=(const Matrix& other);
    int* operator[](size_t index);
    const int* operator[](size_t index) const;

    int determinant() const;
    int minor(size_t row, size_t col) const;
    Matrix inverse() const;
    Matrix transposed() const;

    void random();
    void print() const;
};

std::ostream& operator<<(std::ostream& os, const Matrix& obj);