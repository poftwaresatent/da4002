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
    
}
