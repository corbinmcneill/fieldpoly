#include <limits.h>
struct long_element {
    element_t super;
    unsigned long long order = ULONG_MAX +1;
    unsigned long contents;

