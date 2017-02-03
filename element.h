typedef struct element {
    struct field_ops* field;
} element_t;

typedef struct field_ops {
    element_t* (*add)(element_t*, element_t*);
} field_ops_t;
