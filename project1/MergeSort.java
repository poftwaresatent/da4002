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
    
    
    static private void doSort(String[] array, String[] tmp, int begin, int end)
    {
	int length = end - begin;
	if (length <= 1) {
	    return;
	}
	
	int middle = begin + length / 2;
	doSort(tmp, array, begin, middle);
	doSort(tmp, array, middle, end);
	
	int ii = begin;
	int jj = middle;
	int kk = begin;
	while (ii < middle && jj < end) {
	    if (tmp[ii].compareTo(tmp[jj]) < 0) {
		array[kk++] = tmp[ii++];
	    }
	    else {
		array[kk++] = tmp[jj++];
	    }
	}
	while (ii < middle) {
	    array[kk++] = tmp[ii++];
	}
	while (jj < end) {
	    array[kk++] = tmp[jj++];
	}
    }
    
    
    static public void sort(StringVector sv)
    {
	String[] tmp = new String[sv.size()];
	for (int ii = 0; ii < sv.size(); ++ii) {
	    tmp[ii] = sv.at(ii);
	}
	doSort(sv.raw(), tmp, 0, sv.size());
    }
    
    
    static public void main(String[] args)
    {
	String[] dataset = Factory.createRandomStrings(7);
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
