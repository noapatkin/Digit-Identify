// Dense.h
#ifndef DENSE_H
#define DENSE_H

#include "Activation.h"
#include "Matrix.h"

typedef Matrix(*act_func)(const Matrix&);

class Dense{
public:
    Dense(const Matrix& weights, const Matrix& bias,
          act_func ActivationFunction);
    const Matrix& get_weights() const;
    const Matrix& get_bias() const;
    act_func get_activation() const;
    Matrix operator()(const Matrix& input) const;

private:
    Matrix _weights;
    Matrix _bias;
    act_func _ActivationFunction;
};










#endif //DENSE_H