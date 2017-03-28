#ifndef FF256_H
#define FF256_H

#include <limits.h>
#include <stdint.h>
#include "element.h"

typedef struct ff256 {
	element_t super;
	uint8_t val;
} ff256_t;


// ff256 methods required to meet field criteria
void ff256_add(element_t* a, element_t* b, element_t* result);
void ff256_mult(element_t* a, element_t* b, element_t* result);
void ff256_add_inv(element_t* a, element_t* result);
void ff256_mult_inv(element_t* a, element_t* result);
void ff256_add_id(element_t* result);
void ff256_mult_id(element_t* result);
void ff256_randelement(element_t* result);
void ff256_init(ff256_t* a);

// additional ff256 methods
void ff256_set(uint8_t val, ff256_t* result);

#endif
