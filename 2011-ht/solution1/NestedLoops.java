class NestedLoops
{
    public static void main(String[] commandLine)
    {
	int bound = 0;
	try {
	    //////////////////////////////////////////////////
	    //
	    // There are two things that can go wrong on the following
	    // line:
	    //
	    // - The commandLine array can be empty, so accessing its
	    //   element at index 0 is undefined. In this case, Java
	    //   will raise an ArrayIndexOutOfBoundsException.
	    //
	    // - The String stored in commandLine[0] may not represent
	    //   a natural number. In that case, Integer.parseInt()
	    //   will raise a NumberFormatException.
	    //
	    // We catch each of these exceptions after the try{}
	    // block, and output more human-friendly error messages
	    // when they occur.
	    //
	    bound = Integer.parseInt(commandLine[0]);
	}
	catch (NumberFormatException ee) {
	    System.out.println("The command line argument \"" + commandLine[0] + "\" is not a natural number.");
	    System.exit(42);
	}
	catch (ArrayIndexOutOfBoundsException ee) {
	    System.out.println("Please specify a natural number as command line argument.");
	    System.exit(42);
	}
	
        for (int ii = 1; ii <= bound; ii++) {
	    if (ii > 1) {
		System.out.println(); // Print an empty line for each new ii.
	    }
            for (int jj = 1; jj <= ii; jj++) {
		System.out.println("(" + ii + ", " + jj + ")");
	    }
	}
    }
}
