public class MergeSort
{
    static private void merge(String[] dst, String[] src, int begin, int middle, int end)
    {	
	int ii = begin;		// first half of the source
	int jj = middle;	// second half of the source
	int kk = begin;		// destination
	
	// First go along the first and the second halves of the
	// source, appending the smaller of the two to the
	// destination.
	
	while (ii < middle && jj < end) {
	    if (src[ii].compareTo(src[jj]) < 0) {
		dst[kk++] = src[ii++];
	    }
	    else {
		dst[kk++] = src[jj++];
	    }
	}
	
	// Copy the remainder of the first half, if any.
	while (ii < middle) {
	    dst[kk++] = src[ii++];
	}
	
	// Copy the remainder of the second half, if any.
	while (jj < end) {
	    dst[kk++] = src[jj++];
	}
    }
    
    
    static private void mSort(String[] array, String[] tmp, int begin, int end)
    {
	int length = end - begin;
	if (length <= 1) {
	    return;
	}
	int middle = begin + length / 2;
	
	// trick to avoid copy:
	// - swap array and tmp in recursion
	// - merge tmp into array
	
	mSort(tmp, array, begin, middle);
	mSort(tmp, array, middle, end);
	merge(array, tmp, begin, middle, end);
    }
    
    
    static public void sort(String[] array, int effectiveLength)
    {
	// In order to do the merge, we need a temporary array as
	// scratch area. In order to avoid creating and destroying
	// such a temporary in each step, we create it here and pass
	// it into the recursion. In order to avoid copying the result
	// of the merge back into the container, we use the trick of
	// alternating the temporary and the container at each
	// step. For this trick to work properly, we have to first
	// copy all the data into the temporary.
	
	String[] tmp = Factory.duplicate(array, effectiveLength);
	mSort(array, tmp, 0, effectiveLength);
    }
    
    
    static public void sort(String[] sa)
    {
	sort(sa, sa.length);
    }
    
    
    static private void print(String title, String prefix, String[] array)
    {
	System.out.println(title);
	for (int jj = 0; jj < array.length; ++jj) {
	    System.out.println(prefix + array[jj]);
	}
    }
    
    
    static public void main(String[] args)
    {
	String[] data = Factory.createRandomStrings(30);
	
	print("unsorted:", "  ", data);
	sort(data);
	print("\nsorted:", "  ", data);
    }

}
