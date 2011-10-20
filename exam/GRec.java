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
}
