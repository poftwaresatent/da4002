import java.util.Random;

public class SplitSequence
{
    private static StringList list = new StringList();
    private static StringListIterator position;
    private static Random rnd = new Random();
    
    private static void process(String item)
    {
	if (null == position) {
	    list.pushFront("dummy"); // will be removed after processing
	    position = list.first();
	}
	list.insertAfter(item, position);
	if (item.equals("o")) {
	    position.next();
	}
    }
    
    public static void main(String[] args)
    {
	for (int ii = 0; ii < 80; ++ii) {
	    String item;
	    if (0 == rnd.nextInt(2)) {
		item = "o";
	    }
	    else {
		item = "*";
	    }
	    System.out.print(item);
	    process(item);
	}
	System.out.println();
	
	list.popFront();	// remove the dummy element
	for (StringListIterator ii = list.first(); ii.valid(); ii.next()) {
	    System.out.print(ii.get());
	}
	System.out.println();
    }
}
