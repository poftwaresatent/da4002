class RecFunctions{

    /*
      This class includes a number of functions that should be
      implemented recursively. It has the purpose of providing you
      with material for training your understanding of recursion. In
      many cases the best solution might not be recursive, but here
      you are asked to give a recursive method!

      Think of the rules from the book:
      
           Always at least one base case!
           The recursive calls should make progress towards the base case!
           Trust that the recursive call will do what is expected!
     */

    

    public static long sum(int n){
        // sum all integer numbers from 0 to n.
        // sum(0) = 0
        // sum(n) = n + sum(n-1) for n > 0.
        // What happens when you call your function with a negative argument?
        // What do you think should happen?
	return 0;
    }


    public static long sum(int a, int b){
        // sum all integer numbers from a to b inclusive. b
        // sum(a,a) = a
        // sum(a,b) = b + sum(a, b-1) for b > a.
        // What happens when you call your function with b < a?
        // What do you think should happen?
	return 0;
    }

    
    public static long sumOdds(int n){
        // sum the first n positive odd numbers 1, 3, 5, 7.  Try this
        // function for some inputs. What can you say about the
        // results? Could you compute them in a faster way?
        // Do you think this is possible for other sums?
	return 0;
    }

    public static double power(double base, int exponent){
        // raise base to the exponent.
        // power(base,0) = 1
        // power(base,n) = base * power(base, n-1) for n >0.
            // What happens when you call your function with a negative argument?
        // What do you think should happen?
	return 0;
    }

    public static boolean palindrome(String str){
        // str is a palindrome if it can be read alike forwards and
        // backwards.  Examples of palindromes are ANA, ANANA Can you
        // modify your program so that it ignores white spaces, so
        // that even sentences can be considered. Here comes a longer
        // spanish palindrome: DABALE ARROZ A LA ZORRA EL ABAD. And
        // one in english: A SANTA LIVED AS A DEVIL AT NASA.  Does
        // your function consider it a palindrome?
	return false;
    }
    
    public static void main(String[] cmdLn){
        System.out.println(sum(10));
        System.out.println(sum(100,110));
        System.out.println(sumOdds(4));
        System.out.println(power(2,10));
        System.out.println(palindrome("anana"));
    
    }

}
