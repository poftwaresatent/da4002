import java.util.HashMap;
import java.util.HashSet;
import java.util.Stack;
import java.util.LinkedList;

public class Graph
{
    public HashMap<String, Vertex> vertices;
    
    public Graph()
    {
	vertices = new HashMap<String, Vertex>();
    }
    
    public Vertex findVertex(String name)
    {
	return vertices.get(name);
    }
    
    public Vertex getOrMakeVertex(String name)
    {
	Vertex vv = vertices.get(name);
	if (null == vv) {
	    vv = new Vertex(name);
	    vertices.put(name, vv);
	}
	return vv;
    }
    
    public Edge addEdge(Vertex source, Vertex destination)
    {
	Edge ee = new Edge(destination);
	source.neighbors.add(ee);
	return ee;
    }
    
    public Edge addEdge(String source, String destination)
    {
	return addEdge(getOrMakeVertex(source), getOrMakeVertex(destination));
    }
    
    public boolean dfs(Vertex start, ProcessVertex pv)
    {
	HashSet<Vertex> closed = new HashSet<Vertex>();
	Stack<Vertex> open = new Stack<Vertex>();
	open.push(start);
	for (int counter = 0; 0 < open.size(); ++counter) {
	    Vertex current = open.pop();
	    if ( ! closed.contains(current)) {
		if (pv.visit(current, counter)) {
		    return true;
		}
		closed.add(current);
		for (Edge ee : current.neighbors) {
		    if ( ! closed.contains(ee.destination)) {
			open.push(ee.destination);
		    }
		}
	    }
	}
	return false;
    }
}
