#include <limits.h>
#include "element.h"

typedef struct rational  {
    int num;
    int denom;
} rat_t;

typedef struct rational_element {
    element_t super;
    rat_t contents;
} rat_element_t;

void rat_mult(rat_element_t* a, rat_element_t* b, rat_element_t* result);
void rat_add_inv(rat_element_t* a, rat_element_t* result);
void rat_mult_inv(rat_element_t* a, rat_element_t* result);
void rat_add_id(rat_element_t* result);
void rat_mult_id(rat_element_t* result);
void rat_randelement(rat_element_t* result);
