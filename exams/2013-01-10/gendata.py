#!/opt/local/bin/python

from math import *

global LN2
LN2 = log(2)

def lb(x):
    return log(x) / LN2

def fquad(n):
    return 200 + 30*n + 0.3*n*n  + 5*n*lb(n)   + 500*lb(n)

def fnln(n):
    return 5000 + n            + 50*n*lb(n) + 10*lb(n)

NSTART=10

NMAX=1e3*NSTART
n = NSTART
while n < NMAX:
    t = fquad(n)
    print n, t, t/pow(n,2), t/n/lb(n), t/n, t/lb(n)
    n *= 1.1

print
print

#NSTART=90

NMAX=1e3*NSTART
n = NSTART
while n < NMAX:
    t = fnln(n)
    print n, t, t/pow(n,2), t/n/lb(n), t/n, t/lb(n)
    n *= 1.1
