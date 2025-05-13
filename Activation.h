// Activation.h
#ifndef ACTIVATION_H
#define ACTIVATION_H

#include "Matrix.h"

namespace activation {
    Matrix relu(const Matrix &vec);
    Matrix softmax(const Matrix &vec);
}


#endif //ACTIVATION_H