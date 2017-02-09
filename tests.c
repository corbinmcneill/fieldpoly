#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <assert.h>
#include "debug.h"
#include "rational.h"

int main() {
    debug("testing rational elements, size: %d\n", sizeof(rat_element_t));
    rat_element_t testelement; 
    debug("created\n");
    rat_init(&testelement);
    debug("initialized\n");
    f_rand(&testelement.super);
    debug("\nand set the rational to a random number\n");
    debug("numerator: %d, denominator: %d\n", testelement.contents.num, testelement.contents.denom);

    debug("\ncreating a random polynomial\n");


    return 0;
} 

