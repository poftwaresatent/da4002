import java.util.LinkedList;


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
	    int nextdist = qe.dist + 1;
	    int xx, yy;
	    
	    // try to go west
	    xx = qe.xx - 1;
	    yy = qe.yy;
	    if (map[xx][yy] != WALL && goaldist[xx][yy] > nextdist) {
		goaldist[xx][yy] = nextdist;
		pq.add(new QueueElement(nextdist, xx, yy));
	    }
	    
	    // try to go east
	    xx = qe.xx + 1;
	    if (map[xx][yy] != WALL && goaldist[xx][yy] > nextdist) {
		goaldist[xx][yy] = nextdist;
		pq.add(new QueueElement(nextdist, xx, yy));
	    }
	    
	    // try to go north
	    xx = qe.xx;
	    yy = qe.yy - 1;
	    if (map[xx][yy] != WALL && goaldist[xx][yy] > nextdist) {
		goaldist[xx][yy] = nextdist;
		pq.add(new QueueElement(nextdist, xx, yy));
	    }

	    // try to go south
	    yy = qe.yy + 1;
	    if (map[xx][yy] != WALL && goaldist[xx][yy] > nextdist) {
		goaldist[xx][yy] = nextdist;
		pq.add(new QueueElement(nextdist, xx, yy));
	    }
	    
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
