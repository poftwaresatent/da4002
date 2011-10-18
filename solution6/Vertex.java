import java.util.LinkedList;

public class Vertex
{
    public final String name;
    public double value;
    public LinkedList<Edge> neighbors;
    
    public Vertex(String _name)
    {
	name = _name;
	value = 0.0;
	neighbors = new LinkedList<Edge>();
    }
}
