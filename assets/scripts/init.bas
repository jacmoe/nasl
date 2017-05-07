print "Hello Basic!";

import "assets/scripts/test.bas"

def area(a, b)
	return call mul(a, b)
enddef

def mul(a, b)
	return a * b
enddef

a = 3
b = 4
print a; b; area(a, b);