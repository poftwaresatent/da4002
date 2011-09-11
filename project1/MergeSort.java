public class MergeSort
{
    static private void dump(String title, int[] array, int begin, int end)
    {
	System.out.print(title);
	for (int jj = begin; jj < end; ++jj) {
	    System.out.print("  " + array[jj]);
	}
	System.out.println();
    }
    
    
    static public void sort(String[] array, String[] tmp, int begin, int end)
    {
	int length = end - begin;
	if (length <= 1) {
	    return;
	}
	
	int middle = begin + length / 2;
	sort(array, tmp, begin, middle);
	sort(array, tmp, middle, end);
	
	int ii = begin;
	int jj = middle;
	int kk = begin;
	while (ii < middle && jj < end) {
	    if (array[ii].compareTo(array[jj]) < 0) {
		tmp[kk++] = array[ii++];
	    }
	    else {
		tmp[kk++] = array[jj++];
	    }
	}
	while (ii < middle) {
	    tmp[kk++] = array[ii++];
	}
	while (jj < end) {
	    tmp[kk++] = array[jj++];
	}
	
	for (ii = begin; ii < end; ++ii) {
	    array[ii] = tmp[ii];
	}
    }
    
    
    static public void sort(StringVector sv)
    {
	String[] tmp = new String[sv.size()];
	sort(sv.raw(), tmp, 0, sv.size());
    }
    
    
    static public void main(String[] args)
    {
	String[] dataset = Factory.createRandomStrings(10);
	StringVector sv = new StringVector(dataset);

	sv.print("StringVector before:", "  ");
	sort(sv);
	sv.print("StringVector after:", "  ");
	
	// StringList sl = createSortedList(new StringList(dataset));
	// sl.print("StringList after:", "  ");
	
	// StringListIterator ilist = sl.begin();
	// int ivec = 0;
	// boolean ok = true;
	// while (ilist.valid() && ivec < sv.size()) {
	//     if ( ! ilist.get().equals(sv.at(ivec))) {
	// 	System.out.println("MISMATCH at index " + ivec + ": " + ilist.get() + " should be " + sv.at(ivec));
	// 	ok = false;
	// 	break;
	//     }
	//     ilist.next();
	//     ++ivec;
	// }
	// if (ok && (ilist.valid() || ivec < sv.size())) {
	//     System.out.println("SIZE mismatch");
	// }
    }

}
