import java.util.Random;

public class Factory
{
    static private Random rnd = new Random();
    static private char[] charbag = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ".toCharArray();
    
    static public String[] createRandomStrings(int length)
    {
	if (length < 1) {
	    length = 1;
	}
	String[] array = new String[length];
	for (int ii = 0; ii < length; ++ii) {
	    int strlen = 2 + rnd.nextInt(10);
	    StringBuilder sb = new StringBuilder(strlen);
	    for (int jj = 0; jj < strlen; ++jj) {
		sb.append(charbag[rnd.nextInt(charbag.length)]);
	    }
	    array[ii] = sb.toString();
	}
	return array;
    }
    
    static public void main(String[] args) 
    {
	String[] array = createRandomStrings(10);
	for (int ii = 0; ii < array.length; ++ii) {
	    System.out.println(array[ii]);
	}
    }
}
