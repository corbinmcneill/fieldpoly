#include <limits.h>
#include "element.h"

typedef struct gf257_element {
    struct field_ops* field;
    int contents;
} gf257_element_t;


void gf257_add(element_t* a, element_t* b, element_t* result);
void gf257_mult(element_t* a, element_t* b, element_t* result);
void gf257_add_inv(element_t* a, element_t* result);
void gf257_mult_inv(element_t* a, element_t* result);
void gf257_add_id(element_t* result);
void gf257_mult_id(element_t* result);
void gf257_randelement(element_t* result);
void gf257_init(gf257_element_t* a);
