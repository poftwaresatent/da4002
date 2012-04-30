class NestedLoops
{
    // The commandLine array contains the arguments passed after the
    // class name when launching the java virtual machine. Here is a
    // simple way of printing out all arguments:
    //
    //   for (int ii = 0; ii < commandLine.length; ++ii) {
    //       System.out.println(commandLine[ii]);
    //   }

    public static void main(String[] commandLine)
    {
	
	// Notice that using single-letter variable names can make it
	// harder to find and replace text. A simple trick is to use
	// double letters, such as ii instead of i.
	
        for (int ii = 1; ii <= 5; ii++) {
            for (int jj = 1; jj <= 5; jj++) {
		System.out.println("(" + ii + ", " + jj + ")");
	    }
	}
    }
}
