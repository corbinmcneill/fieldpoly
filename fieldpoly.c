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
    result.coeffs[0] = intercept;
    for (i=1; i<degree+1; i++) {
        //TODO: fix
        //result.coeffs[i] = (uint8_t) rand();
    }   
    result.degree = degree;
    return result;
}

element_t eval_poly(poly_t poly, element_t x) {
    // TODO see if this method works for all fields
    element_t toReturn = f_mult_id(&x);
    element_t workingX = f_add_id(&x);
    int i;
    for (i=0; i<= poly.degree; i++) {
        element_t temp = f_mult(&workingX,&(poly.coeffs[i]) );
        toReturn = f_add(&toReturn, &temp);
        workingX = f_mult(&workingX,&x);
    }   
    return toReturn;
}

poly_t interpolate(element_t* x, element_t *y, int n) {
    //TODO write
    poly_t toReturn;
    element_t* a = calloc(n, sizeof(element_t));
    for (int i = 0; i < n; i++) {
        a[i] = y[i];
    }   
    for (int k = 1; k <= n; k++) {
        for (int j = n; j >= k; j--) { 
            element_t temp1 = f_sub(&a[j],&a[j-1]);
            element_t temp2 = f_sub(&x[j], &x[j-k]);
            a[j] = f_div(&temp1,&temp2);
        }
    }   
    
    free(a);
    return toReturn;
}
// adds the two polynomials, caller must free the returned polynomial
poly_t add_polys(poly_t *polya, poly_t *polyb) {
    poly_t result;  
    result.field = polya->field;
    poly_t *larger, *smaller;
    if (polya->degree >= polyb->degree) {
        larger = polya;
        smaller = polyb;
    } else { 
        larger = polyb;
        smaller = polya;
    }
        
    int i;
    for (i = 0; i < smaller->degree+1; i++) {
        result.coeffs[i] = f_add(&polya->coeffs[i], &polyb->coeffs[i]);
    }
    for (; i < larger->degree+1; i++) {
        result.coeffs[i] = larger->coeffs[i];
    }

    return result;
}

// multiplies the two polynomials, caller must free the returned polynomial
poly_t mult_polys(poly_t polya, poly_t polyb) {
}
