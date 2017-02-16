#include <time.h>
#include <limits.h>
#include <stdlib.h>
#include <assert.h>
#include "primeField.h"
#include "debug.h"

#define MAX 100

field_ops_t gf257_ops;
static char initialized = 0;

int inverse[] = {0, 1, 129, 86, 193, 103, 43, 147, 225, 200, 180, 187, 150, 178, 202, 120, 241, 121, 100, 230, 90, 49, 222, 190, 75, 72, 89, 238, 101, 195, 60, 199, 249, 148, 189, 235, 50, 132, 115, 145, 45, 163, 153, 6, 111, 40, 95, 175, 166, 21, 36, 126, 173, 97, 119, 243, 179, 248, 226, 61, 30, 59, 228, 102, 253, 87, 74, 234, 223, 149, 246, 181, 25, 169, 66, 24, 186, 247, 201, 244, 151, 165, 210, 96, 205, 127, 3, 65, 184, 26, 20, 209, 176, 152, 216, 46, 83, 53, 139, 135, 18, 28, 63, 5, 215, 164, 177, 245, 188, 224, 250, 44, 218, 116, 124, 38, 113, 134, 159, 54, 15, 17, 158, 140, 114, 220, 51, 85, 255, 2, 172, 206, 37, 143, 117, 99, 240, 242, 203, 98, 123, 144, 219, 133, 141, 39, 213, 7, 33, 69, 12, 80, 93, 42, 252, 194, 229, 239, 122, 118, 204, 174, 211, 41, 105, 81, 48, 237, 231, 73, 192, 254, 130, 52, 161, 47, 92, 106, 13, 56, 10, 71, 233, 191, 88, 232, 76, 11, 108, 34, 23, 183, 170, 4, 155, 29, 198, 227, 196, 31, 9, 78, 14, 138, 160, 84, 131, 221, 236, 91, 82, 162, 217, 146, 251, 104, 94, 212, 112, 142, 125, 207, 22, 68, 109, 8, 58, 197, 62, 156, 19, 168, 185, 182, 67, 35,208, 167, 27, 157, 136, 16, 137, 55, 79, 107, 70, 77, 57, 32, 110, 214, 154, 64, 171, 128, 256};

void field_init();

void gf257_add(element_t* a, element_t* b, element_t* result) {
	gf257_element_t* x = (gf257_element_t*) a;
	gf257_element_t* y = (gf257_element_t*) b;
    gf257_element_t* output = (gf257_element_t*) result;
    output->contents = (x->contents + y->contents) % 257;
}


void gf257_mult(element_t* a, element_t* b, element_t* result) {
	gf257_element_t* x = (gf257_element_t*) a;
	gf257_element_t* y = (gf257_element_t*) b;
	gf257_element_t* output = (gf257_element_t*) result;
    output->contents = (x->contents * y->contents) % 257;
}

void gf257_add_inv(element_t* a, element_t* result) {
    int t;
	gf257_element_t* x = (gf257_element_t*) a;
	gf257_element_t* output = (gf257_element_t*) result;
    t = (257 - x->contents) % 257;
    output->contents = t;

}
void gf257_mult_inv(element_t* a, element_t* result) {
	gf257_element_t* x = (gf257_element_t*) a;
	gf257_element_t* output = (gf257_element_t*) result;
    output->contents = inverse[x->contents]; 
}
void gf257_add_id(element_t* result) {
	gf257_element_t* output = (gf257_element_t*) result;
    output->contents = 0;
}
void gf257_mult_id(element_t* result) {
	gf257_element_t* output = (gf257_element_t*) result;
    output->contents = 1;
}
void gf257_randelement(element_t* result) {
	gf257_element_t* output = (gf257_element_t*) result;
    output->contents = rand() % 257;
}
    
void gf257_init(gf257_element_t* a) {
    field_init();
    a->super.field = &gf257_ops;
    a->contents = 0;
}

void gf257_set(int a, gf257_element_t* result){
    gf257_element_t* output = (gf257_element_t*) result;
    output->contents = a;
}

void field_init() {
    if (initialized)
        return;
    srand(time(NULL));
    gf257_ops.add = &gf257_add;
    gf257_ops.mult = &gf257_mult;
    gf257_ops.addinv = &gf257_add_inv;
    gf257_ops.multinv = &gf257_mult_inv;
    gf257_ops.addid = &gf257_add_id;
    gf257_ops.multid = &gf257_mult_id;
    gf257_ops.randelement = &gf257_randelement;
    initialized = 1;
}

