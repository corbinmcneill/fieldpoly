#include "element.h"
#define MAX_DEGREE 100

typedef struct poly {
    int degree;
    struct element* coeffs[MAX_DEGREE+1];
} poly_t;


poly_t make_poly(int degree);
element_t eval_poly(poly_t poly, element_t x);
poly_t make_poly_intercept(int degree, element_t intercept);
poly_t interpolate(element_t* x, element_t* y, int n);
poly_t add_polys(poly_t polya, poly_t polyb);
poly_t mult_polys(poly_t polya, poly_t polyb);
