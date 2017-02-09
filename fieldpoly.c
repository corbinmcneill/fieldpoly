#include <stdlib.h>
#include "fieldpoly.h"
#include <time.h>


void getSmallerLarger(poly_t* polya, poly_t* polyb, poly_t** larger, poly_t** smaller); 

void poly_init(poly_t* polyn, int degree, int element_size, void* element_init(element_t*)) {
    polyn->degree = degree;
    polyn->element_size = element_size;
    polyn->coeffs = malloc((degree+1)* element_size); 
    for (int i = 0; i <= degree; i++) {
        element_init(polyn->coeffs[i]);
    }
}

void rand_poly(int degree, poly_t* result) {
    srand(time(NULL));
    int i;
    for (i=0; i<degree+1; i++) {
        f_rand(result->coeffs[i]);
    }   
}

void rand_poly_intercept(int degree, element_t* intercept, poly_t* result) {
    int i;
    *result.coeffs[0] = *intercept;
    for (i=1; i<degree+1; i++) {
           f_rand(result->coeffs[i]);
    }   
    result->degree = degree;
}

element_t eval_poly(poly_t* poly, element_t* x) {
    element_t toReturn = *x;
    element_t workingX = *x;
    f_mult_inv(&toReturn);    
    f_mult_inv(&workingX);    
    element_t temp;
    for (int i=0; i<= poly->degree; i++) {
        temp = workingX; 
        f_mult(&temp,poly->coeffs[i]);
        f_add(&toReturn, &temp);
        f_mult(&workingX,x);
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
    element_t temp;
    for (int k = 1; k <= n; k++) {
        for (int j = n; j >= k; j--) { 
            f_sub(&a[j],&a[j-1]);
            temp = x[j];
            f_sub(&temp, &x[j-k]);
            f_div(&a[j],&temp);
        }
    }   
    
    free(a);
    return toReturn;
}

void add_polysr(poly_t *polya, poly_t *polyb, poly_t* result) {
    result->field = polya->field;
    poly_t *larger, *smaller;
    getSmallerLarger(polya,polyb,&larger,&smaller);
    int i;
    for (i = 0; i < smaller->degree+1; i++) {
        f_addr(polya->coeffs[i], polyb->coeffs[i], result->coeffs[i]);
    }
    for (; i < larger->degree+1; i++) {
        result->coeffs[i] = larger->coeffs[i];
    }
}

void mult_polysr(poly_t* polya, poly_t* polyb, poly_t* result) {
    result->field = polya->field;
    poly_t *larger, *smaller;
    getSmallerLarger(polya,polyb,&larger,&smaller);

}

void getSmallerLarger(poly_t* polya, poly_t* polyb, poly_t** larger, poly_t** smaller) {
    if (polya->degree >= polyb->degree) {
        *larger = polya;
        *smaller = polyb;
    } else { 
        *larger = polyb;
        *smaller = polya;
    }
} 
