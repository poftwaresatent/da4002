import java.util.ArrayList;

public class Fibonacci
{
    static ArrayList<Integer> memo = new ArrayList<Integer>();
    static {
	memo.add(new Integer(1));
	memo.add(new Integer(1));
    }
    
    static public int calcIter(int nn, boolean verbose)
    {
	int v1 = 1;
	int v2 = 1;
	int vv = 1;
	for (int ii = 2; ii <= nn; ++ii) {
	    vv = v1 + v2;
	    v2 = v1;
	    v1 = vv;
	    if (verbose) {
		System.out.println("  F(" + ii + ") = " + vv);
	    }
	}
	return vv;
    }
    
    static public int calcRecSimple(int nn, boolean verbose)
    {
	if (verbose) {
	    System.out.println("  calcRecSimple(" + nn + ")");
	}
	if (0 == nn) {
	    return 1;
	}
	if (1 == nn) {
	    return 1;
	}
	return calcRecSimple(nn - 2, verbose) + calcRecSimple(nn - 1, verbose);
    }
    
    static public int fibRec(int nn, String prefix)
    {
	System.out.println(prefix + "fibRec(" + nn + ")");
	if (2 > nn) {
	    return 1;
	}
	return fibRec(nn - 2, prefix + " ") + fibRec(nn - 1, prefix + " ");
    }
    
    static public int fibRecMemo(int nn, String prefix)
    {
	if (nn < memo.size()) {
	    System.out.println(prefix + "fibRecMemo: lookup[" + nn + "] = " + memo.get(nn));
	    return memo.get(nn);
	}
	System.out.println(prefix + "fibRecMemo: compute(" + nn + ")...");
	Integer ff = fibRecMemo(nn - 2, prefix + " ") + fibRecMemo(nn - 1, prefix + " ");
	if (nn == memo.size()) {
	    memo.add(ff);
	}
	return ff;
    }
    
    static public void main(String[] args)
    {
	int nn = 7;
	try {
	    nn = Integer.parseInt(args[0]);
	}
	catch (Exception ee) {
	    // ignore
	}
	int result = fibRec(nn, "");
	System.out.println("result: " + result);
	result = fibRecMemo(nn, "");
	System.out.println("result: " + result);
	result = calcIter(nn, true);
	System.out.println("result: " + result);
    }
}
