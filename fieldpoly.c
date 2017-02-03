#include <stdlib.h>
#include "fieldpoly.h"
#include <time.h>

poly_t make_poly(int degree) {
    srand(time(NULL));
    poly_t result;
    int i;
    for (i=0; i<degree+1; i++) {

        //TODO fix
        //result.coeffs[i] = () rand();
    }   
    return result;
}

poly_t make_poly_intercept(int degree, element_t intercept) {
    poly_t result;
    int i;
    result.coeffs[0] = &intercept;
    for (i=1; i<degree+1; i++) {
        //TODO: fix
        //result.coeffs[i] = (uint8_t) rand();
    }   
    result.degree = degree;
    return result;
}

element_t eval_poly(poly_t poly, element_t x) {
    element_t toReturn = 0;
    element_t workingX = 1;
    int i;
    for (i=0; i<= poly.degree; i++) {
        toReturn += workingX*poly[i];
        workingX *= x;
    }   
    return toReturn;
}

poly_t interpolate(element_t* x, element_t *y, int n) {
    for (int i = 0; i < n; i++) {
        a[i] = y[i];
    }   
    for (int k = 1; k <= n; k++) {
        for (int j = n; j >= k; j--) { 
            a[j] = (a[j]-a[j-1])/(x[j] - x[j-k]);
        }
    }   
    return NULL;
}
// adds the two polynomials, caller must free the returned polynomial
poly_t add_polys(poly_t polya, poly_t polyb) {
    poly_t result; 
    for (int i = 0; i < degree +1; i++) {
        result[i] = polya[i] + polyb[i];
    }
    return result;
}

// multiplies the two polynomials, caller must free the returned polynomial
poly_t mult_polys(poly_t polya, poly_t polyb, int degree) {
}
