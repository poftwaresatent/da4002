public class StringBinaryTree
{
    public StringBinaryTreeNode root;
    
    public StringBinaryTree()
    {
        root = null;
    }
    
    public StringBinaryTree(String value)
    {
        root = new StringBinaryTreeNode(value, null, null);
    }
    
    public boolean merge(String value,
			 StringBinaryTree left,
			 StringBinaryTree right)
    {
        if (left.root == right.root && null != left.root) {
            return false;
        }
        root = new StringBinaryTreeNode(value, left.root, right.root);
        if (this != left) {
            left.root = null;
	}
        if (this != right) {
            right.root = null;
	}
	return true;
    }


    public void printPreOrder(String prefix)
    {
        if (null != root) {
            root.printPreOrder(prefix);
	}
    }

    public void printInOrder(String prefix)
    {
        if (null != root) {
           root.printInOrder(prefix);
	}
    }

    public void printPostOrder(String prefix)
    {
        if (null != root) {
           root.printPostOrder(prefix);
	}
    }

    public void clear()
    {
        root = null;
    }

    public boolean empty()
    {
        return null == root;
    }
    
    public int computeSize()
    {
	if (null == root) {
	    return 0;
	}
        return root.computeSize();
    }
    
    public int computeHeight()
    {
	if (null == root) {
	    return -1;
	}
        return root.computeHeight();
    }
    
    static public void main(String [ ] args)
    {
        StringBinaryTree t1 = new StringBinaryTree("1");
        StringBinaryTree t3 = new StringBinaryTree("3");
        StringBinaryTree t5 = new StringBinaryTree("5");
        StringBinaryTree t7 = new StringBinaryTree("7");
        StringBinaryTree t2 = new StringBinaryTree();
        StringBinaryTree t4 = new StringBinaryTree();
        StringBinaryTree t6 = new StringBinaryTree();

        t2.merge("2", t1, t3);
        t6.merge("6", t5, t7);
        t4.merge("4", t2, t6);

        System.out.println("t4 should be perfect 1-7; t2 empty");
        System.out.println("----------------");
        System.out.println("t4");
        t4.printInOrder("  ");
        System.out.println("----------------");
        System.out.println("t2");
        t2.printInOrder("  ");
        System.out.println("----------------");
        System.out.println("t4 size: " + t4.computeSize());
        System.out.println("t4 height: " + t4.computeHeight());
    }

}
