class MyStringComparator
    implements java.util.Comparator<String> {
    public int compare(String a, String b) {
	return a.length() - b.length();
    }
}

class Max
{
    public static final <E extends Comparable<E>> E  max(E a, E b)
    {
        if (a.compareTo(b) <= 0) {
            return b;
	}
        else {
            return a;
	}
    }
    
    public static final <E> E max(E a, E b, java.util.Comparator<E> c)
    {
        if (c.compare(a,b)<=0) {
            return b;
	}
        else {
            return a;
	}
    }

    public static void main (String[] args)
    {
	System.out.println("What is bigger, 17 or 42?");
	System.out.println("  with normal int comparison: " + max(17, 42));
	
	System.out.println("What is bigger, \"aaa\" or \"bb\"?");
	System.out.println("  with normal String comparison: " + max("aaa", "bb"));
	
	MyStringComparator mc = new MyStringComparator();
	System.out.println("  with custom comparator:        " + max("aaa", "bb", mc));
    }
    
}
