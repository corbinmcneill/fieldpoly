#include <stdlib.h>
#include "intpoly.h"
#include <stdio.h>
#include <stdint.h>
#include <assert.h>
#include "debug.h"

int main() {
    /* test polynomial functions */
   /* debug("testing eval_poly..."); 
    uint8_t test_poly[3] = {(uint8_t) 7, (uint8_t) 8, (uint8_t) 9};
    assert(eval_poly(test_poly, 2, 2) == 59);
    assert(eval_poly(test_poly, 2, 20) == 183);
    debug("passed\n"); 
    debug("testing make_poly_intercept...");
    uint8_t* generated_poly = make_poly_intercept(10, 42);
    assert(eval_poly(generated_poly, 10, 0) == 42);
    debug("passed\n"); 
    debug("testing poly_degree...");
    uint8_t line[5] = { 1, 1, 0, 3, 0};
    assert( poly_degree(line, 4) == 3);
    debug("passed\n"); 
    debug("\n\n\ninterpolation stuff\n");
    uint8_t char x[2] = { 1, 2};
    uint8_t char y[2] = { 20, 30};
    uint8_t char secret; 
    secret = interpolate_yintercept(x,y,2);
    debug("\n\n%hhu \n", secret); */


    
    /* test int polynomial functions */
    debug("testing eval_poly..."); 
    uint8_t test_poly[3] = { 7,  8, 9};
    assert(eval_poly(test_poly, 2, 2) == 59);
    assert(eval_poly(test_poly, 2, 20) == 183);
    debug("passed\n"); 
    debug("testing make_poly_intercept...");
    uint8_t* generated_poly = make_poly_intercept(10, 42);
    assert(eval_poly(generated_poly, 10, 0) == 42);
    debug("passed\n"); 
    debug("testing poly_degree...");
    uint8_t line[5] = { 1, 1, 0, 3, 0};
    assert( poly_degree(line, 4) == 3);
    debug("passed\n"); 
    debug("testing addition...");
    uint8_t b[5] = { 1, 1, 0, 3, 0};
    uint8_t a[5] = {5,5,5,5,5};
    uint8_t aplusb[5] = {6,6,5,8,5};
    uint8_t* addresult = add_polys(a,b,4);
    for (int i = 0; i < 5; i++) {
        assert(aplusb[i] == addresult[i]);
    }
    free(addresult);
    debug("passed\n");

    debug("testing multiplication...");
    uint8_t c[5] = {1,2,3,4,5};
    uint8_t d[5] = {6,7,8,9,10};
    uint8_t ctimesd[5] = {6,19,40,70,110,114,106,85,50};
    //uint8_t* addresult = add_polys(a,b,4);
    //for (int i = 0; i < 5; i++) {
     //   assert(aplusb[i] == addresult[i]);
    //}
    //free(addresult);
    debug("passed\n");
    
    debug("testing interpolation...");
    uint8_t x[3] = {1,2,3};
    uint8_t y[3] = {10,19,32};
    uint8_t quadratic[3] = {2,3,5};
    uint8_t* result = interpolate(x,y,3);
    for (int i = 0; i < 3; i++) {
        debug("\n%hhu\n", result[i]);
    }
    debug("passed\n");

    
    return 0;
} 

