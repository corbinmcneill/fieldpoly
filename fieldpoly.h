#ifndef FIELDPOLY_H
#define FIELDPOLY_H
 
#include "element.h"
#define MAX_DEGREE 100

typedef struct poly {
    int degree;
    element_t** coeffs;
} poly_t;

void poly_free(poly_t* polyn);
element_t* eval_poly(poly_t* poly, element_t* x);
poly_t* poly_init(int degree, element_t* init_element);
poly_t* rand_poly(int degree, element_t* init_element);
poly_t* rand_poly_intercept(int degree, element_t* intercept);
poly_t* add_polys(poly_t* polya, poly_t* polyb);
poly_t* mult_polys(poly_t* polya, poly_t* polyb);
poly_t* interpolate(element_t** x, element_t** y, int n);
void scale(poly_t* a, element_t* scalar);
void deepcopy(poly_t* polya, poly_t* polyb);

#endif
