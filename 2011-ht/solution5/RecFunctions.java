class RecFunctions{
    // The palindrome detector needs to be able to quickly look up
    // whitespace characters. So, we store them in a hash table.
    private static java.util.HashSet<Character> whitespace = new java.util.HashSet<Character>();
    static {
	String ws = " ,.;:-_'\"\t\n?!";
	for (int ii = 0; ii < ws.length(); ++ii) {
	    whitespace.add(ws.charAt(ii));
	}
    }
    
    
    public static long sum(int n)
    {
	if (n <= 0) {
	    return 0;
	}
	return n + sum(n-1);
    }
    
    
    public static long sum(int a, int b)
    {
	if (b < a) {
	    return sum(b, a);
	}
	if (a == b) {
	    return a;
	}
	return b + sum(a, b-1);
    }
    
    
    public static long sumOdds(int n)
    {
	if (n <= 1) {
	    return 1;
	}
	return 2*n-1 + sumOdds(n-1);
    }
    
    
    public static double power(double base, int exponent)
    {
	if (exponent <= 0) {
	    return 1;
	}
	return base * power(base, exponent-1);
    }
    
    
    private static boolean palindromeRec(char[] str, int first, int last)
    {
	if (first >= last) {
	    return true;
	}
	if (str[first] != str[last]) {
	    return false;
	}
	for (int ii = first + 1; first < str.length; ++ii) {
	    if ( ! whitespace.contains(str[ii])) {
		first = ii;
		break;
	    }
	    if (first >= last) {
		return true;
	    }
	}
	for (int ii = last - 1; last >= 0; --ii) {
	    if ( ! whitespace.contains(str[ii])) {
		last = ii;
		break;
	    }
	    if (first >= last) {
		return true;
	    }
	}
	return palindromeRec(str, first, last);
    }
    
    
    public static boolean palindrome(String str)
    {
	return palindromeRec(str.toCharArray(), 0, str.length()-1);
    }
    
    
    public static void main(String[] cmdLn)
    {
        System.out.println(sum(10));
        System.out.println(sum(100, 110));
        System.out.println(sumOdds(4));
        System.out.println(power(2, 10));
	
	String[] examplePalindromes = {
	    "ANA",
	    "ANANA",
	    "DABALE ARROZ A LA ZORRA EL ABAD",
	    "I don't think this is a palidrome, do you?",
	    "A SANTA LIVED AS A DEVIL AT NASA"
	};
	for (int ii = 0; ii < examplePalindromes.length; ++ii) {
	    if (palindrome(examplePalindromes[ii])) {
		System.out.println("Yes, this is a palindrome: " + examplePalindromes[ii]);
	    }
	    else {
		System.out.println("No, this is not a palindrome: " + examplePalindromes[ii]);
	    }
	}
    }
}
