import java.util.*;

class Vertex {
    final String name;
    LinkedList<Vertex> neighbors;
    
    Vertex(String _name) {
	name = _name;
	neighbors = new LinkedList<Vertex>();
    }
}

class Graph {
    public HashMap<String, Vertex> vertices;
    
    public Graph()
    {
	vertices = new HashMap<String, Vertex>();
	Vertex a = new Vertex("A");
	Vertex b = new Vertex("B");
	Vertex c = new Vertex("C");
	Vertex d = new Vertex("D");
	vertices.put("A", a);
	vertices.put("B", b);
	vertices.put("C", c);
	vertices.put("D", d);
	a.neighbors.add(b);
	a.neighbors.add(c);
	b.neighbors.add(c);
	b.neighbors.add(d);
	d.neighbors.add(a);
    }
}
