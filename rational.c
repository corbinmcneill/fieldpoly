#include <time.h>
#include <limits.h>
#include <stdlib.h>
#include <assert.h>
#include "rational.h"

#define MAX 100

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
    
