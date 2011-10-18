class First
{
    
    public static void main(String [] commandline)
    {
	// Instead of blindly trying commandline[0] and getting an
	// exception when there are no arguments, it is easier to just
	// check that there actually is at least one element in the
	// array.
	if (commandline.length < 1) {
	    System.out.println("Please specify a name on the command line.");
	    System.exit(123);
	}
	
        hello(commandline[0]);
        sumBetween(1, 3);
        additionTable();
        multiplicationTable();
        System.out.println("max(1, 2, 3) = " + max(1, 2, 3));
        System.out.println("max(4, 1, 2, 3) = " + max(4, 1, 2, 3));
        intPairs(1000);
        format(120, 30);
        fibs(20);
        fibsSmallerThan(10000);
    }
    
    private static final void hello(String name)
    {
	System.out.println("Hello to you " + name + "!");
	System.out.println();
    }
    
    private static final void sumBetween(int lower, int upper)
    {
	// Note that this formula is only correct when 1 <= lower <= upper
	
	int result = (upper * (upper + 1) - (lower - 1) * lower) / 2;
	System.out.println("sumBetween(" + lower + ", " + upper + ") = " + result);
	System.out.println();
    }

    private static final void additionTable()
    {
	System.out.println("           Addition Table");
	System.out.println("   |  0 |  1 |  2 |  3 |  4 |  5 |  6 |  7 |  8 |  9 |");
	System.out.println("------------------------------------------------------");
	
	for (int ii = 0; ii < 10; ++ii) {
	    System.out.print(ii + "  |");
	    for (int jj = 0; jj < 10; ++jj) {
		
		// The printf method allows to specify nicer
		// formatting, but it requires a somewhat cryptic
		// format specification as first argument. See
		// http://download.oracle.com/javase/1.5.0/docs/api/java/io/PrintStream.html
		// for details (scroll down to the documentation for
		// the printf method).
	    
		System.out.printf(" %2d  ", ii + jj);
	    }
	    System.out.println();
	}
	System.out.println();
    }
    
    private static final void multiplicationTable()
    {
	System.out.println("           Multiplication Table");
	System.out.println("   |  0 |  1 |  2 |  3 |  4 |  5 |  6 |  7 |  8 |  9 |");
	System.out.println("------------------------------------------------------");
	
	for (int ii = 0; ii < 10; ++ii) {
	    System.out.print(ii + "  |");
	    for (int jj = 0; jj < 10; ++jj) {
		System.out.printf(" %2d  ", ii * jj);
	    }
	    System.out.println();
	}
	System.out.println();
    }
    
    private static final int max(int xx, int yy, int zz)
    {
	if (xx > yy) {
	    return xx > zz ? xx : zz;
	}
	return yy > zz ? yy : zz;
    }
    
    private static final int max(int xx, int yy, int zz, int uu)
    {
	int m3 = max(yy, zz, uu);
	return xx > m3 ? xx : m3;
    }
    
    private static final void intPairs(int limit)
    {
        // all pairs of positive integers (a, b) such that:
        //     a < b < limit 
        //    (a*a + b*b + 1) / (a*b) is an integer.
	
	for (int aa = 1; aa < limit; ++aa) {
	    for (int bb = aa + 1; bb < limit; ++bb) {
		if (0 == (aa*aa + bb*bb + 1) % (aa*bb)) {
		    System.out.println(aa + " " + bb);
		}
	    }
	}
	System.out.println();
    }
    
    private static final void format(int howMany, int lineLength)
    {
	int remain = lineLength;
	for (int ii = 1; ii <= howMany; ++ii) {
	    
	    //////////////////////////////////////////////////
	    //
	    // We need 2+log10(ii) characters to print ii:
	    // - first the opening brace
	    // - then the number, which requires log10(ii) digits
	    // - then the closing brace
	    //
	    // Notes:
	    // - We need to always round up the log10() result, so use
	    //   the ceil() function.
	    // - log10(10) is 1, but it requires 2 digits, so trick it
	    //   by adding 0.1
	    //
	    
	    int width = 2 + (int) Math.ceil(Math.log10(ii + 0.1));
	    if (width <= remain) {
		remain -= width; // we still fit on the current line
	    }
	    else {
		System.out.println(); // we have to start a new line
		remain = lineLength;
	    }
	    
	    System.out.print("[" + ii + "]");
	}
	System.out.println();
	System.out.println();
    }
    
    
    private static final void fibs(int position)
    {
	if (position < 2) {
	    System.out.println("1");
	    return;
	}
	
	int f1 = 1;
	int f2 = 1;
	System.out.print("1 1");
	for (int ii = 2; ii <= position; ++ii) {
	    int ff = f1 + f2;
	    System.out.print(" " + ff);
	    f2 = f1;
	    f1 = ff;
	}
	System.out.println();
	System.out.println();
    }
    
    private static final void fibsSmallerThan(int ceiling)
    {
	if (ceiling <= 1) {
	    System.out.println();
	    return;
	}
	
	if (ceiling == 2) {
	    System.out.println("1 1");
	    System.out.println();
	    return;
	}
	
	int f1 = 1;
	int f2 = 1;
	int ff = 1;
	System.out.print("1");
	while (ff < ceiling) {
	    System.out.print(" " + ff);
	    ff = f1 + f2;
	    f2 = f1;
	    f1 = ff;
	}
	System.out.println();
	System.out.println();
    }
}


