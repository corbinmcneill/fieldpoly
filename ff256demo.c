#include <stdio.h>
#include "ff256.h"

void ff256_to_string(ff256_t* a, char* output) {
	for (int i=0; i<8; i++) {
		output[7-i] = ((a->val >> i) & 1) + '0';
	}
	output[8] = 0;
}

int main() {
	char binary_buf[9];
	
	ff256_t a,b,c;

	ff256_init(&a);
	ff256_init(&b);
	ff256_init(&c);

	//ff256_randelement((element_t*) &a);
	//ff256_randelement((element_t*) &b);
	a.val = 0b00001001;
	b.val = 0b10011011;
	
	ff256_to_string(&a, binary_buf);
	printf("random a: %s\n", binary_buf);

	ff256_add_inv((element_t*)&a, (element_t*)&c);
	ff256_to_string(&c, binary_buf);
	printf("additive inverse a: %s\n", binary_buf);

	ff256_mult_inv((element_t*)&a, (element_t*)&c);
	ff256_to_string(&c, binary_buf);
	printf("multiplicative inverse a: %s\n\n", binary_buf);

	ff256_to_string(&b, binary_buf);
	printf("random b: %s\n", binary_buf);

	ff256_add_inv((element_t*)&b, (element_t*)&c);
	ff256_to_string(&c, binary_buf);
	printf("additive inverse b: %s\n", binary_buf);

	ff256_mult_inv((element_t*)&b, (element_t*)&c);
	ff256_to_string(&c, binary_buf);
	printf("multiplicative inverse b: %s\n\n", binary_buf);

	ff256_add((element_t*)&a, (element_t*)&b, (element_t*)&c);
	ff256_to_string(&c, binary_buf);
	printf("sum: %s\n", binary_buf);

	ff256_mult((element_t*)&a, (element_t*)&b, (element_t*)&c);
	ff256_to_string(&c, binary_buf);
	printf("product: %s\n", binary_buf);
}	

