#include <limits.h>
#include "element.h"

typedef struct ff256  {
	uint8_t val;
} ff256_t;

typedef struct rational_element {
    struct field_ops* field;
    ff256_t contents;
} rat_element_t;


void ff256_add(element_t* a, element_t* b, element_t* result);
void ff256_mult(element_t* a, element_t* b, element_t* result);
void ff256_add_inv(element_t* a, element_t* result);
void ff256_mult_inv(element_t* a, element_t* result);
void ff256_add_id(element_t* result);
void ff256_mult_id(element_t* result);
void ff256_randelement(element_t* result);
void ff256_init(ff256_element_t* a);
