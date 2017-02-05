element_t f_add(element_t* a, element_t* b) {
   return a->field->add(a,b); 
}
element_t f_mult(element_t* a, element_t* b) {
   return a->field->mult(a,b); 
}
element_t f_add_inv(element_t* a) {
   return a->field->addinv(a); 
}
element_t f_mult_inv(element_t* a) {
   return a->field->multinv(a); 
}
element_t f_add_id(element_t* a) {
   return a->field->addid(); 
}
element_t f_mult_id(element_t* a) {
   return a->field->multid(); 
}

element_t f_sub(element_t* a, element_t* b) {
   return element_add(a,get_add_inv(b)); 
}
element_t f_div(element_t* a, element_t* b) {
   return element_mult(a,get_mult_inv(b)); 
}
