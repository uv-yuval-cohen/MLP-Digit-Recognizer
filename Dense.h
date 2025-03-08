// Dense.h
#ifndef DENSE_H
#define DENSE_H

#include "Activation.h"
typedef Matrix (*ActivationFunction) (const Matrix &);

// Insert Dense class here...
class Dense
{
 private:
  Matrix weights;
  Matrix bias;
  ActivationFunction activation;

 public:
  /**
 * Constructs a Dense layer with specified weights,
   * bias, and activation function.
 * @param weights The weight matrix for the layer.
 * @param bias The bias vector for the layer.
 * @param activationFunction The activation function to apply in the layer.
 */
  Dense (const Matrix &weights, const Matrix &bias,
         ActivationFunction activationFunction);

  // Getters
  /**
 * Gets the layer's weights.
 * @return Reference to the weights matrix.
 */
  const Matrix &get_weights () const;

/**
 * Gets the layer's bias.
 * @return Reference to the bias vector.
 */
  const Matrix &get_bias () const;

/**
 * Gets the layer's activation function.
 * @return The activation function.
 */
  ActivationFunction get_activation () const;

/**
 * Applies the layer operations to the input.
 * @param input The input matrix.
 * @return The result of the layer's computations.
 */
  Matrix operator() (const Matrix &input) const;

};

#endif //DENSE_H