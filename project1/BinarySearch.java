public class BinarySearch
{
    public static int verboseSearch(int[] array, int value)
    {
	int low = 0;
	int high = array.length - 1;
	while (low <= high) {
	    int mid = (low + high) / 2;
	    System.out.print(low + " < " + mid + " < " + high + "  array[mid] = " + array[mid]);
	    if (array[mid] < value) {
		System.out.println(" < " + value + " --> JUMP HIGHER (update lower bound)");
		low = mid + 1;
	    }
	    else if (array[mid] > value) {
		System.out.println(" > " + value + " --> JUMP LOWER (update upper bound)");
		high = mid - 1;
	    }
	    else {
		System.out.println(" = " + value + " --> FOUND at index " + mid);
		return mid;
	    }
	}
	System.out.println("value " + value + " NOT FOUND in array");
	return -1;
    }
    
    public static void main(String[] args)
    {
	int array[] = { -4, -1, 2, 5, 17, 42, 3001 };
	if (0 <= verboseSearch(array, 4)) {
	    System.out.println("Failed to signal 4 as 'not found'");
	}
	if (1 != verboseSearch(array, -1)) {
	    System.out.println("Failed to find -1 at index 1");
	}
    }
}
