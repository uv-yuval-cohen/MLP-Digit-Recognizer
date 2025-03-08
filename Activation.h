// Activation.h
#ifndef ACTIVATION_H
#define ACTIVATION_H

#include "Matrix.h"

// Insert Activation namespace here...
namespace activation
{
    /**
 * Applies the ReLU activation function to each element of the input matrix.
 * @param x The input matrix.
 * @return A matrix with the ReLU function applied element-wise.
 */
    Matrix relu(const Matrix &x);

/**
 * Applies the softmax activation function to the input matrix,
 * treating it as a single vector.
 * @param x The input matrix.
 * @return A matrix representing the softmax probabilities.
 */
    Matrix softmax(const Matrix &x);
}

#endif //ACTIVATION_H