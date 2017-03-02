#!/usr/bin/env python2.7

#this is for prime field inverse table generation

import math

#The finite field order
order = 257

#this multiply function will automatically work for
#prime orders, other fields may require a different
#multiply to represent how multiplication actually
#occurs in that field
def multiply(x,y):
	assert x>=0
	assert x<order
	assert y>=0
	assert y<order

	return ((x*y)%order)

inverses=[]
for i in range(order):
	added = False
	for j in range(order):
		if multiply(i,j) == 1:
			assert(not j in inverses)
			inverses.append(j)
			added = True
	if not added:
		print "no inv for", i
		inverses.append(None)

print inverses
