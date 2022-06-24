#include "matrix.h"

#include <stdio.h>

int main(void) {
    Matrix* mat = create_matrix_from_file("abs.txt");
    if (mat == NULL) {
        puts("Matrix creating from file failed");
        return -1;
    }
    size_t r = 0;
    size_t c = 0;
    get_rows(mat, &r);
    get_cols(mat, &c);

    Matrix* mat2 = create_matrix(r, c);
    if (mat2 == NULL) {
        puts("Matrix creating failed");
        return -1;
    }

    double val;
    set_elem(mat2, 0, 0, 1);
    get_elem(mat2, 0, 0, &val);

    Matrix* mat3 = mul(inv(mat), adj(mat));
    if (mat3 == NULL) {
        puts("Matrix math operations failed");
        return -1;
    }

    Matrix* mat4 = mul_scalar(sum(mat, sub(mat2, mat3)), r);
    if (mat4 == NULL) {
        puts("Matrix math operations failed");
        return -1;
    }

    free_matrix(mat);
    free_matrix(mat2);
    free_matrix(mat3);
    free_matrix(mat4);

    return 0;
}
