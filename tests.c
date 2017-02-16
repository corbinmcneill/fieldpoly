#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <assert.h>
#include "debug.h"
#include "rational.h"
#include "fieldpoly.h"

poly_t* rpoly(); 

int main() {
    debug("testing rational elements, size: %d\n", sizeof(rat_element_t));
    rat_element_t testelement; 
    debug("created\n");
    rat_init(&testelement);
    debug("initialized\n");
    f_rand(&testelement.super);
    debug("\nand set the rational to a random number\n");
    debug("numerator: %d, denominator: %d\n", testelement.contents.num, testelement.contents.denom);

    rat_element_t init_element;
    rat_init(&init_element);
    debug("\ncreating a random polynomial\n");
    debug("allocated space for polynomial\n");
    poly_t* testpoly1 = poly_init(3, (element_t*) &init_element);
    debug("ensuring elements have been initialized to 0\n");
    for (int i = 0; i<= 3; i++) {
        debug("coeff %d: %d\n", i, ((rat_element_t*) testpoly1->coeffs[i])->contents.num); 
        assert(((rat_element_t*) testpoly1->coeffs[i])->contents.num == 0);
    }
    debug("created polynomial\n");
    debug("fill polynomial with random numbers\n");
    rand_poly(testpoly1);
    debug("poly was filled with random numbers\n");
    rat_element_t* thing;
    for (int i = 0; i <= testpoly1->degree; i++) {
        thing = ((rat_element_t*) testpoly1->coeffs[i] );
        debug("coeff #%d: %d/%d \n", i, thing->contents.num, thing->contents.denom); 
    }
    rat_element_t* eval_element = malloc(sizeof(rat_element_t));
    assign((element_t*) eval_element, (element_t*) &testelement);
    eval_element->contents.num = 0;
    eval_element->contents.denom = 1;
    rat_element_t* val = (rat_element_t*) eval_poly(testpoly1, (element_t*) eval_element); 
    debug("evaluated poly @ x = 0, got %d/%d\n", val->contents.num, val->contents.denom);
    eval_element->contents.num = 1;
    eval_element->contents.denom = 1;
    val = (rat_element_t*) eval_poly(testpoly1, (element_t*) eval_element); 
    debug("evaluated poly @ x = 1, got %d/%d\n", val->contents.num, val->contents.denom);

    poly_t* addpoly1 = rpoly();
    poly_t* addpoly2 = rpoly();
    poly_t* addresult = add_polys(addpoly1, addpoly2);

    rat_t a1,a2,r;
    for (int i = 0; i <= addpoly1->degree; i++) {
        a1 = ((rat_element_t*) addpoly1->coeffs[i])->contents;
        a2 = ((rat_element_t*) addpoly2->coeffs[i])->contents;
        r = ((rat_element_t*) addresult->coeffs[i])->contents;
        debug(" %d/%d + %d/%d = %d/%d\n",a1.num,a1.denom,a2.num, a2.denom, r.num,r.denom);
    }


    poly_t* multpoly1 = rpoly();
    poly_t* multpoly2 = rpoly();
    debug("multiplying\n");
    poly_t* multresult = mult_polys(multpoly1, multpoly2);

    rat_t m1,m2,mr;
    for (int i = 0; i <= multpoly1->degree; i++) {
        m1 = ((rat_element_t*) multpoly1->coeffs[i])->contents;
        debug(" +%d/%dx^%d ",m1.num,m1.denom,i);
    }
    debug("\n");
    
    for (int i = 0; i <= multpoly2->degree; i++) {
        m2 = ((rat_element_t*) multpoly2->coeffs[i])->contents;
        debug(" +%d/%dx^%d ",m2.num,m2.denom,i);
    }
    debug("\n");
    
    for (int i = 0; i <= multresult->degree; i++) {
        mr = ((rat_element_t*) multresult->coeffs[i])->contents;
        debug(" +%d/%dx^%d ",mr.num,mr.denom,i);
    }
    debug("\n");
    


    free(eval_element);
    poly_free(testpoly1);



    return 0;
} 

poly_t* rpoly() {
    rat_element_t init_element;
    rat_init(&init_element);
    poly_t* testpoly1 = poly_init(3, (element_t*) &init_element);
    for (int i = 0; i<= 3; i++) {
        debug("coeff %d: %d\n", i, ((rat_element_t*) testpoly1->coeffs[i])->contents.num); 
        assert(((rat_element_t*) testpoly1->coeffs[i])->contents.num == 0);
    }
    rand_poly(testpoly1);
    rat_element_t* thing;
    for (int i = 0; i <= testpoly1->degree; i++) {
        thing = ((rat_element_t*) testpoly1->coeffs[i] );
        debug("coeff #%d: %d/%d \n", i, thing->contents.num, thing->contents.denom); 
    }
    return testpoly1;
}

