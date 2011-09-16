public class BinarySearch
{
    public static int verboseFind(int[] array, int value)
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
    
    public static int find(String[] array, String value, int effectiveLength)
    {
	int low = 0;
	int high = effectiveLength - 1;
	while (low <= high) {
	    int mid = (low + high) / 2;
	    int comparison = array[mid].compareTo(value);
	    if (comparison < 0) {
		low = mid + 1;
	    }
	    else if (comparison > 0) {
		high = mid - 1;
	    }
	    else {
		return mid;
	    }
	}
	return -1;
    }
    
    public static int find(StringVector vector, String value)
    {
	return find(vector.raw(), value, vector.size());
    }
    
    public static void main(String[] args)
    {
	int intArray[] = { -4, -1, 2, 5, 17, 42, 3001 };
	if (0 <= verboseFind(intArray, 4)) {
	    System.out.println("Failed to signal 4 as 'not found'");
	}
	if (1 != verboseFind(intArray, -1)) {
	    System.out.println("Failed to find -1 at index 1");
	}
	
	String[] stringArray = { "aaa", "aab", "aaz", "bbc", "zza", "zzz" };
	if (0 <= find(stringArray, "xyz", stringArray.length)) {
	    System.out.println("Failed to signal 'xyz' as 'not found'");
	}
	if (1 != find(stringArray, "zza", stringArray.length)) {
	    System.out.println("Failed to find 'zza' at index 4");
	}
    }
}
