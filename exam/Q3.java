class Node {
    long value;
    Node foo, bar;
    
    Node(long _value) {
	value = _value;
    }
}

class ContainerOne {
    Node handle;
    
    static Node helper(long value, Node node) {
	if (null == node) {
	    return new Node(value);
	}
	if (value < node.value) {
	    node.foo = helper(value, node.foo);
	}
	else if (value > node.value) {
	    node.bar = helper(value, node.bar);
	}
	return node;
    }
    
    void insert(long value) {
	handle = helper(value, handle);
    }
}

class ContainerTwo {
    Node alpha;
    Node beta;
    
    void insert(long value) {
	Node node = new Node(value);
	if (null == beta) {
	    alpha = node;
	    beta = node;
	    return;
	}
	beta.foo = node;
	node.bar = beta;
	beta = node;
    }
}
