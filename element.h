typedef struct element {
    struct field_ops* field;
} element_t;

typedef struct field_ops {
    element_t (*add)(element_t*, element_t*);
    element_t (*mult)(element_t*, element_t*);
    element_t (*addinv)(element_t*);
    element_t (*multinv)(element_t*);
    element_t (*addid)();
    element_t (*multid)();
} field_ops_t;


element_t f_add(element_t* a, element_t* b);
element_t f_mult(element_t* a, element_t* b);
element_t f_add_inv(element_t* a);
element_t f_mult_inv(element_t* a);
element_t f_add_id(element_t* a);
element_t f_mult_id(element_t* a);
element_t f_sub(element_t* a, element_t* b);
element_t f_div(element_t* a, element_t* b);
