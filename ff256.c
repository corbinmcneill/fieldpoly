#include <time.h>
#include <limits.h>
#include <stdlib.h>
#include <assert.h>
#include "rational.h"
#include "debug.h"

void ff256_add(element_t* a, element_t* b, element_t* result) {
	ff256_element_t* x = (ff256_element_t*) a;
	ff256_element_t* y = (ff256_element_t*) b;
	ff256_element_t* output = (ff256_element_t*) result;

	output->contents.val = (x->contents.val) ^ (y->contents.val);
}

void ff256_mult(element_t* a, element_t* b, element_t* result) {

}

void ff256_add_inv(element_t* a, element_t* result) {
	ff256_element_t* x = (ff256_element_t*) a;
	ff256_element_t* output = (ff256_element_t*) result;

	output->contents.val = ~(x->contents.val);
}

void ff256_mult_inv(element_t* a, element_t* result) {

}

void ff256_add_id(element_t* result) {
	ff256_element_t* output = (ff256_element_t*) result;
	output->contents.val = 0;
}

void ff256_mult_id(element_t* result) {
	ff256_element_t* output = (ff256_element_t*) result;
	output->contents.val = 1;
}

void ff256_randelement(element_t* result) {
	ff256_element_t* output = (ff256_element_t*) result;
	srand(time(NULL));
	output->contents.num = (uint8_t) rand();
}
 
void ff256_init(ff256_element_t* a) {
	a->field = &ff256_ops;
	a->contents.val = 0;
}
