#include <assert.h>
#include <stdlib.h>
#include <time.h>
#ifndef FIELDPOLY
#define FIELDPOLY
#include "fieldpoly.h"
#endif /* FIELDPOLY */
#include "debug.h"
#include "string.h"


void getSmallerLarger(poly_t* polya, poly_t* polyb, poly_t** larger, poly_t** smaller); 

poly_t* poly_init(int degree, element_t* init_element) {
    poly_t* polyn = malloc(sizeof(poly_t));
    polyn->degree = degree;
    polyn->element_size = init_element->size;
    polyn->coeffs = malloc(sizeof(element_t*)*(degree+1)); 
    for (int i = 0; i <= degree; i++) {
        polyn->coeffs[i] = malloc(init_element->size);
        assign(polyn->coeffs[i],init_element);  
    }
    return polyn;
}

void poly_free(poly_t* polyn) {
    for (int i = 0; i <= polyn->degree; i++){ 
        free(polyn->coeffs[i]);
    }
    free(polyn->coeffs);
    free(polyn);
}



void rand_poly(poly_t* result) {
    debug("entering rand poly\n");
    int i;
    for (i=0; i<= result->degree; i++) {
        debug("randomizing coeff %d\n", i);
        f_rand(result->coeffs[i]);
        debug("done randomizing coeff %d\n", i);
    }   
    debug("exiting rand poly\n");
}

void rand_poly_intercept(int degree, element_t* intercept, poly_t* result) {
    int i;
    *(result->coeffs[0]) = *intercept;
    for (i=1; i<degree+1; i++) {
           f_rand(result->coeffs[i]);
    }   
    result->degree = degree;
}

// returned pointer must be freed
element_t* eval_poly(poly_t* poly, element_t* x) {
    element_t* toReturn = malloc(x->size);
    element_t* workingX = malloc(x->size);
    assign(toReturn,x);
    assign(workingX,x);
    f_add_id(toReturn);    
    f_mult_inv(workingX);    
    element_t* temp = malloc(x->size);
    for (int i=0; i<= poly->degree; i++) {
        assign(temp,workingX); 
        f_mult(temp,poly->coeffs[i]);
        f_add(toReturn, temp);
        f_mult(workingX,x);
    }   
    free(workingX);
    free(temp);
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
// returned pointer must be freed
poly_t* add_polys(poly_t *polya, poly_t *polyb) {
    poly_t* result = poly_init(polya->degree,polya->coeffs[0]); 
    poly_t *larger, *smaller;
    getSmallerLarger(polya,polyb,&larger,&smaller);
    int i;
    for (i = 0; i < smaller->degree+1; i++) {
        f_addr(polya->coeffs[i], polyb->coeffs[i], result->coeffs[i]);
    }
    for (; i < larger->degree+1; i++) {
        result->coeffs[i] = larger->coeffs[i];
    }
    return result;
}

// returned pointer must be freed
poly_t* mult_polys(poly_t* polya, poly_t* polyb) {
    element_t* temp = malloc(polya->coeffs[0]->size);
    assign(temp, polya->coeffs[0]);
    f_add_id(temp);
    int resultdegree = polya->degree+polyb->degree;
    poly_t* result = poly_init(resultdegree,temp); 
    poly_t *larger, *smaller;
    getSmallerLarger(polya,polyb,&larger,&smaller);
    
    for (int i = 0; i <= larger->degree; i++) {
       for (int j = 0; j <= smaller->degree; j++) {
          f_multr(larger->coeffs[i], smaller->coeffs[j], temp); 
          f_add(result->coeffs[i+j],temp);
       }
    }
    free(temp);
    return result;
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
