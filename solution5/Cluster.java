import java.util.Random;

class Range {
    public int begin;
    public int end;

    public Range(int _begin, int _end) {
	begin = _begin;
	end = _end;
    }
    
    public void print() {
	for (int ii = 0; ii < begin; ++ii) {
	    System.out.print(' ');
	}
	if (begin == end-1) {
	    System.out.print('|');
	}
	else {
	    System.out.print('[');
	    for (int ii = begin+1; ii < end-1; ++ii) {
		System.out.print('_');
	    }
	    System.out.print(']');
	}
	System.out.println();
    }
}

public class Cluster
{
    private static Random rnd = new Random();
    private static final char FILLED = 'o';
    private static final char EMPTY = '-';
    
    public static String createData(int size, double pfill)
    {
	StringBuilder sb = new StringBuilder();
	for (int ii = 0; ii < size; ++ii) {
	    if (rnd.nextDouble() < pfill) {
		sb.append(FILLED);
	    }
	    else {
		sb.append(EMPTY);
	    }
	}
	return sb.toString();
    }
    
    public static void print(String data, Range highlight)
    {
	if (null == highlight) {
	    System.out.print(data);
	}
	else {
	    for (int ii = 0; ii < data.length(); ++ii) {
		if (ii >= highlight.begin && ii < highlight.end) {
		    if (FILLED == data.charAt(ii)) {
			System.out.print('O');
		    }
		    else {
			System.out.print('=');
		    }
		}
		else {
		    System.out.print(data.charAt(ii));
		}
	    }
	}
    }
    
    public static Range cluster(String data, Range region)
    {
	int len = region.end - region.begin;
	if (0 >= len) {
	    print(data, region);
	    System.out.println("  zero-length");
	    return null;
	}
	else if (1 == len) {
	    print(data, region);
	    if (FILLED == data.charAt(region.begin)) {
		System.out.println("  full");
		region.print();
		return region;
	    }
	    System.out.println("  empty");
	    return null;
	}
	
	int middle = (region.begin + region.end) / 2;
	Range left = cluster(data, new Range(region.begin, middle));
	Range right = cluster(data, new Range(middle, region.end));
	
	print(data, region);
	if (null == left) {
	    System.out.print("  l0");
	    if (null == right) {
		System.out.println(" r0");
	    }
	    else {
		System.out.println(" R");
		right.print();
	    }
	    return right;
	}
	if (null == right) {
	    System.out.println("  L r0");
	    left.print();
	    return left;
	}
	if (left.end == right.begin) {
	    System.out.println("  FUSE");
	    Range cluster = new Range(left.begin, right.end);
	    left.print();
	    right.print();
	    cluster.print();
	    return cluster;
	}
	if (right.end - right.begin > left.end - left.begin) {
	    System.out.println("  right");
	    right.print();
	    return right;
	}
	System.out.println("  left");
	left.print();
	return left;
    }
    
    public static void main(String[] args)
    {
	int size = 10;
	double pfill = 0.3;
	try {
	    size = Integer.parseInt(args[0]);
	    pfill = Double.parseDouble(args[1]);
	}
	catch (Exception ee) {
	    // ignore
	}
	
	////	String data = createData(size, pfill);
	String data = ".oooooo.ooo.oo.oooo.ooo.oooooo.oo.oooooooooooo.ooo..oo.oooooooooooooooooooo.oo.o.ooooo.ooooo.o.ooooo";
	Range info = cluster(data, new Range(0, size));
	print(data, info);
	System.out.println();
    }
}
