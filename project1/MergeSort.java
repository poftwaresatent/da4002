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
    
    
    static private void merge(String[] dst, String[] src, int begin, int middle, int end)
    {	
	int ii = begin;
	int jj = middle;
	int kk = begin;
	while (ii < middle && jj < end) {
	    if (src[ii].compareTo(src[jj]) < 0) {
		dst[kk++] = src[ii++];
	    }
	    else {
		dst[kk++] = src[jj++];
	    }
	}
	while (ii < middle) {
	    dst[kk++] = src[ii++];
	}
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
	mSort(tmp, array, begin, middle);
	mSort(tmp, array, middle, end);
	merge(array, tmp, begin, middle, end);
    }
    
    
    static public void sort(StringVector sv)
    {
	String[] tmp = new String[sv.size()];
	for (int ii = 0; ii < sv.size(); ++ii) {
	    tmp[ii] = sv.at(ii);
	}
	mSort(sv.raw(), tmp, 0, sv.size());
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
