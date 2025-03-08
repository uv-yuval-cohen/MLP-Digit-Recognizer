//
// Created by Yuval Cohen on 01/03/2024.
//

#include "Dense.h"

Dense::Dense (const Matrix &weights, const Matrix &bias,
              ActivationFunction activationFunction)
    : weights (weights), bias (bias), activation (activationFunction)
{}

const Matrix &Dense::get_weights () const
{
  return weights;
}

const Matrix &Dense::get_bias () const
{
  return bias;
}

ActivationFunction Dense::get_activation () const
{
  return activation;
}

Matrix Dense::operator() (const Matrix &input) const
{
  Matrix weighted_input = weights * input + bias; // Perform Wx + b
  return activation (weighted_input); // Apply the activation function
}
