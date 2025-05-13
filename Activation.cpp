#include "Activation.h"
#include "Matrix.h"
#include "cmath"

Matrix activation::relu(const Matrix& vec){
    Matrix rel(vec.get_rows(), vec.get_cols());
    for(int i=0; i< vec.get_cols() * vec.get_rows(); i++){
        if (vec[i] < 0){
            rel[i] = 0;
        }
        else{
            rel[i] = vec[i];
        }
    }
    return rel;
}

Matrix activation::softmax(const Matrix& vec){
    Matrix soft(vec.get_rows(), vec.get_cols());
    float exp_vec_sum = 0;
    for(int i=0; i<vec.get_cols()*vec.get_rows(); i++){
        soft[i] = std::exp(vec[i]);
        exp_vec_sum += soft[i];
    }
    for(int i=0; i< vec.get_cols()*vec.get_rows(); i++){
        soft[i] /= exp_vec_sum;
    }
    return soft;
}
