#include <time.h>
#include <limits.h>
#include <stdlib.h>
#include <assert.h>
#include "rational.h"

#define MAX 100

element_t rat_super;
char initialized = 0;

void field_init();

void rat_add(rat_element_t* a, rat_element_t* b, rat_element_t* result) {
    assert(a->contents.denom != 0);
    assert(b->contents.denom != 0);
    if (a->contents.num == 0) {
        *result = *b;
    }
    else if (b->contents.num == 0) {
        *result = *a;
    }
    else {
        result->contents.num = (a->contents.num * b->contents.denom) + (b->contents.num * a->contents.denom);
        result->contents.denom = a->contents.denom * b->contents.denom;
    }
}
void rat_mult(rat_element_t* a, rat_element_t* b, rat_element_t* result) {
    assert(a->contents.denom != 0);
    assert(b->contents.denom != 0);
    result->contents.num = a->contents.num * b->contents.num;
    result->contents.denom = a->contents.denom * b->contents.denom;
}
void rat_add_inv(rat_element_t* a, rat_element_t* result) {
    assert(a->contents.denom != 0);
    result->contents.num = -(a->contents.num); 
    result->contents.denom = a->contents.denom;
}
void rat_mult_inv(rat_element_t* a, rat_element_t* result) {
    assert(a->contents.denom != 0);
    result->contents.num = a->contents.denom; 
    result->contents.denom = a->contents.num; 
}
void rat_add_id(rat_element_t* result) {
    result->contents.num = 0;
    result->contents.denom = 1;
}
void rat_mult_id(rat_element_t* result) {
    result->contents.num = 1;
    result->contents.denom = 1;
}
void rat_randelement(rat_element_t* result) {
    srand(time(NULL));
    result->contents.num = rand() % MAX;
    result->contents.denom = (rand() % MAX) +1;
}
    
void rat_init(rat_element_t* a) {
    field_init();
    a->super = &rat_super;
}
void field_init() {
    if (initialized)
        return;
    rat_super.field->add = &rat_add;
    rat_super.field->mult = &rat_mult;
    rat_super.field->addinv = &rat_add_inv;
    rat_super.field->multinv = &rat_mult_inv;
    rat_super.field->addid = &rat_add_id;
    rat_super.field->multid = &rat_mult_id;
    rat_super.field->randelement = &rat_randelement;
    initialized = 1;
}

