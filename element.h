typedef struct element {
    struct field_ops* field;
} element_t;

typedef struct field_ops {
    void (*add)(element_t*, element_t*,element_t*);
    void (*mult)(element_t*, element_t*,element_t*);
    void (*addinv)(element_t*,element_t*);
    void (*multinv)(element_t*,element_t*);
    void (*addid)(element_t*);
    void (*multid)(element_t*);
    void (*randelement)(element_t*);
} field_ops_t;


void  f_add(element_t* a, element_t* b);
void  f_mult(element_t* a, element_t* b);
void  f_add_inv(element_t* a);
void  f_mult_inv(element_t* a);
void f_add_id(element_t* a);
void f_mult_id(element_t* a);
void f_rand(element_t* a);


void f_sub(element_t* a, element_t* b);
void f_div(element_t* a, element_t* b);


void  f_addr(element_t* a, element_t* b, element_t* result);
void  f_multr(element_t* a, element_t* b, element_t* result);
void  f_add_invr(element_t* a, element_t* result);
void  f_mult_invr(element_t* a, element_t* result);
void f_add_idr(element_t* a, element_t* result);
void f_mult_idr(element_t* a, element_t* result);
void f_randr(element_t* a, element_t* result);


void f_subr(element_t* a, element_t* b, element_t* result);
void f_divr(element_t* a, element_t* b, element_t* result);
