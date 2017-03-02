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


// must free return 
poly_t* rand_poly(int degree, element_t* init_element) {
    poly_t* result = poly_init(degree,init_element); 
    int i;
    for (i=0; i<= result->degree; i++) {
        f_rand(result->coeffs[i]);
    }   
    return result;
}

// must free return
poly_t* rand_poly_intercept(int degree, element_t* intercept) {
    poly_t* result = poly_init(degree,intercept); 
    for (int i=1; i<degree+1; i++) {
           f_rand(result->coeffs[i]);
    }   
    result->degree = degree;
    return result;
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

// must free return 
poly_t* interpolate(element_t** x, element_t** y, int arraysize) {
    poly_t* result = NULL; 
    int elementsize = x[0]->size;
    int n = arraysize-1;
    int degree = arraysize -1;
    element_t** a = malloc((n+1)*sizeof(element_t*));
    for (int i = 0; i < n+1; i++) {
        a[i] = malloc(elementsize);
        assign(a[i],y[i]);
    }   
    element_t* temp = malloc(elementsize);
    assign(temp, x[0]);
    for (int k = 1; k <= n; k++) {
        for (int j = n; j >= k; j--) { 
            f_sub(a[j], a[j-1]);
            assign(temp, x[j]);
            f_sub(temp, x[j-k]); 
            f_div(a[j], temp);
        }
    }   
    poly_t* polys[degree+1];
    poly_t* mid_polys[degree+1];
    poly_t* temp_polys[degree+1];
    f_mult_id(temp);
    polys[0] = poly_init(0, temp); 
    for (int i = 1; i <= degree; i++){
        polys[i] = poly_init(1, temp); 
        f_add_invr(x[i-1], polys[i]->coeffs[0]);
    }
    for (int i = 0; i <= degree; i++) {
        deepcopy(&temp_polys[i],polys[i]);
        for (int j = i-1; j >= 0; j--) {
            temp_polys[j] = mult_polys(temp_polys[j+1], polys[j]);
        }
        deepcopy(&mid_polys[i],temp_polys[0]);
        for (int j = i; j >= 0; j--) {
            poly_free(temp_polys[j]);
        }
        scale(mid_polys[i], a[i]);
    }
    deepcopy(&temp_polys[0], mid_polys[0]);
    for (int i = 0; i < degree; i++) {
        temp_polys[i+1] = add_polys(temp_polys[i], mid_polys[i+1]);
    }
    deepcopy(&result, temp_polys[degree]);
    for (int f = 0; f <= degree; f++) {
        poly_free(temp_polys[f]);
        poly_free(mid_polys[f]);
        poly_free(polys[f]);
    }
    for (int i = 0; i < n+1; i++) {
        free(a[i]);
    }
    free(a);
    free(temp);
    return result;
}

// returned pointer must be freed
poly_t* add_polys(poly_t *polya, poly_t *polyb) {
    poly_t *larger, *smaller;
    getSmallerLarger(polya,polyb,&larger,&smaller);
    poly_t* result = poly_init(larger->degree,larger->coeffs[0]); 
    int i;
    for (i = 0; i < smaller->degree+1; i++) {
        f_addr(polya->coeffs[i], polyb->coeffs[i], result->coeffs[i]);
    }
    for (; i < larger->degree+1; i++) {
        assign(result->coeffs[i],larger->coeffs[i]);
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

void scale(poly_t* a, element_t* scalar) {
    for (int i = 0; i <= a->degree; i++) {
        assert(a->coeffs[i]->size != 0);
        f_mult(a->coeffs[i], scalar);
    }
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

// initializes polya 
void deepcopy(poly_t** polya, poly_t* polyb) {
    *polya = malloc(sizeof(poly_t));
    int elementsize = polyb->coeffs[0]->size;
    int degree = polyb->degree;
    (*polya)->degree = degree;
    (*polya)->coeffs = malloc(sizeof(element_t*)*(polyb->degree+1));
    for (int i = 0; i <= polyb->degree; i++) {
        assert(polyb->coeffs[i] != NULL);
        (*polya)->coeffs[i] = malloc(elementsize);
        assign((*polya)->coeffs[i],polyb->coeffs[i]);
    }
}
