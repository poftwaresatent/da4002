import java.util.PriorityQueue;
import java.util.Comparator;
import java.util.Random;

class SomeData
{
    public double foo;
    public String bar;
    
    public SomeData(double _foo, String _bar)
    {
	foo = _foo;
	bar = _bar;
    }
    
    public String toString()
    {
	return bar + " / " + foo;
    }
}


class ExampleOne
    implements Comparable<ExampleOne>
{
    int value;
    SomeData data;
    
    public ExampleOne(int _value, SomeData _data)
    {
	value = _value;
	data = _data;
    }
    
    public int compareTo(ExampleOne other)
    {
	if (value < other.value) {
	    return -1;
	}
	if (value > other.value) {
	    return 1;
	}
	return 0;
    }
    
    public String toString()
    {
	return data + "\t(value " + value + ")";
    }
}


class ExampleTwo
    implements Comparator<SomeData>
{
    public int compare(SomeData left, SomeData right)
    {
	if (left.foo < right.foo) {
	    return -1;
	}
	if (left.foo > right.foo) {
	    return 1;
	}
	return 0;
    }
}


public class PriorityQueueExample
{
    static private Random rnd = new Random();
    static private final String charbag = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    
    public static void main(String[] args)
    {
	SomeData[] data = new SomeData[20];
	for (int ii = 0; ii < data.length; ++ii) {
	    StringBuilder sb = new StringBuilder();
	    for (int jj = 0; jj < 3; ++jj) {
		sb.append(charbag.charAt(rnd.nextInt(charbag.length())));
	    }
	    data[ii] = new SomeData(rnd.nextDouble() * 200.0 - 100.0, sb.toString());
	}
	
	System.out.println("Example 1: using a Comparable with an extra 'value' field");
	PriorityQueue<ExampleOne> pqOne = new PriorityQueue<ExampleOne>();
	for (int ii = 0; ii < data.length; ++ii) {
	    int value = rnd.nextInt(5);
	    if (pqOne.add(new ExampleOne(value, data[ii]))) {
		System.out.println("  inserted " + data[ii] + " (value " + value
				   + ")\ttop: " + pqOne.peek());
	    }
	    else {
		System.out.println("  FAILED to insert " + data[ii] + " (value " + value + ")");
	    }
	}
	System.out.println("Emptying the queue:");
	while (true) {
	    ExampleOne ee = pqOne.poll();
	    if (null == ee) {
		break;
	    }
	    System.out.println("  " + ee);
	}
    }
}
