#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <assert.h>
#include "debug.h"
#include "rational.h"
#include "ff256.h"
#include "fieldpoly.h"
#include "primeField.h"

poly_t* rpoly(int degree, char name,int tabs); 
void test_ff256();
void test_primeField();
int test();

int main() {
    
    //for (int i = 0; i < 1000000; i++)
        test();
    return 0;
}

int test() {
    debug("Rational elements test\n\n\n");
    debug("\tsize of rational element: %ld\n", sizeof(rat_element_t));
    rat_element_t* testelement = malloc(sizeof(rat_element_t)); 
    debug("\tcreated element\n");
    rat_init(testelement);
    debug("\tinitialized element \n");
    f_rand((element_t*) testelement);
    debug("\tset the rational to a random number\n");
    debug("\tnumerator: %d, denominator: %d\n", testelement->contents.num, testelement->contents.denom);
    debug("\n\n\n");


    debug("Polynomial tests\n\n\n");
    debug("\t1. Create random polynomial \n\n");
    rat_element_t* init_element = malloc(sizeof(rat_element_t));
    rat_init(init_element);
    debug("\t\tcreating a random polynomial p\n");
    poly_t* testpoly1 = rand_poly(3, (element_t*) init_element);
    debug("\t\tp was filled with random numbers:\n");
    rat_element_t* thing;
    for (int i = 0; i <= testpoly1->degree; i++) {
        thing = ((rat_element_t*) testpoly1->coeffs[i] );
        debug("\t\tp's coeff #%d: %d/%d \n", i, thing->contents.num, thing->contents.denom); 
    }
    debug("\n\t2. Evaluate p\n\n");
    rat_element_t* eval_element = malloc(sizeof(rat_element_t));
    assign((element_t*) eval_element, (element_t*) testelement);
    eval_element->contents.num = 0;
    eval_element->contents.denom = 1;
    rat_element_t* val = (rat_element_t*) eval_poly(testpoly1, (element_t*) eval_element); 
    debug("\t\tevaluated p @ x = 0, got %d/%d\n", val->contents.num, val->contents.denom);
    free(val);
    eval_element->contents.num = 1;
    eval_element->contents.denom = 1;
    val = (rat_element_t*) eval_poly(testpoly1, (element_t*) eval_element); 
    debug("\t\tevaluated p @ x = 1, got %d/%d\n", val->contents.num, val->contents.denom);
    free(val);

    debug("\n\t3. Adding a + b = c, where a and b are random polynomials\n\n");
    poly_t* addpoly1 = rpoly(3,'a',2);
    poly_t* addpoly2 = rpoly(3,'b',2);
    poly_t* addresult = add_polys(addpoly1, addpoly2);

    rat_t a1,a2,r;
    debug("\t\t a  +  b  =  c\n");
    for (int i = 0; i <= addpoly1->degree; i++) {
        a1 = ((rat_element_t*) addpoly1->coeffs[i])->contents;
        a2 = ((rat_element_t*) addpoly2->coeffs[i])->contents;
        r = ((rat_element_t*) addresult->coeffs[i])->contents;
        debug("\t\t%d/%d + %d/%d = %d/%d\n",a1.num,a1.denom,a2.num, a2.denom, r.num,r.denom);
    }

    debug("\n\t4. Multiplying x + y = z, where x and y are random polynomials\n\n");
    poly_t* multpoly1 = rpoly(3,'x',2);
    poly_t* multpoly2 = rpoly(3,'y',2);
    poly_t* multresult = mult_polys(multpoly1, multpoly2);

    rat_t m1,m2,mr;
    debug("\n\t\t(");
    for (int i = 0; i <= multpoly1->degree; i++) {
        m1 = ((rat_element_t*) multpoly1->coeffs[i])->contents;
        debug(" +%d/%dx^%d ",m1.num,m1.denom,i);
    }
    debug(")*");
    debug("(");
    for (int i = 0; i <= multpoly2->degree; i++) {
        m2 = ((rat_element_t*) multpoly2->coeffs[i])->contents;
        debug(" +%d/%dx^%d ",m2.num,m2.denom,i);
    }
    debug(") = \n");
    debug("\t\t(");
    
    for (int i = 0; i <= multresult->degree; i++) {
        mr = ((rat_element_t*) multresult->coeffs[i])->contents;
        debug(" +%d/%dx^%d ",mr.num,mr.denom,i);
    }
    debug(")");
    debug("\n");

    debug("\n\t5. interpolating k from some of it's points\n\n");
    rat_element_t* x[4]; 
    rat_element_t* y[4];
    rat_element_t* tempinterp;  
    poly_t* ogpoly = rpoly(3,'k',2);
    poly_t* interppoly;
    debug("\n\t\tpoints:\n");
    for (int i = 0; i < 4; i++) {
        x[i] = malloc(sizeof(rat_element_t));
        y[i] = malloc(sizeof(rat_element_t));
        rat_init(x[i]);
        x[i]->contents.num = i;
        x[i]->contents.denom = 1;
        tempinterp = (rat_element_t*) eval_poly(ogpoly, (element_t*) x[i]);
        assign((element_t*) y[i], (element_t*) tempinterp);
        debug("\t\t(%d/%d,%d/%d)\n", x[i]->contents.num, x[i]->contents.denom, y[i]->contents.num, y[i]->contents.denom);
        free(tempinterp);
    }
    debug("\n\t\toriginal polynomial: \n\t\t");
    for (int i = 0; i <= ogpoly->degree; i++) {
        mr = ((rat_element_t*) ogpoly->coeffs[i])->contents;
        debug(" +%d/%dx^%d ",mr.num,mr.denom,i);
    }
    interppoly = interpolate((element_t**) x, (element_t**) y,4);
    debug("\n\t\tinterpolated polynomial: \n\t\t");
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

poly_t* rpoly(int degree, char name,int tabs) {
    rat_element_t* init_element = malloc(sizeof(rat_element_t));
    rat_init(init_element);
    poly_t* testpoly1 = rand_poly(degree, (element_t*) init_element);
    rat_element_t* thing;
    for (int i = 0; i <= testpoly1->degree; i++) {
        thing = ((rat_element_t*) testpoly1->coeffs[i] );
        for (int k = 0; k < tabs; k++)
            debug("\t");
        debug("%c's  coeff #%d: %d/%d \n", name,i, thing->contents.num, thing->contents.denom); 
    }
    free(init_element);
    return testpoly1;
}
    

void test_primeField() {
    gf257_element_t a;
    gf257_init(&a);
    gf257_randelement(&a.super);
    //printf("%d\n",a.contents);

    gf257_element_t b;
    gf257_init(&b);
    gf257_randelement(&b.super);
    //printf("%d\n",b.contents);

    gf257_element_t c;
    gf257_init(&c);
    gf257_randelement(&c.super);
    //printf("%d\n",c.contents);

    gf257_element_t result;
    gf257_init(&result);

    gf257_add((element_t*)(&a), (element_t*)(&b), (element_t*)&result);
    //printf("%d\n",result.contents);

}

