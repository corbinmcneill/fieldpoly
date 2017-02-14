#include <time.h>
#include <limits.h>
#include <stdlib.h>
#include <assert.h>
#include "rational.h"
#include "debug.h"

//precalculated multiplicative inverse table
//for efficient lookup
uint8_t *inverses = 
	{0, 1, 141, 246, 203, 82, 123, 209, 
	232, 79, 41, 192, 176, 225, 229, 199,
	116, 180, 170, 75, 153, 43, 96, 95, 
	88, 63, 253, 204, 255, 64, 238, 178, 
	58, 110, 90, 241, 85, 77, 168, 201, 
	193, 10, 152, 21, 48, 68, 162, 194, 
	44, 69, 146, 108, 243, 57, 102, 66, 
	242, 53, 32, 111, 119, 187, 89, 25, 
	29, 254, 55, 103, 45, 49, 245, 105, 
	167, 100, 171, 19, 84, 37, 233, 9, 
	237, 92, 5, 202, 76, 36, 135, 191, 
	24, 62, 34, 240, 81, 236, 97, 23, 
	22, 94, 175, 211, 73, 166, 54, 67, 
	244, 71, 145, 223, 51, 147, 33, 59, 
	121, 183, 151, 133, 16, 181, 186, 60, 
	182, 112, 208, 6, 161, 250, 129, 130, 
	131, 126, 127, 128, 150, 115, 190, 86, 
	155, 158, 149, 217, 247, 2, 185, 164, 
	222, 106, 50, 109, 216, 138, 132, 114, 
	42, 20, 159, 136, 249, 220, 137, 154, 
	251, 124, 46, 195, 143, 184, 101, 72, 
	38, 200, 18, 74, 206, 231, 210, 98, 
	12, 224, 31, 239, 17, 117, 120, 113, 
	165, 142, 118, 61, 189, 188, 134, 87, 
	11, 40, 47, 163, 218, 212, 228, 15, 
	169, 39, 83, 4, 27, 252, 172, 230, 
	122, 7, 174, 99, 197, 219, 226, 234, 
	148, 139, 196, 213, 157, 248, 144, 107, 
	177, 13, 214, 235, 198, 14, 207, 173, 
	8, 78, 215, 227, 93, 80, 30, 179, 
	91, 35, 56, 52, 104, 70, 3, 140, 
	221, 156, 125, 160, 205, 26, 65, 28};

int ilog2(uint16_t x) {
  uint8_t result;
  uint8_t num;

  num = (!!(x>>8)) << 3;
  result = result + num;
  x = x>>num;

  num = (!!(x>>4)) << 2;
  result = result + num;
  x = x>>num;

  num = (!!(x>>2)) << 1;
  result = result + num;
  x = x>>num;

  num = !!(x>>1);
  return result + num;
}

void ff256_add(element_t* a, element_t* b, element_t* result) {
	ff256_element_t* x = (ff256_element_t*) a;
	ff256_element_t* y = (ff256_element_t*) b;
	ff256_element_t* output = (ff256_element_t*) result;

	output->contents.val = (x->contents.val) ^ (y->contents.val);
}

void ff256_mult(element_t* a, element_t* b, element_t* result) {
	ff256_element_t* x = (ff256_element_t*) a;
	ff256_element_t* y = (ff256_element_t*) b;
	ff256_element_t* output = (ff256_element_t*) result;

	uint16_t X = (uint16_t) x->contents.val;
	uint16_t Y = (uint16_t) y->contents.val;

	uint16_t upperMask = 0xFF00;
	uint16_t intermediate = 0;
	uint16_t splitFieldPoly = 0x11b;

	while (Y != 0) {
		if (Y & 1) {
			intermediate ^= X;
			while (intermediate & upperMask) {
				intermediate ^= (splitFieldPoly<<(ilog2(intermediate)-8));
			}
		}
		Y>>=1;
		X<<=1;
	}
}

void ff256_add_inv(element_t* a, element_t* result) {
	ff256_element_t* x = (ff256_element_t*) a;
	ff256_element_t* output = (ff256_element_t*) result;

	output->contents.val = ~(x->contents.val);
}

void ff256_mult_inv(element_t* a, element_t* result) {
	ff256_element_t* x = (ff256_element_t*) a;
	ff256_element_t* output = (ff256_element_t*) result;

	output->contents.val=inverses[a->contents.val];
}

void ff256_add_id(element_t* result) {
	ff256_element_t* output = (ff256_element_t*) result;
	output->contents.val = 0;
}

void ff256_mult_id(element_t* result) {
	ff256_element_t* output = (ff256_element_t*) result;

	output->contents.val = 1;
}

void ff256_randelement(element_t* result) {
	ff256_element_t* output = (ff256_element_t*) result;

	srand(time(NULL));
	output->contents.num = (uint8_t) rand();
}
 
void ff256_init(ff256_element_t* a) {
	a->field = &ff256_ops;
	a->contents.val = 0;
}
