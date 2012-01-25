import java.io.*;

class S2 {
    static final double log2 = Math.log(2.0);
    
    static long tt;
    
    static void f_3ms() {
	tt += 3;
    }
    
    static void f_1ms() {
	tt += 1;
    }
    
    static double lb(long N) {
	return Math.log(N) / log2;
    }
    
    static long fragment1(long N) {
	tt = 0;
	for (long ii = 0; ii < N; ii += 3) {
	    f_3ms ();
	    for (long jj = 0; jj < N; ++jj) {
		f_1ms ();
	    }
	}
	return tt;
    }
    
    static double answer1(long N) {
	return N * (3.0 + N) / 3.0;
    }
    
    static long fragment2(long N) {
	tt = 0;
	for (long ii = 0; ii < N; ++ii) {
	    f_3ms ();
	}
	for (long jj = 0; jj < N; jj += 2) {
	    f_1ms ();
	}
	return tt;
    }
    
    static double answer2(long N) {
	return 3.5 * N;
    }
    
    static void foo (long N) {
	if (N <= 1) {
	    f_3ms ();
	}
	else {
	    f_1ms ();
	    foo (N / 2);
	}
    }
    
    static long fragment3(long N) {
	tt = 0;
	for (long ii = 0; ii < N; ++ii) {
	    foo (N);
	}
	return tt;
    }
    
    static double answer3(long N) {
	return N * (3.0 + lb(N));
    }
    
    static long fragment4(long N) {
	tt = 0;
	for (long ii = 1; ii < N; ii *= 2) {
	    f_3ms ();
	    for (long jj = 0; jj < N*ii; ++jj) {
		f_1ms();
	    }
	}
	return tt;
    }
    
    static double answer4(long N) {
	final double lceil = Math.ceil(lb(N));
	// I cannot figure out where the factor of 2 comes from, but
	// this formula matches rather well... will need to swing it
	// by someone else.
	return 2.0 * (3.0 * lceil + N * Math.pow(2.0, lceil - 1));
    }
    
    public static void main(String[] args) {
	final long nMin = 100;
	final long nMax = 20000;
	final double nFactor = 1.5;
	try {
	    FileWriter logFile = new FileWriter("s2.log");
	    
	    System.out.println("N\tT1\tP1\tT2\tP2\tT2\tP2\tT3\tP3\tT4\tP4");
	    
	    for (long nn = nMin; nn < nMax; nn = (long) Math.round(nn * nFactor)) {
		String line
		    = nn + "\t"
		    + fragment1(nn) + "\t" + answer1(nn) + "\t"
		    + fragment2(nn) + "\t" + answer2(nn) + "\t"
		    + fragment3(nn) + "\t" + answer3(nn) + "\t"
		    + fragment4(nn) + "\t" + answer4(nn) + "\n";
		System.out.print(line);
		logFile.write(line);
	    }
	    
	    logFile.close();
	    
	    System.out.println();
	    System.out.println("  set key top left");
	    System.out.println("  set logscale y");
	    System.out.println();
	    System.out.println("  plot 's2.log' u 1:2 w lp t 'T1', 's2.log' u 1:3 w lp t 'P1'");
	    System.out.println("  plot 's2.log' u 1:($3-$2) w lp t 'D1'");
	    System.out.println("  plot 's2.log' u 1:4 w lp t 'T2', 's2.log' u 1:5 w lp t 'P2'");
	    System.out.println("  plot 's2.log' u 1:($5-$4) w lp t 'D2'");
	    System.out.println("  plot 's2.log' u 1:6 w lp t 'T3', 's2.log' u 1:7 w lp t 'P3'");
	    System.out.println("  plot 's2.log' u 1:($7-$6) w lp t 'D3'");
	    System.out.println("  plot 's2.log' u 1:8 w lp t 'T4', 's2.log' u 1:9 w lp t 'P4'");
	    System.out.println("  plot 's2.log' u 1:($9-$8) w lp t 'D4'");
	    
	}
	catch (IOException ee) {
	    System.err.println("Failure due to some input-output problem:\n  " + ee);
	    System.exit(42);
	}
    }
    
}
