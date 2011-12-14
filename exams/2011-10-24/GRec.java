class GRec {
    static long gRec (long n) {
	if (n <= 2) {
	    return 0;		// (A)
	}
	if (n == 3) {
	    return 1;		// (B)
	}
	return 2 * gRec(n-3) - gRec(n-2) + gRec(n-1); // (C)
    }
    
    //////////////////////////////////////////////////
    // solution A: memoization
    
    static java.util.HashMap<Long, Long> memo = new java.util.HashMap<Long, Long>();
    
    static long gRecMemo (long n) {
	if (memo.containsKey(n)) {
	    return memo.get(n);
	}
	if (n <= 2) {
	    memo.put(n, new Long(0));
	    return 0;
	}
	if (n == 3) {
	    memo.put(n, new Long(1));
	    return 1;
	}
	long gn = 2 * gRec(n-3) - gRec(n-2) + gRec(n-1);
	memo.put(n, gn);
	return gn;
    }
    
    //////////////////////////////////////////////////
    // solution B: rewrite as iterative algorithm (bottom-up DP)
    
    static long gRecIter(long n) {
	if (n <= 2) {
	    return 0;
	}
	long g1 = 0;
	long g2 = 0;
	long g3 = 1;
	long gg = g3;
	while (n > 3) {
	    gg = 2 * g1 - g2 + g3;
	    g1 = g2;
	    g2 = g3;
	    g3 = gg;
	    n -= 1;
	}
	return gg;
    }
    
    //////////////////////////////////////////////////
    // wrong alternative B.2
    
    static long gRecIterWrong2(long n) {
	long fn1 = 0;
	long fn2 = 0;
	long fn3 = 1;
	while (n-- > 0) {
	    fn1 = fn1 + fn2;
	    fn2 = fn1 - fn2;
	    fn3 = fn1 + fn2 + fn3;
	}
	return fn1;
    }
    
}
