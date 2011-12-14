import java.util.HashSet;
import java.util.HashMap;
import java.util.LinkedList;
import java.util.StringTokenizer;
import java.io.BufferedReader;
import java.io.FileReader;
import java.io.FileNotFoundException;
import java.io.IOException;

class TopoOrder {
    HashSet<String> vertices;
    HashMap<String, HashSet<String> > edges;
    
    TopoOrder() {
	vertices = new HashSet();
	edges = new HashMap();
    }
    
    void load(String filename) throws FileNotFoundException, IOException
    {
	BufferedReader in = new BufferedReader(new FileReader(filename));
	String line;
	while (null != (line = in.readLine())) {
	    StringTokenizer st = new StringTokenizer(line);
	    String source = st.nextToken();
	    String destination = st.nextToken();
	    vertices.add(source);
	    vertices.add(destination);
	    if ( ! edges.containsKey(source)) {
		edges.put(source, new HashSet());
	    }
	    edges.get(source).add(destination);
	}
    }
    
    LinkedList<String> topo() {
	HashMap<String, Integer> indeg = new HashMap();
	for (String vv : vertices) {
	    indeg.put(vv, new Integer(0));
	}
	for (HashSet<String> ee : edges.values()) {
	    for (String dst : ee) {
		indeg.put(dst, new Integer(indeg.get(dst) + 1));
	    }
	}
	
	LinkedList<String> order = new LinkedList();
	LinkedList<String> queue = new LinkedList();
	for (String vv : vertices) {
	    if (0 == indeg.get(vv)) {
		queue.offer(vv);
	    }
	}
	
	while (0 != queue.size()) {
	    String vv = queue.poll();
	    order.add(vv);
	    if (edges.containsKey(vv)) {
		for (String dst : edges.get(vv)) {
		    int nd = indeg.get(dst) - 1;
		    indeg.put(dst, nd);
		    if (0 == nd) {
			queue.offer(dst);
		    }
		}
	    }
	}
	
	for (String vv : vertices) {
	    if (0 != indeg.get(vv)) {
		return null;
	    }
	}
	
	return order;
    }
    
    public static void main(String[] args) {
	for (int ii = 0; ii < args.length; ++ii) {
	    try {
		TopoOrder gg = new TopoOrder();
		gg.load(args[ii]);
		LinkedList<String> order = gg.topo();
		if (null == order) {
		    System.out.println("There is a cycle in " + args[ii]);
		}
		else {
		    System.out.println("Topological order of " + args[ii]);
		    for (String vv : order) {
			System.out.println("  " + vv);
		    }
		}
	    }
	    catch (Exception ee) {
		System.out.println("EXCEPTION while processing " + args[ii]);
		System.out.println("  " + ee);
	    }
	}
    }
    
}
