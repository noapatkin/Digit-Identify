#include "MlpNetwork.h"
#include "Activation.h"
#define VEC_LENGTH 10

MlpNetwork::MlpNetwork(Matrix weights[], Matrix biases[]):_layers{
        {weights[0], biases[0], activation::relu},
        {weights[1], biases[1], activation::relu},
        {weights[2], biases[2], activation::relu},
        {weights[3], biases[3], activation::softmax}}{};
digit MlpNetwork::operator()(Matrix& input) const{
    digit dig;
    Matrix r1 = _layers[0](input);
    Matrix r2 = _layers[1](r1);
    Matrix r3 = _layers[2](r2);
    Matrix r4 = _layers[3](r3);
    int max_ind = 0;
    float max_probability = r4[0];
    for(int i=1; i<r4.get_cols()*r4.get_rows(); i++){
        if(r4[i]>max_probability){
            max_ind = i;
            max_probability = r4[i];
        }
    }
    dig.probability = max_probability;
    dig.value = max_ind;
    return dig;
}