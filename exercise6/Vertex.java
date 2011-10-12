import java.util.LinkedList;

public class Vertex
{
    public final String name;
    public LinkedList<Edge> neighbors;
    
    public Vertex(String _name)
    {
	name = _name;
	neighbors = new LinkedList<Edge>();
    }
}
