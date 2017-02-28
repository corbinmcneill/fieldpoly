#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <assert.h>
#include "debug.h"
#include "rational.h"
#include "ff256.h"
#include "fieldpoly.h"
#include "primeField.h"

poly_t* rpoly(); 
void test_ff256();
void test_primeField();
int test();

int main() {
    test();
    return 0;
}

int test() {
    debug("testing rational elements, size: %ld\n", sizeof(rat_element_t));
    rat_element_t* testelement = malloc(sizeof(rat_element_t)); 
    debug("created\n");
    rat_init(testelement);
    debug("initialized\n");
    f_rand((element_t*) testelement);
    debug("\nand set the rational to a random number\n");
    debug("numerator: %d, denominator: %d\n", testelement->contents.num, testelement->contents.denom);


    rat_element_t* init_element = malloc(sizeof(rat_element_t));
    rat_init(init_element);
    debug("\ncreating a random polynomial\n");
    debug("allocated space for polynomial\n");
    poly_t* testpoly1 = rand_poly(3, (element_t*) init_element);
    debug("created polynomial\n");
    debug("fill polynomial with random numbers\n");
    debug("poly was filled with random numbers\n");
    rat_element_t* thing;
    for (int i = 0; i <= testpoly1->degree; i++) {
        thing = ((rat_element_t*) testpoly1->coeffs[i] );
        debug("coeff #%d: %d/%d \n", i, thing->contents.num, thing->contents.denom); 
    }
    rat_element_t* eval_element = malloc(sizeof(rat_element_t));
    assign((element_t*) eval_element, (element_t*) testelement);
    eval_element->contents.num = 0;
    eval_element->contents.denom = 1;
    rat_element_t* val = (rat_element_t*) eval_poly(testpoly1, (element_t*) eval_element); 
    debug("evaluated poly @ x = 0, got %d/%d\n", val->contents.num, val->contents.denom);
    free(val);
    eval_element->contents.num = 1;
    eval_element->contents.denom = 1;
    val = (rat_element_t*) eval_poly(testpoly1, (element_t*) eval_element); 
    debug("evaluated poly @ x = 1, got %d/%d\n", val->contents.num, val->contents.denom);
    free(val);

    poly_t* addpoly1 = rpoly(3);
    poly_t* addpoly2 = rpoly(3);
    poly_t* addresult = add_polys(addpoly1, addpoly2);

    rat_t a1,a2,r;
    for (int i = 0; i <= addpoly1->degree; i++) {
        a1 = ((rat_element_t*) addpoly1->coeffs[i])->contents;
        a2 = ((rat_element_t*) addpoly2->coeffs[i])->contents;
        r = ((rat_element_t*) addresult->coeffs[i])->contents;
        debug(" %d/%d + %d/%d = %d/%d\n",a1.num,a1.denom,a2.num, a2.denom, r.num,r.denom);
    }


    poly_t* multpoly1 = rpoly(3);
    poly_t* multpoly2 = rpoly(3);
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

    rat_element_t* x[4]; 
    rat_element_t* y[4];
    rat_element_t* tempinterp;  
    poly_t* ogpoly = rpoly(3);
    poly_t* interppoly;
    for (int i = 0; i < 4; i++) {
        x[i] = malloc(sizeof(rat_element_t));
        y[i] = malloc(sizeof(rat_element_t));
        rat_init(x[i]);
        x[i]->contents.num = i;
        x[i]->contents.denom = 1;
        tempinterp = (rat_element_t*) eval_poly(ogpoly, (element_t*) x[i]);
        assign((element_t*) y[i], (element_t*) tempinterp);
        free(tempinterp);
    }
    debug("\noriginal polynomial: \n");
    for (int i = 0; i <= ogpoly->degree; i++) {
        mr = ((rat_element_t*) ogpoly->coeffs[i])->contents;
        debug(" +%d/%dx^%d ",mr.num,mr.denom,i);
    }
    debug("beginning interpolation\n");
    interppoly = interpolate((element_t**) x, (element_t**) y,4);
    debug("\ninterpolated polynomial: \n");
    for (int i = 0; i <= interppoly->degree; i++) {
        mr = ((rat_element_t*) interppoly->coeffs[i])->contents;
        debug(" +%d/%dx^%d ",mr.num,mr.denom,i);
    }
    debug("\n");
    free(testelement);
    free(init_element);
    free(eval_element);
    poly_free(interppoly);
    poly_free(addpoly1);
    poly_free(addpoly2);
    poly_free(addresult);
    poly_free(multpoly1);
    poly_free(multpoly2);
    poly_free(multresult);
    poly_free(testpoly1); 
    poly_free(ogpoly); 
    for (int i = 0; i < 4; i++) {
        free(x[i]);
        free(y[i]);
    }
    
	//test_ff256();

//    printf("Testing primeField: \n");

    //test_primeField();

    return 0;
} 

poly_t* rpoly(int degree) {
    rat_element_t* init_element = malloc(sizeof(rat_element_t));
    rat_init(init_element);
    poly_t* testpoly1 = rand_poly(degree, (element_t*) init_element);
    rat_element_t* thing;
    for (int i = 0; i <= testpoly1->degree; i++) {
        thing = ((rat_element_t*) testpoly1->coeffs[i] );
        debug("coeff #%d: %d/%d \n", i, thing->contents.num, thing->contents.denom); 
    }
    free(init_element);
    return testpoly1;
}
    

void test_primeField() {
    gf257_element_t a;
    gf257_init(&a);
    gf257_randelement(&a.super);
    printf("%d\n",a.contents);

    gf257_element_t b;
    gf257_init(&b);
    gf257_randelement(&b.super);
    printf("%d\n",b.contents);

    gf257_element_t c;
    gf257_init(&c);
    gf257_randelement(&c.super);
    printf("%d\n",c.contents);

    gf257_element_t result;
    gf257_init(&result);

    gf257_add((element_t*)(&a), (element_t*)(&b), (element_t*)&result);
    printf("%d\n",result.contents);

}

