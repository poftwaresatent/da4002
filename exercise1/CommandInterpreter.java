class CommandInterpreter
{
    private enum Command { SORT, SEARCH, RANDOM, QUIT }
    
    private static int    size = 100;
    private static int[]  aa = new int[size];
    private static int    xx = 0;
    
    private static java.util.Random rnd = new java.util.Random();
    private static java.io.BufferedReader in = new java.io.BufferedReader(new java.io.InputStreamReader(System.in));
    
    public static void execute(Command com)
	throws java.io.IOException
    {
        System.out.println("About to " + com + " ...");
	
        switch (com) {
	    
        case SORT:
            java.util.Arrays.sort(aa);
            System.out.println(java.util.Arrays.toString(aa));
            break;
	    
        case SEARCH:
            System.out.println("sought? ");
            xx = new Integer(in.readLine());
            int pos = java.util.Arrays.binarySearch(aa, xx);
            if (pos < 0) {
                System.out.println(xx + " not found in " + java.util.Arrays.toString(aa));
	    }
            else {
                System.out.println(xx + " found at position " + pos + " in " + java.util.Arrays.toString(aa));
	    }
            break;
	    
        case RANDOM:
            System.out.println("size? ");
            size = new Integer(in.readLine());
            aa = new int[size];
            for (int ii = 0; ii < size; ++ii) {
                aa[ii] = rnd.nextInt(100);
	    }
            System.out.println(java.util.Arrays.toString(aa));
            break;
	    
        case QUIT:
            System.exit(0);

        default:
	    ;
        }
	
        System.out.println("Done with " + com + ".");
        System.out.println();
    }
    
    public static void main(String[] cmdLn)
	throws java.io.IOException
    {
        System.out.println();
        System.out.println("Welcome to the array command interpreter!\n");
        System.out.println("the following operations are available:");
        for (Command cc : Command.values()) {
            System.out.println(cc);
        }
        System.out.println();
	
        String line = null;
        while (true) {
            try {
                line = in.readLine();
                execute(Command.valueOf(line.toUpperCase()));
            }
	    catch (IllegalArgumentException ee) {
		System.out.println("Sorry! no Command " + line);
	    }
        }
    }
}
