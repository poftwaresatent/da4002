class Node {
    double value;
    Node foo, bar;
    
    Node(double _value) {
	value = _value;
    }
}

class ContainerOne {
    Node handle;
    
    static Node helper(double value, Node node) {
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
    
    void insert(double value) {
	handle = helper(value, handle);
    }
}

class ContainerTwo {
    Node alpha;
    Node beta;
    
    void insert(double value) {
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
