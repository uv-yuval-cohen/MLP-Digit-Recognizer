// Matrix.h
#ifndef MATRIX_H
#define MATRIX_H

#include <cmath>
#include <iostream>

// You don't have to use the struct. Can help you with MlpNetwork.h
struct matrix_dims
{
    int rows, cols;
};

// Insert Matrix class here...
class Matrix
{
 private:
  // Pointer to the one-dimensional dynamic array of matrix elements
  float *elements;
  matrix_dims dimensions; // Using the provided struct for dimensions

  // Helping methods for rref
  void swap_rows (int i, int j);
  void scale_row (int i, float factor);
  void add_multiple_of_row (int source_row, int target_row, float factor);
  bool is_row_zero (int row_index) const;
  void move_zero_rows_to_bottom ();
  bool find_pivot_row_and_make_lead_one (int &r, int &lead, float epsilon);
  void process_column (int r, int lead, float epsilon);

 public:
  // Constructors
  /**
 * Constructs a Matrix object with the specified number of rows and columns.
 * Initializes all elements to zero.
 * @param rows The number of rows in the matrix.
 * @param cols The number of columns in the matrix.
 * @throws std::invalid_argument if rows or cols are non-positive.
 */
  Matrix (int rows, int cols);

/**
 * Default constructor. Constructs a 1x1 Matrix object
 * with the element initialized to zero.
 */
  Matrix ();

/**
 * Copy constructor. Constructs a Matrix object
 * that is a copy of the provided matrix.
 * @param m The Matrix object to copy.
 */
  Matrix (const Matrix &m);

  /**
 * Destructor. Releases any resources allocated by the Matrix object.
 */
  ~Matrix ();

  // Methods & Functions
  /**
 * Returns the number of rows in the matrix.
 * @return The number of rows.
 */
  int get_rows () const;

/**
 * Returns the number of columns in the matrix.
 * @return The number of columns.
 */
  int get_cols () const;

  /**
 * Transposes the matrix in-place, swapping rows with columns.
 * @return Reference to the current matrix.
 */
  Matrix &transpose ();

/**
 * Reshapes the matrix into a column vector.
 * @return Reference to the current matrix.
 */
  Matrix &vectorize ();

  /**
 * Prints the matrix elements to standard output in a plain format.
 */
  void plain_print () const;

/**
 * Performs element-wise multiplication (Hadamard product) with another matrix.
 * @param m The matrix to multiply with.
 * @return A new matrix that is the result of the element-wise multiplication.
 */
  Matrix dot (const Matrix &m) const;

  /**
 * Calculates the Frobenius norm of the matrix,
   * which is the square root of the sum of the squares of its elements.
 * @return The Frobenius norm of the matrix.
 */
  float norm () const;

/**
 * Transforms the matrix into its Reduced Row Echelon Form (RREF).
 * @return A new matrix that is the RREF of the original matrix.
 */
  Matrix rref () const;

/**
 * Finds the index of the maximum element in the matrix.
 * If the matrix is vectorized, it treats it as a vector.
 * @return The index of the first occurrence of the maximum element.
 */
  int argmax () const;

/**
 * Calculates the sum of all elements in the matrix.
 * @return The sum of all elements.
 */
  float sum () const;

  /**
 * Adds another matrix to this matrix element-wise.
 * @param rhs The right-hand side matrix to add.
 * @return A reference to this matrix after addition.
 */
  Matrix &operator+= (const Matrix &rhs);

/**
 * Creates a new matrix by adding another matrix to this matrix element-wise.
 * @param rhs The right-hand side matrix to add.
 * @return A new matrix that is the sum of this matrix and rhs.
 */
  Matrix operator+ (const Matrix &rhs) const;

/**
 * Copies the elements of another matrix to this matrix.
 * @param rhs The right-hand side matrix to copy from.
 * @return A reference to this matrix after copying.
 */
  Matrix &operator= (const Matrix &rhs);

/**
 * Multiplies this matrix with another matrix (matrix multiplication).
 * @param rhs The right-hand side matrix to multiply with.
 * @return A new matrix that is the product of this matrix and rhs.
 */
  Matrix operator* (const Matrix &rhs) const;

/**
 * Multiplies this matrix by a scalar value element-wise.
 * @param scalar The scalar value to multiply with.
 * @return A new matrix that is the product of this matrix and the scalar.
 */
  Matrix operator* (float scalar) const;

  /**
 * Accesses the element at the specified row and column for modification.
 * @param row The row index of the element.
 * @param col The column index of the element.
 * @return A reference to the element at the specified location.
 */
  float &operator() (int row, int col);

/**
 * Accesses the element at the specified row and column,
 * without allowing modification.
 * @param row The row index of the element.
 * @param col The column index of the element.
 * @return A const reference to the element at the specified location.
 */
  const float &operator() (int row, int col) const;

/**
 * Accesses the element at the specified index for modification,
 * treating the matrix as a 1D array.
 * @param index The index of the element in the array.
 * @return A reference to the element at the specified index.
 */
  float &operator[] (int index);

/**
 * Accesses the element at the specified index without
 * allowing modification, treating the matrix as a 1D array.
 * @param index The index of the element in the array.
 * @return A const reference to the element at the specified index.
 */
  const float &operator[] (int index) const;

  /**
 * Outputs the Matrix to provided output stream in a human-readable format.
 * @param os The output stream to write to.
 * @param m The Matrix object to output.
 * @return A reference to the output stream for chaining.
 */
  friend std::ostream &operator<< (std::ostream &os, const Matrix &m);

/**
 * Reads matrix elements from provided input stream into the Matrix object.
 * The input format should match the matrix's dimensions.
 * @param is The input stream to read from.
 * @param m The Matrix object to fill with data.
 * @return A reference to the input stream for chaining.
 */
  friend std::istream &operator>> (std::istream &is, Matrix &m);

};

Matrix operator* (float scalar, const Matrix &m);

#endif //MATRIX_H