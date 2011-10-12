import java.util.ArrayList;
import java.util.Stack;
import java.util.LinkedList;

public class IdGraph
{
    public ArrayList<IdVertex> vertices;
    public ArrayList<IdEdge> edges;
    
    public IdGraph()
    {
	vertices = new ArrayList<IdVertex>();
	edges = new ArrayList<IdEdge>();
    }
    
    public IdVertex addVertex()
    {
	IdVertex vv = new IdVertex(vertices.size());
	vertices.add(vv);
	return vv;
    }
    
    public IdVertex getVertex(int id)
    {
	if (id < vertices.size()) {
	    return vertices.get(id);
	}
	IdVertex vv = new IdVertex(vertices.size());
	vertices.add(vv);
	return vv;
    }
    
    public IdEdge addEdge(IdVertex source, IdVertex destination)
    {
	IdEdge ee = new IdEdge(edges.size(), destination);
	edges.add(ee);
	source.neighbors.add(ee);
	return ee;
    }
    
    public IdEdge addEdge(int source_id, int destination_id)
    {
	return addEdge(getVertex(source_id), getVertex(destination_id));
    }
    
    public boolean dfs(IdVertex start, IdVertexIterationCallback cb)
    {
	int[] mark = new int[vertices.size()];
	for (int ii = 0; ii < vertices.size(); ++ii) {
	    mark[ii] = -1;
	}
	int counter = 0;
	Stack<IdVertex> stack = new Stack<IdVertex>();
	stack.push(start);
	do {
	    IdVertex current = stack.pop();
	    if (0 > mark[current.id]) {
		if (cb.processNodeIteration(current, counter)) {
		    return true;
		}
		mark[current.id] = counter;
		for (IdEdge ee : current.neighbors) {
		    if (0 > mark[ee.destination.id]) {
			stack.push(ee.destination);
		    }
		}
	    }
	    ++counter;
	} while (0 < stack.size());
	return false;
    }
}
