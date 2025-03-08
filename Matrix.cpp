//
// Created by Yuval Cohen on 29/02/2024.
//
#include "Matrix.h"
#define EPSILON 0.001F
#define THRESHOLD 0.1F

Matrix::Matrix (int rows, int cols)
{
  if (rows <= 0 || cols <= 0)
  {
    throw std::exception ();
  }
  else
  {
    this->dimensions.rows = rows;
    this->dimensions.cols = cols;
  }
  this->elements = new float[this->dimensions.rows * this->dimensions.cols] ();
  // Initialize all elements to 0.
}

// Default constructor
Matrix::Matrix ()
{
  this->dimensions.rows = 1;
  this->dimensions.cols = 1;
  this->elements = new float[1] (); // Initialize the single element to 0.
}

Matrix::Matrix (const Matrix &m)
{
  this->dimensions = m.dimensions;
  this->elements = new float[m.dimensions.rows * m.dimensions.cols];
  // Copy the elements from m to this matrix
  for (int i = 0; i < this->dimensions.rows * this->dimensions.cols; ++i)
  {
    this->elements[i] = m.elements[i];
  }
}

// Destructor
Matrix::~Matrix ()
{
  delete[] this->elements; // Release the allocated memory
}

// Getters
// Returns the number of rows in the matrix.
int Matrix::get_rows () const
{
  return this->dimensions.rows;
}

// Returns the number of columns in the matrix.
int Matrix::get_cols () const
{
  return this->dimensions.cols;
}

// Transforms a matrix into its transpose matrix.
Matrix &Matrix::transpose ()
{
  // If the matrix is square, we can transpose without allocating new memory.
  if (this->dimensions.rows == this->dimensions.cols)
  {
    for (int i = 0; i < this->dimensions.rows; ++i)
    {
      for (int j = i + 1; j < this->dimensions.cols; ++j)
      {
        std::swap (this->elements[i * this->dimensions.cols + j],
                   this->elements[j * this->dimensions.cols + i]);
      }
    }
  }
  else
  { // The matrix is not square
    // Allocate new memory for the transposed matrix
    float *new_elements = new float[this->dimensions.rows
                                    * this->dimensions.cols];
    for (int i = 0; i < this->dimensions.rows; ++i)
    {
      for (int j = 0; j < this->dimensions.cols; ++j)
      {
        new_elements[j * this->dimensions.rows + i] = this->elements[
            i * this->dimensions.cols + j];
      }
    }
    // Delete the old elements array
    delete[] this->elements;
    // Swap the dimensions
    std::swap (this->dimensions.rows, this->dimensions.cols);
    // Set the elements to the new array
    this->elements = new_elements;
  }
  return *this;
}

Matrix &Matrix::vectorize ()
{
  this->dimensions.rows = this->dimensions.rows * this->dimensions.cols;
  this->dimensions.cols = 1;
  return *this;
}

void Matrix::plain_print () const
{
  for (int i = 0; i < dimensions.rows; ++i)
  {
    for (int j = 0; j < dimensions.cols; ++j)
    {
      std::cout << elements[i * dimensions.cols + j] << " ";
    }
    std::cout << "\n";
  }
}

Matrix Matrix::dot (const Matrix &m) const
{
  if (this->dimensions.rows != m.dimensions.rows
      || this->dimensions.cols != m.dimensions.cols)
  {
    throw std::exception ();
  }

  Matrix result (this->dimensions.rows, this->dimensions.cols);
  for (int i = 0; i < this->dimensions.rows; ++i)
  {
    for (int j = 0; j < this->dimensions.cols; ++j)
    {
      result.elements[i * dimensions.cols + j] =
          this->elements[i * dimensions.cols + j]
          * m.elements[i * dimensions.cols + j];
    }
  }
  return result;
}

float Matrix::norm () const
{
  float sum = 0.0;
  for (int i = 0; i < dimensions.rows * dimensions.cols; ++i)
  {
    sum += (elements[i] * elements[i]);
  }
  return std::sqrt (sum);
}

int Matrix::argmax () const
{
  int index = 0;
  float max_value = elements[0];

  for (int i = 1; i < dimensions.rows * dimensions.cols; ++i)
  {
    if (elements[i] > max_value)
    {
      max_value = elements[i];
      index = i;
    }
  }

  return index;
}

float Matrix::sum () const
{
  float sum = 0;
  for (int i = 0; i < dimensions.rows * dimensions.cols; ++i)
  {
    sum += elements[i];
  }
  return sum;
}

Matrix Matrix::rref () const
{
  Matrix result (*this);
  float epsilon = EPSILON;
  int lead = 0;

  for (int r = 0; r < result.dimensions.rows; ++r)
  {
    if (lead >= result.dimensions.cols)
    { break; }

    if (!result.find_pivot_row_and_make_lead_one (r, lead, epsilon))
    {
      ++lead;
      if (lead == result.dimensions.cols)
      {
        result.move_zero_rows_to_bottom ();
        break;
      }
      --r; // Retry the same row with the next lead
      continue;
    }

    result.process_column (r, lead, epsilon);
    ++lead;
  }

  result.move_zero_rows_to_bottom ();
  return result;
}

void Matrix::swap_rows (int i, int j)
{
  if (i >= dimensions.rows || j >= dimensions.rows || i < 0 || j < 0)
  {
    throw std::exception ();
  }

  for (int k = 0; k < dimensions.cols; ++k)
  {
    std::swap (elements[i * dimensions.cols + k],
               elements[j * dimensions.cols + k]);
  }
}

void Matrix::scale_row (int i, float factor)
{
  if (i >= dimensions.rows || i < 0)
  {
    throw std::exception ();
  }
  if (factor == 0.0F)
  {
    throw std::exception ();
  }

  for (int j = 0; j < dimensions.cols; ++j)
  {
    elements[i * dimensions.cols + j] *= factor;
  }
}

void Matrix::add_multiple_of_row (int source_row, int target_row, float factor)
{
  if (source_row >= dimensions.rows || target_row >= dimensions.rows
      || source_row < 0 || target_row < 0)
  {
    throw std::exception ();
  }

  for (int k = 0; k < dimensions.cols; ++k)
  {
    elements[target_row * dimensions.cols + k] +=
        factor * elements[source_row * dimensions.cols + k];
  }
}

bool Matrix::is_row_zero (int row_index) const
{
  // Check each element in the row.
  for (int j = 0; j < dimensions.cols; ++j)
  {
    // If any element is not approximately zero, the row is not a zero row.
    if (std::abs (elements[row_index * dimensions.cols + j]) > EPSILON)
    {
      return false;
    }
  }
  // If all elements are approximately zero, return true.
  return true;
}

void Matrix::move_zero_rows_to_bottom ()
{
  int last_nonzero_row = dimensions.rows - 1;

  for (int i = 0; i <= last_nonzero_row; ++i)
  {
    bool is_zero_row = true;
    for (int j = 0; j < dimensions.cols && is_zero_row; ++j)
    {
      if (std::abs (elements[i * dimensions.cols + j]) > EPSILON)
      {
        is_zero_row = false;
      }
    }

    if (is_zero_row)
    {
      // Find the last non-zero row to swap with
      while (last_nonzero_row > i && is_row_zero (last_nonzero_row))
      {
        --last_nonzero_row;
      }
      if (last_nonzero_row > i)
      {
        swap_rows (i, last_nonzero_row);
        --last_nonzero_row; // Update the position of the last non-zero row
      }
    }
  }
}

bool
Matrix::find_pivot_row_and_make_lead_one (int &r, int &lead, float epsilon)
{
  for (int i = r; i < dimensions.rows; ++i)
  {
    if (std::abs (elements[i * dimensions.cols + lead]) >= epsilon)
    {
      if (i != r)
      {
        swap_rows (i, r);
      }
      scale_row (r, 1.0F / elements[r * dimensions.cols + lead]);
      return true;
    }
  }
  return false; // No valid pivot found
}

void Matrix::process_column (int r, int lead, float epsilon)
{
  for (int i = 0; i < dimensions.rows; ++i)
  {
    if (i != r && std::abs (elements[i * dimensions.cols + lead])
                  >= epsilon)
    {
      add_multiple_of_row (r, i,
                           -elements[i * dimensions.cols + lead]);
    }
  }
}

Matrix &Matrix::operator+= (const Matrix &rhs)
{
  if (this->dimensions.rows != rhs.dimensions.rows
      || this->dimensions.cols != rhs.dimensions.cols)
  {
    throw std::exception ();
  }
  for (int i = 0; i < dimensions.rows * dimensions.cols; ++i)
  {
    this->elements[i] += rhs.elements[i];
  }
  return *this;
}

Matrix Matrix::operator+ (const Matrix &rhs) const
{
  Matrix result = *this; // Copy current matrix
  result += rhs;         // Use addition assignment to add rhs to the copy
  return result;
}

Matrix &Matrix::operator= (const Matrix &rhs)
{
  if (this == &rhs)
  {
    return *this;
  } // Handle self-assignment

  // If dimensions are different, reallocate space
  if (this->dimensions.rows != rhs.dimensions.rows
      || this->dimensions.cols != rhs.dimensions.cols)
  {
    delete[] this->elements;
    this->dimensions = rhs.dimensions;
    this->elements = new float[dimensions.rows * dimensions.cols];
  }

  // Copy elements
  std::copy (rhs.elements, rhs.elements +
                           (dimensions.rows
                            * dimensions.cols), this->elements);
  return *this;
}

Matrix Matrix::operator* (const Matrix &rhs) const
{
  if (this->dimensions.cols != rhs.dimensions.rows)
  {
    throw std::exception ();
  }
  // Initialize result matrix with zeros
  Matrix result (this->dimensions.rows, rhs.dimensions.cols);

  for (int i = 0; i < result.dimensions.rows; ++i)
  {
    for (int j = 0; j < result.dimensions.cols; ++j)
    {
      for (int k = 0; k < this->dimensions.cols; ++k)
      {
        result.elements[i * result.dimensions.cols + j] +=
            this->elements[i * this->dimensions.cols + k]
            * rhs.elements[k * rhs.dimensions.cols + j];
      }
    }
  }
  return result;
}

// Scalar multiplication on the right: Matrix * float
Matrix Matrix::operator* (float scalar) const
{
  Matrix result (this->dimensions.rows, this->dimensions.cols);
  for (int i = 0; i < this->dimensions.rows * this->dimensions.cols; ++i)
  {
    result.elements[i] = this->elements[i] * scalar;
  }
  return result;
}

// Scalar multiplication on the left: float * Matrix
Matrix operator* (float scalar, const Matrix &m)
{
  return m * scalar; // Reuse the implementation of scalar multiplication on
  // the right
}

// Parenthesis indexing for non-const objects
float &Matrix::operator() (int row, int col)
{
  if (row >= dimensions.rows || col >= dimensions.cols || row < 0 || col < 0)
  {
    throw std::exception ();
  }
  return elements[row * dimensions.cols + col];
}

// Parenthesis indexing for const objects
const float &Matrix::operator() (int row, int col) const
{
  if (row >= dimensions.rows || col >= dimensions.cols || row < 0 || col < 0)
  {
    throw std::exception ();
  }
  return elements[row * dimensions.cols + col];
}

// Bracket indexing for non-const objects
float &Matrix::operator[] (int index)
{
  if (index >= dimensions.rows * dimensions.cols || index < 0)
  {
    throw std::exception ();
  }
  return elements[index];
}

// Bracket indexing for const objects
const float &Matrix::operator[] (int index) const
{
  if (index >= dimensions.rows * dimensions.cols || index < 0)
  {
    throw std::exception ();
  }
  return elements[index];
}

std::ostream &operator<< (std::ostream &os, const Matrix &m)
{
  for (int i = 0; i < m.get_rows (); ++i)
  {
    for (int j = 0; j < m.get_cols (); ++j)
    {
      //if the element is greater than 0.1, print '**'
      if (m (i, j) > THRESHOLD)
      {
        os << "**";
      }
      else
      {
        os << "  "; // Otherwise, print double space
      }
    }
    os << std::endl; // After each row, print a newline
  }
  return os; // Return the stream for chaining
}

//std::istream &operator>> (std::istream &is, Matrix &m)
//{
//  for (int i = 0; i < m.get_rows () * m.get_cols (); ++i)
//  {
//    if (!(is >> m.elements[i]))
//    {
//      throw std::exception ();
//    }
//  }
//  return is; // Return the stream for chaining
//}

std::istream &operator>> (std::istream &is, Matrix &m)
{
  std::streamsize read_size = m.get_rows () * m.get_cols () * sizeof (float);
  is.read ((char *) m.elements, read_size);
  if (is.gcount () != read_size)
  {
    throw std::exception ();
  }
  return is;
}

