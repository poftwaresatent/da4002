public class PrintNumber {
    static private char[] digit = "0123456789abcdefghijklmnopqrstuvwxyz".toCharArray();
    
    static public void print(int number, int base) {
	if (number >= base) {
	    print(number / base, base);
	}
	System.out.print(digit[number % base]);
    }
    
    static public void main(String[] args) {
	int number;
	int base;
	try {
	    number = Integer.parseInt(args[0]);
	    base = Integer.parseInt(args[1]);
	    if (base < 1) {
		System.err.println("Sorry, minimum base is 2");
		System.exit(42);
	    }
	    if (base > digit.length) {
		System.err.println("Sorry, maximum base is " + digit.length);
		System.exit(42);
	    }
	    System.out.print("in base " + base + ", the number " + number + " is written ");
	    if (number < 0) {
		System.out.print("-");
		number = -number;
	    }
	    print(number, base);
	    System.out.println();
	}
	catch (Exception ee) {
	    System.err.println("Oops, an exception occurred... did you specify an integer number and base?");
	    System.exit(42);
	}
    }
}
