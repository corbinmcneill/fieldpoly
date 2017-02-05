#include "element.h"
#define MAX_DEGREE 100

typedef struct poly {
    int degree;
    struct field_ops* field;
    element_t coeffs[MAX_DEGREE+1];
} poly_t;


poly_t make_poly(int degree);
element_t eval_poly(poly_t poly, element_t x);
poly_t make_poly_intercept(int degree, element_t intercept);
poly_t mult_polys(poly_t polya, poly_t polyb);
