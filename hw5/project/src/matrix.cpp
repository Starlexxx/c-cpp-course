#include <math.h>
#include <iomanip>

#include "exceptions.h"
#include "matrix.h"

namespace prep {
Matrix::Matrix(size_t rows, size_t cols) : rows(rows), cols(cols) {
  this->data.assign(rows, std::vector<double>(cols, 0));
}

Matrix::Matrix(std::istream &is) {
  is >> rows >> cols;
  if (is.fail()) {
    throw(InvalidMatrixStream());
  }

  this->data.assign(rows, std::vector<double>(cols));
  for (auto &row : this->data) {
    for (auto &col : row) {
      is >> (col);
      if (is.fail()) {
        throw(InvalidMatrixStream());
      }
    }
  }
}

size_t Matrix::getRows() const { return rows; }

size_t Matrix::getCols() const { return cols; }

double Matrix::operator()(size_t i, size_t j) const {
  if (i >= rows || j >= cols) {
    throw(OutOfRange(i, j, *this));
  }
  return (*this).data[i][j];
}

double &Matrix::operator()(size_t i, size_t j) {
  if (i >= rows || j >= cols) {
    throw(OutOfRange(i, j, *this));
  }
  return (*this).data[i][j];
}

bool Matrix::operator==(const Matrix &rhs) const {
  if (rhs.getRows() != rows || rhs.getCols() != cols) {
    return false;
  }

  for (size_t i = 0; i < rows; ++i) {
    for (size_t j = 0; j < cols; ++j) {
      if (fabs(rhs(i, j) - (*this)(i, j)) >= DELTA) {
        return false;
      }
    }
  }
  return true;
}

bool Matrix::operator!=(const Matrix &rhs) const { return !(*this == rhs); }

Matrix Matrix::operator+(const Matrix &rhs) const {
  if (rhs.getRows() != rows || rhs.getCols() != cols) {
    throw(DimensionMismatch(*this, rhs));
  }

  Matrix res(rows, cols);
  for (size_t i = 0; i < rows; ++i) {
    for (size_t j = 0; j < cols; ++j) {
      res(i, j) = (*this)(i, j) + rhs(i, j);
    }
  }
  return res;
}

Matrix Matrix::operator-(const Matrix &rhs) const {
  if (rhs.getRows() != rows || rhs.getCols() != cols) {
    throw(DimensionMismatch(*this, rhs));
  }

  Matrix res(rows, cols);
  for (size_t i = 0; i < rows; ++i) {
    for (size_t j = 0; j < cols; ++j) {
      res(i, j) = (*this)(i, j) - rhs(i, j);
    }
  }
  return res;
}

Matrix Matrix::operator*(const Matrix &rhs) const {
  if (rhs.getRows() != cols) {
    throw(DimensionMismatch(*this, rhs));
  }

  Matrix res(rows, rhs.getCols());
  for (size_t i = 0; i < rows; ++i) {
    for (size_t j = 0; j < rhs.getCols(); ++j) {
      double sum = 0;
      for (size_t k = 0; k < cols; ++k) {
        sum += rhs(k, j) * (*this)(i, k);
      }
      res(i, j) = sum;
    }
  }
  return res;
}

Matrix Matrix::operator*(double val) const {
  Matrix res(rows, cols);
  for (size_t i = 0; i < rows; ++i) {
    for (size_t j = 0; j < cols; ++j) {
      res(i, j) = (*this)(i, j) * val;
    }
  }
  return res;
}

Matrix operator*(double val, const Matrix &matrix) { return matrix * val; }

std::ostream &operator<<(std::ostream &os, const Matrix &matrix) {
  if (os.bad()) {
    throw(InvalidMatrixStream());
  }
  os << matrix.getRows() << ' ';
  if (os.fail()) {
    throw(InvalidMatrixStream());
  }

  os << matrix.getCols() << '\n';
  if (os.fail()) {
    throw(InvalidMatrixStream());
  }

  for (size_t i = 0; i < matrix.getRows(); ++i) {
    for (size_t j = 0; j < matrix.getCols(); ++j) {
      os << std::setprecision(std::numeric_limits<double>::max_digits10)
         << matrix(i, j) << ' ';
      if (os.fail()) {
        throw(InvalidMatrixStream());
      }
    }
    os << '\n';
  }
  return os;
}

Matrix Matrix::transp() const {
  Matrix matr(cols, rows);
  for (size_t i = 0; i < cols; ++i) {
    for (size_t j = 0; j < rows; ++j) {
      matr(i, j) = (*this)(j, i);
    }
  }
  return matr;
}

static Matrix minor_matrix(Matrix matrix, size_t row, size_t col) {
  Matrix matr(matrix.getRows() - 1, matrix.getCols() - 1);
  size_t matr_i = 0;
  size_t matr_j = 0;

  for (size_t i = 0; i < matrix.getRows(); ++i) {
    if (i == row) {
      continue;
    }
    for (size_t j = 0; j < matrix.getCols(); ++j) {
      if (j == col) {
        continue;
      }
      matr(matr_i, matr_j) = matrix(i, j);
      matr_j++;
    }
    matr_j = 0;
    matr_i++;
  }
  return matr;
}

double Matrix::det() const {
  if (rows != cols) {
    throw(DimensionMismatch(*this));
  }

  double sign = 1;
  if (cols == 1) {
    return (*this)(0, 0);
  }

  if (cols == 2) {
    return (*this)(0, 0) * (*this)(1, 1) - (*this)(1, 0) * (*this)(0, 1);
  } else {
    double d = 0.0;
    for (size_t j = 0; j < cols; ++j) {
      Matrix minor = minor_matrix((*this), 0, j);
      d += (*this)(0, j) * minor.det() * sign;
      sign *= -1;
    }
    return d;
  }
}

Matrix Matrix::adj() const {
  if (cols != rows) {
    throw(DimensionMismatch(*this));
  }

  Matrix transp_matrix = this->transp();
  Matrix adj_matrix(this->getRows(), this->getRows());

  int dop_sign = 1;

  for (size_t i = 0; i < this->getRows(); i++)
    for (size_t j = 0; j < this->getRows(); j++) {
      dop_sign = (i + j) % 2 == 0 ? 1 : -1;

      Matrix matrix_minor = minor_matrix(transp_matrix, i, j);
      double det_minor = matrix_minor.det();
      adj_matrix(i, j) = det_minor * dop_sign;
    }
  return adj_matrix;
}

Matrix Matrix::inv() const {
  if (cols != rows) {
    throw(DimensionMismatch(*this));
  }

  double d = (*this).det();
  if (fabs(d) <= DELTA) {
    throw(SingularMatrix());
  }
  Matrix matr = (*this).adj() * (1.0 / d);

  return matr;
}
}  //  namespace prep
