import java.util.*;

class V4 {
    String name;
    LinkedList<V4> neighbors;
    
    V4(String name_) {
	name = name_;
	neighbors = new LinkedList<V4>();
    }
}

class G4 {
    TreeMap<String, V4> vertices;
    
    G4() {
	vertices = new TreeMap<String, V4>();
	addEdge("A", "B");
	addEdge("A", "C");
	addEdge("B", "A");
	addEdge("B", "D");
	addEdge("B", "E");
	addEdge("C", "A");
	addEdge("C", "B");
	addEdge("C", "F");
	addEdge("D", "C");
	addEdge("D", "F");
	addEdge("E", "G");
	addEdge("F", "D");
	addEdge("F", "G");
	addEdge("G", "D");
    }
    
    void addEdge(String src, String dst) {
	V4 from = vertices.get(src);
	if (null == from) {
	    from = new V4(src);
	    vertices.put(src, from);
	}
	V4 to = vertices.get(dst);
	if (null == to) {
	    to = new V4(dst);
	    vertices.put(dst, to);
	}
	from.neighbors.add(to);
    }
    
    void dump() {
	for (V4 vv : vertices.values()) {
	    System.out.print(vv.name + ":");
	    for (V4 nn : vv.neighbors) {
		System.out.print(" " + nn.name);
	    }
	    System.out.println();
	}
    }
    
    void dfs(String src) {
	System.out.println("DFS from " + src);
	V4 start = vertices.get(src);
	if (null == start) {
	    System.out.println("  no such vertex");
	    return;
	}
	HashSet<V4> closed = new HashSet<V4>();
	Stack<V4> open = new Stack<V4>();
	open.push(start);
	for (int counter = 0; 0 < open.size(); ++counter) {
	    System.out.print("  stack:");
	    for (V4 ss : open) {
		System.out.print(" " + ss.name);
	    }
	    System.out.println();
	    V4 current = open.pop();
	    if (closed.contains(current)) {
		System.out.println("    (skip " + current.name + ")");
	    }
	    else {
		System.out.println("    visit " + current.name);
		closed.add(current);
		System.out.print("      push");
		for (V4 next : current.neighbors) {
		    if ( ! closed.contains(next)) {
			System.out.print(" " + next.name);
			open.push(next);
		    }
		}
		System.out.println();
	    }
	}
    }
    
    void bfs(String src)
    {
	System.out.println("BFS from " + src);
	V4 start = vertices.get(src);
	if (null == start) {
	    System.out.println("  no such vertex");
	    return;
	}
	HashSet<V4> closed = new HashSet<V4>();
	LinkedList<V4> open = new LinkedList<V4>();
	open.offer(start);
	for (int counter = 0; 0 < open.size(); ++counter) {
	    System.out.print("  queue:");
	    for (V4 ss : open) {
		System.out.print(" " + ss.name);
	    }
	    System.out.println();
	    V4 current = open.poll();
	    if (closed.contains(current)) {
		System.out.println("    (skip " + current.name + ")");
	    }
	    else {
		System.out.println("    visit " + current.name);
		closed.add(current);
		System.out.print("      enqueue");
		for (V4 next : current.neighbors) {
		    if ( ! closed.contains(next)) {
			System.out.print(" " + next.name);
			open.offer(next);
		    }
		}
		System.out.println();
	    }
	}
    }
}

public class S4 {
    static public void main(String[] args) {
	G4 graph = new G4();
	graph.dump();
	graph.dfs("D");
	graph.bfs("D");
	graph.dfs("A");
	graph.bfs("A");
    }
}
