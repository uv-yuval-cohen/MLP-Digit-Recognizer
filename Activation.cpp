//
// Created by Yuval Cohen on 01/03/2024.
//
#include "Activation.h"
namespace activation
{

    Matrix relu (const Matrix &x)
    {
      Matrix result = x; // Copy x to apply changes
      for (int i = 0; i < x.get_rows () * x.get_cols (); ++i)
      {
        // Apply ReLU treating very small positive numbers as zero
        result[i] = std::max (0.0F, result[i]);
      }
      return result;
    }

    Matrix softmax (const Matrix &x)
    {
      Matrix result = x; // Copy x to apply changes
      float sum_exp = 0.0F;

      // Compute the sum of exponentials
      for (int i = 0; i < x.get_rows () * x.get_cols (); ++i)
      {
        result[i] = std::exp (result[i]);
        sum_exp += result[i];
      }

      //Divide each exponentiated value by the sum of all exponentiated values
      for (int i = 0; i < x.get_rows () * x.get_cols (); ++i)
      {
        result[i] /= sum_exp;
      }

      return result;
    }

}