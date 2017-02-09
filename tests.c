#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <assert.h>
#include "debug.h"
#include "rational.h"

int main() {
    rat_t test;
    debug("testing elements\n");
    rat_element_t testelement;
    debug("created, ");
    rat_init(&testelement);
    debug("initialized, ");
    f_rand(&testelement);
    debug(", and set the rational to a random number\n");
    debug("numerator: %d, denominator: %d\n", testelement.contents.num, testelement.contents.denom);
    return 0;
} 

