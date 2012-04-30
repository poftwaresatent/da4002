class First
{
    
    public static void main(String [] commandline)
    {
        // to test your methods:
        
        hello(commandline[0]);
        sumBetween(1, 3);
        additionTable();
        multiplicationTable();
        System.out.println("max(1, 2, 3) = " + max(1, 2, 3));
        System.out.println("max(4, 1, 2, 3) = " + max(4, 1, 2, 3));
        intPairs(1000);
        format(100, 30);
        fibs(20);
        fibsSmallerThan(10000);
    }
    
    private static final void hello(String name)
    {
        // A method that writes to the terminal a line saying
        //     Hello to you
        //     followed by the argument name
        //     followed by an exclamation mark.
        // It should then write an empty line.
    }
    
    private static final void sumBetween(int lower, int upper)
    {
        // A method that writes to the terminal the sum of all integer
        // numbers between lower and upper.  It should also write a
        // message explaining what the result stands for, something
        // like "sumBetween(1,3) = 6" whenever lower is 1 and upper is
        // 3.  It should then write an empty line.
    }

    private static final void additionTable()
    {
        // Print the addition table for single digit numbers, followed
        // by an empty line.
    }
    
    private static final void multiplicationTable()
    {
        // Print the multiplication table for single digit numbers,
        // followed by an empty line.
    }
    
    private static final int max(int xx, int yy, int zz)
    {
        // Return the maximum of three integers.
        return 0;
    }
    
    private static final int max(int xx, int yy, int zz, int uu)
    {
        // Return the maximum of four integers.
        return 0;
    }
    
    private static final void intPairs(int limit)
    {
        // Write to the terminal all pairs of positive integers (a, b)
        // satisfying the following two conditions:
	//
        //   a < b < limit 
        //   (a*a + b*b + 1) / (a*b) is an integer.
	//
        // After listing all such pairs, it should write an empty
        // line.
    }
    
    private static final void format(int howMany, int lineLength)
    {
        // Write to the terminal the positive integers up to howMany
        // in the format [1][2][3][4] etc.  It should not output more
        // than lineLength characters on any one line: do not start a
        // "[" unless the corresponding "]" will fit on the sam eline.
        // It should write an empty line at the end.
    }
    
    
    private static final void fibs(int position)
    {
        // The series of Fibonacci numbers is:  
        // 1 1 2 3 5 8 13 21 34 55 89 144 233 377 610 987 1597 ...
        // - the first two numbers are 1
        // - all subsequent numbers are the sum of their two predecessors.
	//
        // This method should write to the terminal the series of
        // Fibonacci numbers up to the given position, followed by an
        // empty line.
    }
    
    private static final void fibsSmallerThan(int ceiling)
    {
        // A method to write to the terminal all Fibonacci numbers
        // smaller that the given ceiling, followed by an empty line.
    }

}


