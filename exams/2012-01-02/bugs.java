class QueueNode {
    String item;
    QueueNode next;
    
    QueueNode (String _item) {
	item = _item;
    }
}

class Queue_nobug {
    QueueNode head, tail;
    
    void enqueue (String item) {
	QueueNode node = new QueueNode(item);
	if (null == head) {
	    head = node;
	    tail = node;
	}
	else {
	    tail.next = node;
	    tail = node;
	}
    }
    
    String dequeue () {
	if (null == head) {
	    return null;
	}
	String item = head.item;
	head = head.next;
	return item;
    }
}

class Queue_bug {
    QueueNode head, tail;
    
    void enqueue (String item) {
	QueueNode node = new QueueNode(item);
	if (null == head) {
	    head = node;
	    tail = node;
	}
	else {
	    node.next = tail;
	    tail = node;
	}
    }
    
    String dequeue () {
	if (null == head) {
	    return null;
	}
	String item = head.item;
	head = head.next;
	return item;
    }
}

class bugs {

    static int fibonacci_nobug (int nn) {
	if (nn <= 2) {
	    return 1;
	}
	int f1 = 1;
	int f2 = 1;
	int ff = 0;
	for (int ii = 2; ii < nn; ++ii) {
	    ff = f1 + f2;
	    f1 = f2;
	    f2 = ff;
	}
	return ff;
    }

    static int fibonacci_bug (int nn) {
	if (nn <= 2) {
	    return 1;
	}
	int f1 = 1;
	int f2 = 1;
	int ff = 0;
	for (int ii = 2; ii < nn; ++ii) {
	    ff = f1 + f2;
	    f2 = ff;
	    f1 = f2;
	}
	return ff;
    }
    
    static int binsearch_nobug (int [] data, int item) {
	int low = 0;
	int high = data.length - 1;
	while (low <= high) {
	    int mid = (low + high) / 2;
	    if (data[mid] < item) {
		low = mid + 1;
	    }
	    else if (data[mid] > item) {
		high = mid - 1;
	    }
	    else {
		return mid;
	    }
	}
	return -1;
    }
    
    static int binsearch_bug (int [] data, int item) {
	int low = 0;
	int high = data.length - 1;
	while (low <= high) {
	    int mid = (low + high) / 2;
	    if (data[mid] < item) {
		high = mid - 1;
	    }
	    else if (data[mid] > item) {
		low = mid + 1;
	    }
	    else {
		return mid;
	    }
	}
	return -1;
    }
    
    public static void main (String [] args) {
	System.out.println("Fibonacci bug:");
	for (int ii = 1; ii < 10; ++ii) {
	    System.out.println("  " + ii + ": " + fibonacci_bug (ii) + " should be " + fibonacci_nobug(ii));
	}
	
	System.out.println("Binary search bug:");
	int [] data = { 1, 23, 25, 66, 102 };
	for (int ii = 24; ii <= 26; ++ii) {
	    System.out.println("  " + ii + ": " + binsearch_bug(data, ii) + " should be " + binsearch_nobug(data, ii));
	}
	for (int ii = 65; ii <= 67; ++ii) {
	    System.out.println("  " + ii + ": " + binsearch_bug(data, ii) + " should be " + binsearch_nobug(data, ii));
	}
	
	System.out.println("Queue bug:");
	String [] items = { "one", "two", "three" };
	Queue_nobug qnb = new Queue_nobug();
	Queue_bug qbg = new Queue_bug();
	for (int ii = 0; ii < items.length; ++ii) {
	    qnb.enqueue(items[ii]);
	    qbg.enqueue(items[ii]);
	}
	for (int ii = 0; ii < items.length; ++ii) {
	    String inb = qnb.dequeue();
	    if ( ! inb.equals(items[ii])) {
		System.out.println("ERROR in nobug version of queue!");
	    }
	    String ibg = qbg.dequeue();
	    System.out.println("  " + ii + ": " + ibg + " should be " + inb);
	}
	if (null != qnb.dequeue()) {
	    System.out.println("ERROR in nobug version of queue!");
	}
    }

}
