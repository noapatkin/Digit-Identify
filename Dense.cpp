#include "Dense.h"
#include "stdio.h"
#include "Matrix.h"

typedef Matrix(*act_func)(const Matrix&);

Dense::Dense(const Matrix& weights, const Matrix& bias,
             act_func ActivationFunction):
_weights(weights), _bias(bias), _ActivationFunction(ActivationFunction){};
const Matrix& Dense::get_weights() const{
    return _weights;
}
const Matrix& Dense::get_bias() const{
    return _bias;
}
act_func Dense::get_activation() const{
    return _ActivationFunction;
}
Matrix Dense::operator()(const Matrix& input) const{
    Matrix to_calc = _weights*input + _bias;
    return _ActivationFunction(to_calc);
}

