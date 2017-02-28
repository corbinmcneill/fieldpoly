#ifndef FIELDPOLY_H
#define FIELDPOLY_H
 
#include "element.h"
#define MAX_DEGREE 100

typedef struct poly {
    int degree;
    element_t** coeffs;
} poly_t;

/*
 * Frees a polynomial 
 *
 * poly - an initialized polynomial
 */
void poly_free(poly_t* poly);
/* 
 * Evaluates poly at x 
 *
 * poly - the polynomial to evaluate
 * x - the point to evaluate the polynomial at
 *
 * Returns a pointer to the result of the evaluation.
 * CALLER MUST FREE THE RETURNED POINTER 
 */
element_t* eval_poly(poly_t* poly, element_t* x);
/* 
 * Initializes a polynomial of a given degree over the same field as a given
 * element
 *
 * degree - the degree of the polynomial
 * init_element - an element of the field this function constructs the polynomial
 * over
 *
 * Returns a pointer to the generated polynomial.
 * CALLER MUST CALL poly_free ON THE RETURNED POINTER
 */
poly_t* poly_init(int degree, element_t* init_element);
// Same as poly_init, but randomizes coefficients
poly_t* rand_poly(int degree, element_t* init_element);
/* Same as rand_poly, but the second arguement specifys what the y-intercept of
 * the generated polynomial should be.
 */
poly_t* rand_poly_intercept(int degree, element_t* intercept);
/* 
 * Adds two polynomials
 *
 * polya, polyb - the two polynomials to add
 *
 * Returns the result of the addition.
 * CALLER MUST CALL poly_free ON THE RETURNED POINTER
 */
poly_t* add_polys(poly_t* polya, poly_t* polyb);
/*
 * Multiplies two polynomials 
 *
 * polya,polyb - the two polynomials to multiple
 * CALLER MUST CALL poly_free ON THE RETURNED POINTER
 */
poly_t* mult_polys(poly_t* polya, poly_t* polyb);
/*
 * Interpolates a polynomial based on n points
 *
 * x - the x values of the points used
 * y - the y values of the points used
 * n - the size of the x and y arrays
 *
 * Returns a polynomial of degree <= n-1 that passes through all of the given points
 * CALLER MUST CALL poly_free ON THE RETURNED POINTER
 */
poly_t* interpolate(element_t** x, element_t** y, int n);
/* 
 * scales a polynomial by a constant
 *
 * a - the polynomial to scale
 * scalar - the scalar to multiply the polynomial by
 *
 */
void scale(poly_t* a, element_t* scalar);
/*
 * Copies a polynomial
 *
 * polya - a pointer to a polynomial pointer 
 * polyb - a pointer to an initialized polynomial
 *
 * The function initializes polya and set all of it's fields to be the same as
 * polyb. 
 * CALLER MUST CALL poly_free ON *polya
 */
void deepcopy(poly_t** polya, poly_t* polyb);

#endif
