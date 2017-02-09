#include <time.h>
#include <limits.h>
#include <stdlib.h>
#include <assert.h>
#include "rational.h"
#include "debug.h"

#define MAX 100

char initialized = 0;

void field_init();

void rat_add(element_t* a, element_t* b, element_t* result) {
	rat_element_t* x = (rat_element_t*) a;
	rat_element_t* y = (rat_element_t*) b;
	rat_element_t* output = (rat_element_t*) result;
    assert(x->contents.denom != 0);
    assert(y->contents.denom != 0);
    if (x->contents.num == 0) {
        *output = *y;
    }
    else if (y->contents.num == 0) {
        *output = *x;
    }
    else {
        output->contents.num = (x->contents.num * y->contents.denom) + (y->contents.num * x->contents.denom);
        output->contents.denom = x->contents.denom * y->contents.denom;
    }
}
void rat_mult(element_t* a, element_t* b, element_t* result) {
	rat_element_t* x = (rat_element_t*) a;
	rat_element_t* y = (rat_element_t*) b;
	rat_element_t* output = (rat_element_t*) result;
    assert(x->contents.denom != 0);
    assert(y->contents.denom != 0);
    output->contents.num = x->contents.num * y->contents.num;
    output->contents.denom = x->contents.denom * y->contents.denom;
}
void rat_add_inv(element_t* a, element_t* result) {
	rat_element_t* x = (rat_element_t*) a;
	rat_element_t* output = (rat_element_t*) result;
    assert(x->contents.denom != 0);
    output->contents.num = -(x->contents.num); 
    output->contents.denom = x->contents.denom;
}
void rat_mult_inv(element_t* a, element_t* result) {
	rat_element_t* x = (rat_element_t*) a;
	rat_element_t* output = (rat_element_t*) result;
    assert(x->contents.denom != 0);
    output->contents.num = x->contents.denom; 
    output->contents.denom = x->contents.num; 
}
void rat_add_id(element_t* result) {
	rat_element_t* output = (rat_element_t*) result;
    output->contents.num = 0;
    output->contents.denom = 1;
}
void rat_mult_id(element_t* result) {
	rat_element_t* output = (rat_element_t*) result;
    output->contents.num = 1;
    output->contents.denom = 1;
}
void rat_randelement(element_t* result) {
	rat_element_t* output = (rat_element_t*) result;
    srand(time(NULL));
    output->contents.num = rand() % MAX;
    output->contents.denom = (rand() % MAX) +1;
}

static field_ops_t rat_ops = {
    .add = rat_add,
    .mult = rat_mult,
    .addinv = rat_add_inv,
    .multinv = rat_mult_inv,
    .addid = rat_add_id,
    .multid = rat_mult_id,
    .randelement = rat_randelement,
};
    
void rat_init(rat_element_t* a) {
    a->super.field = &rat_ops;
    a->contents.num = 0;
    a->contents.denom = 1;
}
