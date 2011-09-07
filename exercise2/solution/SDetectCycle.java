package exercise2.solution;

import exercise2.*;
import java.util.Random;

public class SDetectCycle
{
    static private Random rnd = new Random();
    
    static private StringList createList(int length, int cyclePosition)
    {
	if (length < 1) {
	    length = 1;
	}
	if (cyclePosition >= length) {
	    cyclePosition = length - 1;
	}
	StringList list = new StringList();
	StringListIterator last
	    = new StringListIterator(null); // Java requires this but it is not necessary.
	for (int ii = 0; ii < length; ++ii) {
	    list.pushFront("" + rnd.nextInt(100));
	    if (0 == ii) {
		last = list.begin();
	    }
	}
	if (0 <= cyclePosition) {
	    StringListIterator cycle = list.begin();
	    for (int ii = 0; ii < cyclePosition; ++ii) {
		cycle.next();
	    }
	    last.node.next = cycle.node;
	}
	return list;
    }
    
    static private boolean detectCycle(StringList list)
    {
	StringListIterator fast = list.begin();
	StringListIterator slow = list.begin();
	while (fast.valid()) {
	    fast.next();
	    if ( ! fast.valid()) {
		return false;
	    }
	    if (fast.node == slow.node) {
		return true;
	    }
	    slow.next();
	    fast.next();
	}
	return false;
    }
    
    static public void main(String[] args)
    {
	StringList list;
	boolean hasCycle, detectedCycle;
	for (int ii = 0; ii < 10; ++ii) {
	    if (0 == rnd.nextInt(2)) {
		hasCycle = true;
		list = createList(20 + rnd.nextInt(20), rnd.nextInt(20));
	    }
	    else {
		hasCycle = false;
		list = createList(20 + rnd.nextInt(20), -1);
	    }
	    if (hasCycle == detectCycle(list)) {
		if (hasCycle) {
		    System.out.println("correctly identified an existing cycle");
		}
		else {
		    System.out.println("correctly identified the absence of cycles");
		}
	    }
	    else {
		if (hasCycle) {
		    System.out.println("failed to detect an existing cycle");
		}
		else {
		    System.out.println("mis-detected a cycle when actually there was noe");
		}
	    }
	}
    }
}
