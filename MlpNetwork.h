// MlpNetwork.h
#ifndef MLPNETWORK_H
#define MLPNETWORK_H

#include "Dense.h"

#define MLP_SIZE 4

/**
 * @struct digit
 * @brief Identified (by Mlp network) digit with
 *        the associated probability.
 * @var value - Identified digit value
 * @var probability - identification probability
 */
typedef struct digit
{
    unsigned int value;
    float probability;
} digit;

const matrix_dims img_dims = {28, 28};
const matrix_dims weights_dims[] = {{128, 784},
                                    {64,  128},
                                    {20,  64},
                                    {10,  20}};
const matrix_dims bias_dims[] = {{128, 1},
                                 {64,  1},
                                 {20,  1},
                                 {10,  1}};

// Insert MlpNetwork class here...
class MlpNetwork
{
 private:
  Dense layers[MLP_SIZE]; // Array of Dense layers

 public:
  /**
 * Constructs an MLP network using specified weights and biases for each layer.
 * @param weights Array of weight matrices for the network layers.
 * @param biases Array of bias vectors for the network layers.
 */
  MlpNetwork (const Matrix weights[], const Matrix biases[]);

  /**
  * Predicts the digit from the input matrix.
  * @param input Matrix representing an image.
  * @return digit struct with the predicted digit and its probability.
  */
  digit operator() (const Matrix &input) const;
};

#endif // MLPNETWORK_H