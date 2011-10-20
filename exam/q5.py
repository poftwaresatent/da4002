#! /usr/bin/env python

def groovy (g, w, n):
    g1 = g[0]
    g2 = g[1]
    g3 = g[2]
    while n > 3:
        gg = w[0] * g1 + w[1] * g2 + w[2] * g3
        print " ", gg,
        g1 = g2
        g2 = g3
        g3 = gg
        n = n-1
    print

groovy((0, 0, 1), (2, -1, 1), 20)

def grec(n):
    if n <= 2:
        print n, " & A & 0 \\\\"
        return 0
    if n == 3:
        print n, " & B & 1 \\\\"
        return 1
    g3 = grec(n-3)
    g2 = grec(n-2)
    g1 = grec(n-1)
    gg = 2 * g3 - g2 + g1
    print n, " & C & 2*", g3, "-", g2, "+", g1, "=", gg, "\\\\"
    return gg

for ii in (4, 5, 6, 7):
    print
    print "TABLE for n =", ii
    print
    print "\\begin{tabular}{|c|c|l|}"
    print "\\hline"
    print "n & label & value \\\\"
    print "\\hline"
    grec(ii)
    print "\\hline"
    print "\\end{tabular}"
