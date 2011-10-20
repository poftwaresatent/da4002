#! /usr/bin/env python

import math

def lg2(x):
    return math.log(x) / math.log(2)

def vpm(n, t1):
    return t1 * ((n * (n-1) - 2) / 4.0 + 1)

def cto(n, t2, t3):
    return t2 * n / 5.0 + t3 * n * lg2(n/5.0)

parms = [ (0.4, 5.0, 0.5) , (0.2, 5.0, 0.5) ]
ns = ( 10, 20, 40, 80, 160 )
for pp in parms:
    print
    print "t_i\t", pp
    print "N",
    for n in ns:
        print "\t", n,
    print
    print "VPM",
    for n in ns:
        print "\t", vpm(n, pp[0]),
    print
    print "CTO",
    for n in ns:
        print "\t", cto(n, pp[1], pp[2]),
    print
