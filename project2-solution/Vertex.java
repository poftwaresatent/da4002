import java.util.LinkedList;

public class Vertex
{
    public final String name;
    public double value;
    public LinkedList<Edge> neighbors;
    
    public Vertex(String _name, double _value)
    {
	name = _name;
	value = _value;
	neighbors = new LinkedList<Edge>();
    }
}
