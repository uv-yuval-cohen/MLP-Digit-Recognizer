//
// Created by Yuval Cohen on 01/03/2024.
//
#include "MlpNetwork.h"

// Constructor implementation
MlpNetwork::MlpNetwork (const Matrix weights[], const Matrix biases[]) :
layers {
    Dense(weights[0], biases[0], activation::relu),
    Dense(weights[1], biases[1], activation::relu),
    Dense(weights[2], biases[2], activation::relu),
    Dense(weights[3], biases[3], activation::softmax)
}
{
  // Verify that the weights and biases arrays are the correct size
  for (int i = 0; i < MLP_SIZE; ++i)
  {
    if (weights[i].get_rows () != weights_dims[i].rows
        || weights[i].get_cols () != weights_dims[i].cols)
    {
      throw std::exception ();
    }
    if (biases[i].get_rows () != bias_dims[i].rows
        || biases[i].get_cols () != bias_dims[i].cols)
    {
      throw std::exception ();
    }

  }
}


digit MlpNetwork::operator()(const Matrix& input) const {
  Matrix current_output = input;

  // Apply each layer in the network to the input
  for (int i = 0; i < MLP_SIZE; ++i) {
    current_output = layers[i](current_output);
  }


  int max_index = 0;
  float max_value = current_output(0, 0);
  for (int i = 1; i < current_output.get_rows(); ++i) {
    if (current_output(i, 0) > max_value) {
      max_value = current_output(i, 0);
      max_index = i;
    }
  }

  // Return the digit with the associated probability
  return {static_cast<unsigned int>(max_index), max_value};
}
