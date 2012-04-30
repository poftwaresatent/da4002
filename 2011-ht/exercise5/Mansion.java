import java.util.LinkedList;

//////////////////////////////////////////////////
//////////////////////////////////////////////////
////
//// This is an almost-finished application.  Your assignment is to
//// fill in the missing implementation inside method propagate of the
//// Mansion class.
////
//// There are detailed instructions there, and you do not need to
//// change any of the other code. However, you should carefully read
//// all of the code, so that you understand the entire application.
////
//////////////////////////////////////////////////
//////////////////////////////////////////////////


class QueueElement
    implements Comparable<QueueElement>
{
    public QueueElement(int _dist, int _xx, int _yy) {
	dist = _dist;
	xx = _xx;
	yy = _yy;
    }
    
    public int compareTo(QueueElement other) {
	return dist - other.dist;
    }
    
    public final int dist, xx, yy;
}


public class Mansion
{
    private static final char WALL =  '#';
    private static final char FLOOR = ' ';
    private static final char PATH =  'o';
    private static final char START = '+';
    private static final char GOAL =  'x';
    
    private char[][] map;
    private int[][] goaldist;
    
    
    public Mansion()
    {
	map = new char[16][12];
	for (int xx = 0; xx < 16; ++xx) {
	    for (int yy = 0; yy < 12; ++yy) {
		map[xx][yy] = WALL;
	    }
	}
	for (int xx = 1; xx <= 5; ++xx) {
	    for (int yy = 1; yy <= 4; ++yy) {
		map[xx][yy] = FLOOR;
	    }
	    for (int yy = 6; yy <= 10; ++yy) {
		map[xx][yy] = FLOOR;
	    }
	}
	for (int xx = 7; xx <= 14; ++xx) {
	    for (int yy = 1; yy <= 7; ++yy) {
		map[xx][yy] = FLOOR;
	    }
	    for (int yy = 9; yy <= 10; ++yy) {
		map[xx][yy] = FLOOR;
	    }
	}
	map[6][3] = FLOOR;
	map[6][10] = FLOOR;
	map[8][8] = FLOOR;
	map[13][8] = FLOOR;
    }
    
    
    //////////////////////////////////////////////////
    //////////////////////////////////////////////////
    ////
    //// The propagate method is incomplete, you have to fill in the
    //// missing parts as explained in the code below.
    ////
    //// This method receives goal coordinates and must implement the
    //// NF1 algorithm. The initialization is already done for you:
    //// first, the goal distance table is re-initialized, the goal
    //// distance of the goal cell is set to zero, and the propagation
    //// queue is initialized with the goal cell. Your task is to do
    //// the actual propagation step inside the while loop.
    ////
    public boolean propagate(int goalx, int goaly)
    {
	if (map[goalx][goaly] == WALL) {
	    return false;
	}
	
	goaldist = new int[16][12];
	for (int xx = 0; xx < 16; ++xx) {
	    for (int yy = 0; yy < 12; ++yy) {
		goaldist[xx][yy] = Integer.MAX_VALUE;
	    }
	}
	
	LinkedList<QueueElement> pq = new LinkedList<QueueElement>();
	goaldist[goalx][goaly] = 0;
	pq.add(new QueueElement(0, goalx, goaly));
	
	while (0 != pq.size()) {
	    
	    QueueElement qe = pq.poll();
	    
	    //////////////////////////////////////////////////
	    //////////////////////////////////////////////////
	    ////
	    //// Put your code here.
	    ////
	    //// The qe variable contains the currently active
	    //// cell. You can access its coordinates by using qe.xx
	    //// and qe.yy, which are indices for the map of the
	    //// environment and the goal distance table (see
	    //// below). The distance between the current cell and the
	    //// goal can be retrieved in the qe.dist variable.
	    ////
	    //// The field called map is a two-dimensional array of
	    //// characters which encode whether a cell is an obstacle
	    //// or not. All obstacles contain the value WALL. This is
	    //// important so that your propagation does not go into
	    //// walls!
	    ////
	    //// The field called goaldist is a two-dimensional array
	    //// of natural numbers which record the length of the
	    //// shortest path to the goal. It is your task to compute
	    //// and store the goaldist! Note that the goal cell's
	    //// goaldist is already set to zero above, your task is
	    //// to assign goaldist=1 to the 4 immediate neighbors of
	    //// the goal, then two to their immediate neighbors,
	    //// etc. Also note that al non-goal cells have been
	    //// initialized to a goaldist of Integer.MAX_VALUE, which
	    //// is a very large number. You can use this fact to
	    //// determine if a particular goaldist entry should be
	    //// overwritten or not: a goaldist should obly be
	    //// overwritten by a smaller value, never a bigger one.
	    ////
	    //// More detailed instructions are written as comments
	    //// further below as well.
	    ////
	    //// You can find more information about multi-dimensional
	    //// arrays in Java on the official tutorial website at
	    //// http://download.oracle.com/javase/tutorial/java/nutsandbolts/arrays.html
	    ////
	    
	    //////////////////////////////////////////////////
	    // 1. compute the next goal distance and store it in a variable
	    
	    //////////////////////////////////////////////////
	    // 2. attempt propagation to the WEST:
	    //
	    // check whether the neighbor at [qe.xx-1][qe.yy] can
	    // be updated:
	    //  - Make sure it is not a wall!
	    //  - Check whether its current goaldist is higher than
	    //    the next goal distance.
	    //  - In case you update the neighbor's goaldist, place
	    //    it in the queue so that later its neighbors will
	    //    get propagated as well.
	    //
	    // HINT: You can add a cell to the queue by using code like this:
	    //
	    //    pq.add(new QueueElement(nextdist, xx, yy));
	    //
	    //    This is very similar to the idea of level-order
	    //    traversal in trees. You can look at the
	    //    StringTree class from exercise 3.1 to get further
	    //    inspiration.
	    
	    //////////////////////////////////////////////////
	    // 3. attempt propagation to the EAST:
	    //
	    // repeat step 2 for [qe.xx+1][qe.yy]

	    //////////////////////////////////////////////////
	    // 4. attempt propagation to the NORTH:
	    //
	    // repeat step 2 for [qe.xx][qe.yy-1]

	    //////////////////////////////////////////////////
	    // 5. attempt propagation to the SOUTH:
	    //
	    // repeat step 2 for [qe.xx][qe.yy+1]
	    
	    ////
	    //// END OF implementation to be filled in by students.
	    ////
	    //// It should not be necessary to touch anything below,
	    //// but of course reading the existing code is part of
	    //// understanding the context you have to work in.
	    ////
	    //////////////////////////////////////////////////
	    //////////////////////////////////////////////////
	    
	}
	
	return true;
    }
    
    
    public boolean backtrace(int startx, int starty)
    {
	if (null == goaldist
	    || map[startx][starty] == WALL
	    || goaldist[startx][starty] == Integer.MAX_VALUE) {
	    return false;
	}
	
	// remove old path
	for (int xx = 0; xx < 16; ++xx) {
	    for (int yy = 0; yy < 12; ++yy) {
		if (map[xx][yy] != WALL) {
		    map[xx][yy] = FLOOR;
		}
	    }
	}
	
	int xx = startx;
	int yy = starty;
	map[xx][yy] = START;
	while (goaldist[xx][yy] > 0) {
	    int mindist = goaldist[xx][yy];
	    int nx = -1;
	    int ny = -1;
	    for (int ix = xx - 1; ix <= xx + 1; ++ix) {
		for (int iy = yy - 1; iy <= yy + 1; ++iy) {
		    if (goaldist[ix][iy] < mindist) {
			mindist = goaldist[ix][iy];
			nx = ix;
			ny = iy;
		    }
		}
	    }
	    if (0 > nx) {
		return false;
	    }
	    xx = nx;
	    yy = ny;
	    map[xx][yy] = PATH;
	}
	map[xx][yy] = GOAL;
	
	return true;
    }
    
    
    public void print()
    {
	System.out.print("  ");
	for (int ix = 0; ix < 14; ++ix) {
	    System.out.print((char)((int)'a' + ix));
	}
	System.out.println();
	for (int iy = 0; iy < 12; ++iy) {
	    if ((iy > 0) && (iy < 11)) {
		System.out.print(iy - 1);
	    }
	    else {
		System.out.print(' ');
	    }
	    for (int ix = 0; ix < 16; ++ix) {
		System.out.print(map[ix][iy]);
	    }
	    if ((iy > 0) && (iy < 11)) {
		System.out.print(iy - 1);
	    }
	    System.out.println();
	}
	System.out.print("  ");
	for (int ix = 0; ix < 14; ++ix) {
	    System.out.print((char)((int)'a' + ix));
	}
	System.out.println();
    }
    
    
    static public Pair<Integer> parseCoordinate(String string)
	throws RuntimeException
    {
	if (string.length() != 2) {
	    throw new RuntimeException("coordinate strings must look like a8 or L3 or so");
	}
	final int ix = (int)Character.toUpperCase(string.charAt(0)) - (int)'A' + 1;
	if (ix < 1 || ix > 15) {
	    throw new RuntimeException("X coordinate is not in range a-n");
	}
	final int iy = (int)string.charAt(1) - (int)'0' + 1;
	if (iy < 1 || iy > 11) {
	    throw new RuntimeException("Y coordinate is not in range 0-9");
	}
	return new Pair<Integer>(ix, iy);
    }
    
    
    static public void main(String[] args)
    {
	Mansion house = new Mansion();
	
	if (args.length < 2) {
	    house.print();
	    System.out.println();
	    System.out.println("Please specify start and goal coordinates, for instance `a0 n9'");
	}
	else {
	    try {
		Pair<Integer> start = parseCoordinate(args[0]);
		Pair<Integer> goal = parseCoordinate(args[1]);
		
		if ( ! house.propagate(goal.one, goal.two)) {
		    throw new RuntimeException("failed to propagate");
		}
		if ( ! house.backtrace(start.one, start.two)) {
		    throw new RuntimeException("failed to backtrace");
		}
		house.print();
	    }
	    catch (Exception ee) {
		System.err.println(ee);
	    }
	}
    }
    
}
