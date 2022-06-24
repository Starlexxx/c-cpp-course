#include "matrix.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

Matrix *create_matrix(size_t rows, size_t cols) {
  if (rows == 0 || cols == 0) {
    return NULL;
  }

  Matrix *matr = malloc(sizeof(Matrix));
  if (matr == NULL) {
    return NULL;
  }

  matr->col = cols;
  matr->row = rows;
  matr->data = calloc(1, matr->row * matr->col * sizeof(double));

  if (matr->data == NULL) {
    free_matrix(matr);
    return NULL;
  }
  return matr;
}

int free_matrix(Matrix *matrix) {
  free(matrix->data);
  free(matrix);
  return 0;
}

Matrix *create_matrix_from_file(const char *path_file) {
  FILE *file = fopen(path_file, "r");
  if (file == NULL) {
    return NULL;
  }

  size_t rows = 0;
  size_t cols = 0;
  if (fscanf(file, "%zu %zu", &rows, &cols) < NUM_OF_PARAMS) {
    fclose(file);
    return NULL;
  }

  Matrix *matr = create_matrix(rows, cols);
  if (matr == NULL) {
    fclose(file);
    return NULL;
  }

  for (size_t i = 0; i < matr->row; ++i) {
    for (size_t j = 0; j < matr->col; ++j) {
      if (fscanf(file, "%lf", &matr->data[i * cols + j]) < PARAM_VALUE) {
        free_matrix(matr);
        matr = NULL;
      }
    }
  }
  fclose(file);
  return matr;
}

int get_rows(const Matrix *matrix, size_t *rows) {
  if (matrix == NULL) {
    return MATRIX_EXISTS_ERR;
  }

  if (rows == NULL) {
    return MATRIX_PARAM_ERR;
  }

  *rows = matrix->row;
  return 0;
}

int get_cols(const Matrix *matrix, size_t *cols) {
  if (matrix == NULL) {
    return MATRIX_EXISTS_ERR;
  }

  if (cols == NULL) {
    return MATRIX_PARAM_ERR;
  }

  *cols = matrix->col;
  return 0;
}

int get_elem(const Matrix *matrix, size_t row, size_t col, double *val) {
  if (matrix == NULL) {
    return MATRIX_EXISTS_ERR;
  }

  if (val == NULL) {
    return VAL_ERROR;
  }

  if (matrix->row <= row || matrix->col <= col) {
    return MATR_LIMIT_ERROR;
  }

  *val = matrix->data[row * matrix->col + col];
  return 0;
}

int set_elem(Matrix *matrix, size_t row, size_t col, double val) {
  if (matrix == NULL) {
    return MATRIX_EXISTS_ERR;
  }

  if (matrix->row <= row || matrix->col <= col) {
    return MATR_LIMIT_ERROR;
  }

  (matrix->data[row * matrix->col + col]) = val;
  return 0;
}

Matrix *mul_scalar(const Matrix *matrix, double val) {
  if (matrix == NULL || matrix->data == NULL) {
    return NULL;
  }

  Matrix *matr = create_matrix(matrix->row, matrix->col);
  if (matr == NULL) {
    return NULL;
  }

  for (size_t i = 0; i < matr->row; ++i) {
    for (size_t j = 0; j < matr->col; ++j) {
      matr->data[i * matr->col + j] = matrix->data[i * matrix->col + j] * val;
    }
  }
  return matr;
}

Matrix *transp(const Matrix *matrix) {
  if (matrix == NULL) {
    return NULL;
  }

  Matrix *matr = create_matrix(matrix->col, matrix->row);
  if (matr == NULL) {
    return NULL;
  }

  for (size_t i = 0; i < matr->row; ++i) {
    for (size_t j = 0; j < matr->col; ++j) {
      matr->data[i * matr->col + j] = matrix->data[j * matrix->col + i];
    }
  }
  return matr;
}

Matrix *sum(const Matrix *l, const Matrix *r) {
  if (l == NULL || r == NULL) {
    return NULL;
  }

  Matrix *matr = create_matrix(l->row, l->col);
  if (matr == NULL) {
    return NULL;
  }

  for (size_t i = 0; i < matr->row; ++i) {
    for (size_t j = 0; j < matr->col; ++j) {
      matr->data[i * matr->col + j] =
          l->data[i * l->col + j] + r->data[i * r->col + j];
    }
  }
  return matr;
}

Matrix *sub(const Matrix *l, const Matrix *r) {
  if (l == NULL || r == NULL) {
    return NULL;
  }

  Matrix *matr = create_matrix(l->row, l->col);
  if (matr == NULL) {
    return NULL;
  }

  for (size_t i = 0; i < matr->row; ++i) {
    for (size_t j = 0; j < matr->col; ++j) {
      matr->data[i * matr->col + j] =
          l->data[i * l->col + j] - r->data[i * r->col + j];
    }
  }
  return matr;
}

Matrix *mul(const Matrix *l, const Matrix *r) {
  if (l == NULL || r == NULL) {
    return NULL;
  }

  Matrix *matr = create_matrix(l->row, r->col);
  if (matr == NULL) {
    return NULL;
  }

  for (size_t i = 0; i < l->row; ++i) {
    for (size_t j = 0; j < r->col; ++j) {
      for (size_t k = 0; k < l->col; ++k) {
        matr->data[i * matr->col + j] +=
            l->data[i * l->col + k] * r->data[k * r->col + j];
      }
    }
  }
  return matr;
}

static Matrix *minor_matrix(const Matrix *matrix, size_t col, size_t row) {
  if (matrix == NULL) {
    return NULL;
  }

  Matrix *matr = create_matrix(matrix->row - 1, matrix->col - 1);
  if (matr == NULL) {
    return NULL;
  }

  int matr_i = 0;
  int matr_j = 0;
  for (size_t i = 0; i < matrix->row; ++i) {
    if (i == row) {
      continue;
    }
    for (size_t j = 0; j < matrix->col; ++j) {
      if (j == col) {
        continue;
      }
      matr->data[matr_i * matr->col + matr_j] =
          matrix->data[i * matrix->col + j];
      ++matr_j;
    }
    matr_j = 0;
    ++matr_i;
  }
  return matr;
}

static double get_det(const Matrix *matrix) {
  if (matrix == NULL) {
    return MATRIX_EXISTS_ERR;
  }

  double sign = 1;
  if (matrix->col == 1) {
    return *(matrix->data);
  }

  if (matrix->col == 2) {
    return matrix->data[0] * matrix->data[3] -
           matrix->data[1] * matrix->data[2];
  }
  double determinant = 0.0;
  for (size_t j = 0; j < matrix->col; ++j) {
    Matrix *minor = minor_matrix(matrix, j, 0);

    determinant += *(matrix->data + j) * get_det(minor) * sign;
    sign *= -1;

    free_matrix(minor);
  }
  return determinant;
}

int det(const Matrix *matrix, double *val) {
  if (matrix == NULL) {
    return MATRIX_EXISTS_ERR;
  }

  if (val == NULL) {
    return VAL_ERROR;
  }

  if (matrix->col != matrix->row) {
    return SQUARE_MATRIX_ERROR;
  }

  *val = get_det(matrix);
  return 0;
}

Matrix *adj(const Matrix *matrix) {
  if (matrix == NULL) {
    return NULL;
  }

  Matrix *transp_matr = transp(matrix);
  Matrix *matr = create_matrix(matrix->row, matrix->col);

  if (transp_matr == NULL || matr == NULL) {
    return NULL;
  }

  double sign = -1;
  for (size_t i = 0; i < matrix->row; ++i) {
    for (size_t j = 0; j < matrix->col; ++j) {
      Matrix *minor = minor_matrix(transp_matr, j, i);
      if (minor == NULL) {
        return NULL;
      }
      matr->data[i * matr->col + j] = pow(sign, i + j) * get_det(minor);
      free_matrix(minor);
    }
  }

  free_matrix(transp_matr);
  return matr;
}

Matrix *inv(const Matrix *matrix) {
  if (matrix->data == NULL || matrix->col != matrix->row) {
    return NULL;
  }

  double d = 0;
  if (det(matrix, &d) != 0) {
    return NULL;
  }

  if (matrix->row == 1) {
    Matrix *matr = create_matrix(matrix->row, matrix->col);
    if (matr == NULL) {
      return NULL;
    }
    if (d == 0) {
      return NULL;
    }
    matr->data[0] = 1.0 / d;
    return matr;
  }

  Matrix *adj_matrix = adj(matrix);
  Matrix *matr = mul_scalar(adj_matrix, 1.0 / d);

  if (adj_matrix == NULL || matr == NULL) {
    return NULL;
  }

  free_matrix(adj_matrix);
  return matr;
}
