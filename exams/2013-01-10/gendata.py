#!/opt/local/bin/python

from math import *

global LN2
LN2 = log(2)

def lb(x):
    return log(x) / LN2

def fquad(n):
    return 3e6 + 2e4*n + 3*n*n    + 3e3*n*lb(n) + 5e9*lb(n)

def fnln(n):
    return 1e9 + 0.3*n            + 5*n*lb(n)   + 1e10*lb(n)

NSTART=1e2
NMAX=1e7
PFAC=1e-4

n = NSTART
while n < NMAX:
    t = fquad(n)
    print PFAC*n, t, t/pow(n,2), t/n/lb(n), t/n, t/lb(n)
    n *= 1.1

print
print

NSTART=1e7
NMAX=1e12
PFAC=1e-9

n = NSTART
while n < NMAX:
    t = fnln(n)
    print PFAC*n, t, t/pow(n,2), t/n/lb(n), t/n, t/lb(n)
    n *= 1.1
