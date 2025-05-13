#include <stdio.h>
#include <iostream>
#include "Matrix.h"
#include "cmath"
#include "cstring"
#define MIN_PRINT 0.1
#define INVALID_ARITHMETICS "matrix are not in the right size"
#define INDEX_ERR "index over limit"
#define INVALID_DIMS "invalid dims"
#define INVALID_STREAM_SIZE "stream is short"
#define UNREADABLE_MATRIX "matrix is unreadable"

Matrix::Matrix(int rows, int cols) {
    if(rows <= 0 || cols <= 0){
        throw std::invalid_argument(INVALID_DIMS);
    }
    _rows = rows;
    _cols = cols;
    _matrix = new float[rows*cols];
    for (int i = 0; i < rows*cols; i++) {
        _matrix[i] = 0;
    }
}

Matrix::Matrix(const Matrix& m){
    _rows = m.get_rows();
    _cols = m.get_cols();
    _matrix = new float[_rows*_cols];
    for (int i = 0; i < _rows*_cols; i++) {
        _matrix[i] = m[i];
    }
}

Matrix::~Matrix(){
    delete[] _matrix;
}

int Matrix::get_rows() const{
    return _rows;
}

int Matrix::get_cols() const{
    return _cols;
}

Matrix& Matrix::transpose(){
    float* transposed = new float[_rows*_cols];
    for (int i = 0; i < _cols; i++) {
        for (int j = 0; j < _rows; j++) {
            transposed[i*_rows+j] = _matrix[j*_cols+i];
        }
    }
    int temp = _rows;
    _rows = _cols;
    _cols = temp;
    delete[] _matrix;
    _matrix = transposed;
    return *this;
}

Matrix& Matrix::vectorize(){
    _rows = _cols*_rows;
    _cols = 1;
    return *this;
}

void Matrix::plain_print() const{
    for (int i = 0; i < _rows; i++) {
        for (int j = 0; j < _cols; j++) {
            std::cout << (*this)(i,j) << " ";
        }
        std::cout << "\n";
    }
}

Matrix Matrix::dot(const Matrix& m) const{
    if(_rows != m._rows || _cols != m._cols){
        throw std::invalid_argument(INVALID_DIMS);
    }
    Matrix dot(_rows, _cols);
    for (int i = 0; i < _rows*_cols; i++) {
        dot[i] = (*this)[i] * m[i];
    }
    return dot;
}

float Matrix::norm() const{
    float sum = 0;
    for (int i = 0; i < _rows*_cols; i++) {
        sum += _matrix[i]*_matrix[i];
    }
    return std::sqrt(sum);
}

Matrix Matrix::rref() const{
    Matrix rref(*this);
    int lead = 0;
    float temp;
    for (int r = 0; r < _rows; ++r) {
        if (lead >= _cols) {
            return rref;
        }
        int i = r;
        while (rref[i * _cols + lead] == 0) {
            ++i;
            if (i == _rows) {
                i = r;
                ++lead;
                if (lead == _cols) {
                    return rref;
                }
            }
        }
        // Swap rows r and i
        for (int j = 0; j < _cols; ++j) {
            temp = rref[r * _cols + j];
            rref[r * _cols + j] = rref[i * _cols + j];
            rref[i * _cols + j] = temp;
        }
        double lv = rref[r * _cols + lead];
        for (int j = 0; j < _cols; ++j) {
            rref[r * _cols + j] /= lv;
        }
        for (int i = 0; i < _rows; ++i) {
            if (i != r) {
                lv = rref[i * _cols + lead];
                for (int j = 0; j < _cols; ++j) {
                    rref[i * _cols + j] -= lv * rref[r * _cols + j];
                }
            }
        }
        ++lead;
    }
    return rref;
}


int Matrix::argmax() const{
    float max = _matrix[0];
    int max_index = 0;
    for (int i = 0; i < _rows*_cols; i++) {
        if(max < _matrix[i]){
            max = _matrix[i];
            max_index = i;
        }
    }
    return max_index;
}

float Matrix::sum() const{
    float sum = 0;
    for (int i = 0; i < _rows*_cols; i++) {
        sum += _matrix[i];
    }
    return sum;
}

Matrix& Matrix::operator+=(const Matrix& m){
    if(_rows != m._rows || _cols != m._cols){
        throw std::invalid_argument(INVALID_ARITHMETICS);
    }
    for (int i = 0; i < _rows*_cols; i++) {
        _matrix[i] += m[i];
    }
    return *this;
}

Matrix Matrix::operator+(const Matrix& m) const{
    if(_rows != m._rows || _cols != m._cols){
        throw std::invalid_argument(INVALID_ARITHMETICS);
    }
    Matrix add = Matrix(_rows, _cols);
    for (int i = 0; i < _rows*_cols; i++) {
        add[i] = _matrix[i] + m[i];
    }
    return add;
}

Matrix& Matrix::operator=(const Matrix& m){
    if(this != &m) {
        _rows = m.get_rows();
        _cols = m.get_cols();
        delete[] _matrix;
        _matrix = new float[_rows * _cols];
        for (int i = 0; i < _rows * _cols; i++) {
            _matrix[i] = m[i];
        }
    }
    return *this;
}

Matrix Matrix::operator*(const Matrix& m) const{
    if(_cols != m._rows){
        throw std::invalid_argument(INVALID_ARITHMETICS);
    }
    Matrix mult = Matrix(_rows, m.get_cols());
    float cord = 0;
    for(int i=0; i<_rows; i++){
        for(int j=0; j<m.get_cols(); j++){
            cord = 0;
            for(int t=0; t< _cols; t++){
                cord += (*this)(i,t) * m(t,j);
            }
            mult(i,j) = cord;
        }
    }
    return mult;
}

Matrix Matrix::operator*(float c) const{
    Matrix mult = Matrix(_rows, _cols);
    for (int i = 0; i < _rows*_cols; i++) {
        mult[i] = _matrix[i]*c;
    }
    return mult;
}

Matrix operator*(float c, const Matrix& m){
    return m*c;
}


float& Matrix::operator()(int i, int j){
    if(i*_cols+j > _rows*_cols || i<0 || j<0){
        throw std::invalid_argument(INDEX_ERR);
    }
    return _matrix[i*_cols+j];
}
float Matrix::operator()(int i, int j) const{
    if(i*_cols+j > _rows*_cols || i<0 || j<0){
        throw std::invalid_argument(INDEX_ERR);
    }
    return _matrix[i*_cols+j];
}

float& Matrix::operator[](const int k) {
    if(k > _rows*_cols || k<0){
        throw std::invalid_argument(INDEX_ERR);
    }
    return _matrix[k];
}
float Matrix::operator[](const int k) const {
    if(k > _rows*_cols || k<0){
        throw std::invalid_argument(INDEX_ERR);
    }
    return _matrix[k];
}


std::ostream& operator<<(std::ostream &os, const Matrix& m){
    for (int i = 0; i < m.get_rows(); i++) {
        for (int j = 0; j < m.get_cols(); j++) {
            if(m(i,j) > MIN_PRINT){
                os << "**";
            }
            else{
                os << "  ";
            }
        }
        os << "\n";
    }
    return os;
}

std::istream& operator>>(std::istream &is,  Matrix& m)
{
    is.seekg(0, std::ios::end);
    long int length = m.get_rows() * m.get_cols();
    if(is.tellg() < length)
    {
        throw std::invalid_argument(INVALID_STREAM_SIZE);
    }
    is.seekg(0, std::ios::beg);
    char* str = new char[length * sizeof(float)];
    is.read(str, length * sizeof(float));
    if(!is.good())
    {
        throw std::invalid_argument(UNREADABLE_MATRIX);
    }
    else{
        std::memcpy(m._matrix, str, length * sizeof(float));
    }
    delete[] str;
    return is;

}
