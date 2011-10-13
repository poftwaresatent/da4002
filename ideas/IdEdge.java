public class IdEdge
{
    public final int id;
    public IdVertex destination;
    
    /**
       If you want to use the id as index into various external data
       stores, you have to make sure to generate consistent ids. The
       addEdge method of the IdGraph class does this for you.
    */
    public IdEdge(int _id, IdVertex _destination)
    {
	id = _id;
	destination = _destination;
    }
}
