import java.util.LinkedList;

public class Vertex
{
    public final String name;
    public double value;
    public Vertex backpointer;
    public LinkedList<Edge> neighbors;
    
    public Vertex(String _name)
    {
	name = _name;
	value = 0.0;
	backpointer = null;
	neighbors = new LinkedList<Edge>();
    }
}
