// Matrix.h
#ifndef MATRIX_H
#include "stdio.h"
#include "iostream"
#define MATRIX_H



// You don't have to use the struct. Can help you with MlpNetwork.h
struct matrix_dims {
    int rows, cols;
};

class Matrix{
public:
	Matrix(int rows=1, int cols=1);
	Matrix(const Matrix& m);
	~Matrix();
	int get_rows() const;
	int get_cols() const;
    Matrix& transpose();
    Matrix& vectorize();
	void plain_print() const;
	Matrix dot(const Matrix& m) const;
	float norm() const;
	Matrix rref() const;
	int argmax() const;
	float sum() const;
    Matrix& operator+=(const Matrix& m);
	Matrix operator+(const Matrix& m) const;
	Matrix& operator=(const Matrix& m);
	Matrix operator*(const Matrix& m) const;
	friend Matrix operator*(float c, const Matrix& m);
	Matrix operator*(float c) const;
	float& operator()(int i, int j);
    float operator()(int i, int j) const;
    float& operator[](int k);
    float operator[](int k) const;

    friend std::ostream& operator<<(std::ostream &os, const Matrix& m);
	friend std::istream& operator>>(std::istream &is,  Matrix& m);
private:
	int _rows, _cols;
	float *_matrix;
};





#endif //MATRIX_H