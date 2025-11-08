// matrix-multiplication <Project2.cpp>
// ECE 312 Project 2 submission by
// Vidita Bhotika
// vb9359
// Slip days used: <0>
// Spring 2025

#include "MatrixMultiply.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

void multiplyMatrices(double a[], const uint32_t a_rows, const uint32_t a_cols,
                      double b[], const uint32_t b_cols, double c[]) {
  // https://en.wikipedia.org/wiki/Row-_and_column-major_order

  double rowSum = 0;
  for (int i = 0; i < a_rows; i++) {
    for (int j = 0; j < b_cols; j++) {
      rowSum = 0;
      for (int k = 0; k < a_cols; k++) {
        double aValue = (a[i * a_cols + k]);
        double bValue = (b[k * b_cols + j]);
        rowSum += aValue * bValue;
      }
      c[i * b_cols + j] = rowSum;
      // printf("%lf", c[i * b_cols + j]);
    }
  }
}

double **multiplyMatricesPtr(double **a, const uint32_t a_rows,
                             const uint32_t a_cols, double **b,
                             const uint32_t b_cols) {
  double rowSum = 0;
  double **c = (double **)malloc(a_rows * (sizeof(double *)));
  for (int z = 0; z < a_rows; z++) {
    *(c + z) = (double *)malloc(b_cols * sizeof(double));
  }

  for (int i = 0; i < a_rows; i++) {
    for (int j = 0; j < b_cols; j++) {
      rowSum = 0;
      for (int k = 0; k < a_cols; k++) {
        double aValue = *(*(a + i) + k); // = a[i][k]
        double bValue = *(*(b + k) + j); // = b[k][j]
        rowSum += aValue * bValue;
      }

      *(*(c + i) + j) = rowSum;
    }
  }

  if (c != NULL) {
    return c;
  }

  return NULL;
}

// https://en.wikipedia.org/wiki/Matrix_(mathematics)#Submatrix
double **createSubMatrix(double **a, const uint32_t a_rows,
                         const uint32_t a_cols, const uint32_t row_x,
                         const uint32_t col_y) {

  double **b = (double **)malloc((a_rows - 1) * (sizeof(double *)));
  for (int z = 0; z < a_rows - 1; z++) {
    *(b + z) = (double *)malloc((a_cols - 1) * sizeof(double));
  }

  int valueI = 0;
  int valueJ = 0;

  for (int i = 0; i < a_rows; i++) {
    if (i == row_x) {
      i++;
    }
    for (int j = 0; j < a_cols; j++) {
      if (j == col_y) {
        j++;
      }

      if (i != a_rows && j != a_cols) {
        *(*(b + valueI) + valueJ) = *(*(a + i) + j);
        valueJ++;
      }
    }
    valueJ = 0;

    valueI++;
  }
  return b;
}
