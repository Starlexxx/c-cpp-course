#ifndef PROJECT_INCLUDE_MATRIX_H_
#define PROJECT_INCLUDE_MATRIX_H_

#include <stddef.h>

#define NUM_OF_PARAMS 2
#define PARAM_VALUE 1
#define MATRIX_EXISTS_ERR -2
#define MATRIX_PARAM_ERR -3
#define SQUARE_MATRIX_ERROR -4
#define VAL_ERROR -5
#define MATR_LIMIT_ERROR -6

typedef struct Matrix {
  size_t col;
  size_t row;
  double *data;
} Matrix;

// Init/release operations
Matrix *create_matrix_from_file(const char *path_file);
Matrix *create_matrix(size_t rows, size_t cols);
int free_matrix(Matrix *matrix);

// Basic operations
int get_rows(const Matrix *matrix, size_t *rows);
int get_cols(const Matrix *matrix, size_t *cols);
int get_elem(const Matrix *matrix, size_t row, size_t col, double *val);
int set_elem(Matrix *matrix, size_t row, size_t col, double val);

// Math operations
Matrix *mul_scalar(const Matrix *matrix, double val);
Matrix *transp(const Matrix *matrix);

Matrix *sum(const Matrix *l, const Matrix *r);
Matrix *sub(const Matrix *l, const Matrix *r);
Matrix *mul(const Matrix *l, const Matrix *r);

// Extra operations
int det(const Matrix *matrix, double *val);
Matrix *adj(const Matrix *matrix);
Matrix *inv(const Matrix *matrix);

#endif  // PROJECT_INCLUDE_MATRIX_H_
