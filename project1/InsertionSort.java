public class InsertionSort
{
    static private void dump(String title, int[] array, int ii)
    {
	System.out.print(title);
	for (int jj = 0; jj <= ii; ++jj) {
	    System.out.print("  " + array[jj]);
	}
	System.out.println();
    }
    
    
    static public void demo()
    {
	int[] array = { 17, 8, 99, 14, 1009, 71, 72, 99, 8, 70 };
	
	dump("init:", array, array.length - 1);
	
	for (int ii = 1; ii < array.length; ++ii) {
	    int ival = array[ii];

	    System.out.println();
	    System.out.println("ival[" + ii + "] = " + ival);
	    dump("  -->", array, ii);
	    
	    int jj = ii - 1;	    
	    for (; jj >= 0 && ival < array[jj]; --jj) {
		array[jj + 1] = array[jj];
		dump("  [" + jj + "]", array, ii);
	    }
	    array[++jj] = ival;
	    dump("  <--", array, ii);
	}
	
	System.out.println();
	dump("fini:", array, array.length - 1);
    }
    
    
    static public void sort(StringVector sv)
    {
	String[] array = sv.raw();
	for (int ii = 1; ii < array.length; ++ii) {
	    String ival = array[ii];
	    int jj = ii;
	    for ( ; jj > 0 && ival.compareTo(array[jj-1]) < 0; --jj) {
		array[jj] = array[jj-1];
	    }
	    array[jj] = ival;
	}
    }
    
    
    static public StringList createSortedList(StringList sl)
    {
	StringList sorted = new StringList();
	if (sl.empty()) {
	    return sorted;
	}
	StringListIterator src = sl.begin();
	sorted.pushFront(src.node.value);
	//dbg//	sorted.print("  init:", "    ");
	src.next();
	while (src.valid()) {
	    StringListIterator dst = sorted.begin();
	    if (src.node.value.compareTo(dst.node.value) <= 0) {
		sorted.pushFront(src.node.value);
		//dbg// sorted.print("  push " + src.node.value + ":", "    ");
	    }
	    else {
		while (src.node.value.compareTo(dst.node.value) > 0 && null != dst.node.next) {
		    dst.next();
		}
		if (null != dst.node.next) {
		    //dbg// String dbg = "insert " + src.node.value + " before " + dst.node.value;
		    sorted.insertBefore(src.node.value, dst);
		    //dbg// sorted.print("  " + dbg + ":", "    ");
		}
		else {
		    if (src.node.value.compareTo(dst.node.value) > 0) {
			//dbg// String dbg = "insert " + src.node.value + " after last node " + dst.node.value;
			sorted.insertAfter(src.node.value, dst);
			//dbg// sorted.print("  " + dbg + ":", "    ");
		    }
		    else {
			//dbg// String dbg = "insert " + src.node.value + " before last node " + dst.node.value;
			sorted.insertBefore(src.node.value, dst);
			//dbg// sorted.print("  " + dbg + ":", "    ");
		    }
		}
	    }
	    src.next();
	}
	return sorted;
    }
    
    
    static public void main(String[] args)
    {
	String[] dataset = Factory.createRandomStrings(10);
	StringVector sv = new StringVector(dataset);

	sv.print("StringVector before:", "  ");
	sort(sv);
	sv.print("StringVector after:", "  ");
	
	StringList sl = createSortedList(new StringList(dataset));
	sl.print("StringList after:", "  ");
	
	StringListIterator ilist = sl.begin();
	int ivec = 0;
	boolean ok = true;
	while (ilist.valid() && ivec < sv.size()) {
	    if ( ! ilist.get().equals(sv.at(ivec))) {
		System.out.println("MISMATCH at index " + ivec + ": " + ilist.get() + " should be " + sv.at(ivec));
		ok = false;
		break;
	    }
	    ilist.next();
	    ++ivec;
	}
	if (ok && (ilist.valid() || ivec < sv.size())) {
	    System.out.println("SIZE mismatch");
	}
    }

}
