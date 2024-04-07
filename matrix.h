/*
 * data types
 */

typedef struct Matrix {
    float* values;
    int rows;
    int columns;
} Matrix;

/*
 * functions
 */

int add(Matrix* min1, Matrix* min2, Matrix* mout);
int subtract(Matrix* min1, Matrix* min2, Matrix* mout);
int multiply(Matrix* min1, Matrix* min2, Matrix* mout);
