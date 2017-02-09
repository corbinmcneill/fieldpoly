#include <limits.h>
#include "element.h"

typedef struct rational  {
    int num;
    int denom;
} rat_t;

typedef struct rational_element {
    struct field_ops* field;
    rat_t contents;
} rat_element_t;


void rat_add(element_t* a, element_t* b, element_t* result);
void rat_mult(element_t* a, element_t* b, element_t* result);
void rat_add_inv(element_t* a, element_t* result);
void rat_mult_inv(element_t* a, element_t* result);
void rat_add_id(element_t* result);
void rat_mult_id(element_t* result);
void rat_randelement(element_t* result);
void rat_init(rat_element_t* a);
