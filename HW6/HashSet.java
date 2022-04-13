/** 
 * Represents the HashSet class.
 * HashSet implement Set interface.
 * @see Set  
 * @param E object-type to hold in set.
 * @author Bahadir Etka Kilinc
 * @version 1.0
 * @since 2021-01-25
*/

public class HashSet<E> implements Set<E>{
	private E[] elements; // underlying container.
	private int numberOfElements;

	/** No paramater constructor. Initial size is zero, and 
	 *  underlying container created. 
	 */
	public HashSet(){
		numberOfElements = 0;
	}

	/* Returns an Iterator over HashSet. */
	@Override
	public Iterator<E> iterator(){
		@SuppressWarnings("unchecked")
		E[][] temp = (E[][]) new Object[1][numberOfElements];
		temp[0] = elements;

		return new Iterator<E>(temp,this);
	}


	/**
	 * Ensures that HashSet contains the specified element 
	 * Adds if it's not in the HashSet, does not do anything 
	 * if it's already in the HashSet. 
	 * @param e, element to insert to HashSet. 
	 */
	@Override
	public void add(E e){
		if(isEmpty()){
			@SuppressWarnings("unchecked")
			E[] temp = (E[]) new Object[1];
			elements = temp;
			elements[0] = e;
			setSize(size()+1);
		}
		else if(!contains(e)){
			setSize(size()+1); // grow the size.
			@SuppressWarnings("unchecked")
			E[] temp = (E[]) new Object[size()]; 

			for(int i=0;i<elements.length;++i) // copy the previous.
				temp[i] = elements[i];

			temp[size()-1] = e; // add the new.
			elements = temp;
		}
	}

	
	/** 
	 * Ensures that HashSet contains all of the elements in the 
	 * specified collection. Again, duplicates are not permitted. 
	 * @param c, collection to insert. 
	**/
	@Override
	public void addAll(Collection<E> c){
		Iterator<E> begin = c.iterator();
		while(begin.hasNext())
			add(begin.next());
	}

	/**
	 * Removes all of the elements from HashSet 
	**/
	@Override
	public void clear(){
		elements = null;
		setSize(0);
	}

	/**
	 * Returns true if the HashSet contains the specified element. 
	**/
	public boolean contains(E e){
		boolean found = false;

		if(isEmpty())
			found = false;
		else{
			for(int i=0;i<size() && !found;++i){
				if(elements[i] == e)
					found = true;
			}
		}
		return found;
	}

	
	/**
	 * Returns true if this HashSet contains all of the elements in the
     * specified collection.
	 * @param c, collection to look for.
    **/
	@Override
	public boolean containsAll(Collection<E> c){
		boolean found = true;
		Iterator<E> begin = c.iterator();
		while(begin.hasNext())
			found = found && contains(begin.next());
		
		return found;
	}

	/**
	 * Returns true if the HashSet contains no element. 
	 **/
	@Override
	public boolean isEmpty(){
		return size()==0;
	}

	/**
	 * Ensures that HashSet does not contain the specified element
	 * Removes if it's in the HashSet, does not do anything
	 * if it's already not in the HashSet
	 * @param e, element to remove from HashSet.
	 */
	@Override
	@SuppressWarnings("unchecked")
	public void remove(E e){
		if(contains(e)){
			setSize(size()-1);
			E[] temp = (E[])new Object[size()];


			for(int i=0,j=0;i<elements.length;++i){
				if(elements[i] != e)
					temp[j++] = elements[i];
			}
			elements = temp;
		}
	}


	
	/**
	 * Removes all of HashSet's elements that are also contained
	 * in the specified collection.
	 * @param c, collection to remove from set.
	*/
	@Override
	public void removeAll(Collection<E> c){
		Iterator<E> begin = c.iterator();
		while(begin.hasNext())
			remove(begin.next());
	}

	
	/**
	 * Retains only the elements HashSet that are contained in
	 * the specified collection
	 * @param c, collection to retain. 
	**/
	@Override
	public void retainAll(Collection<E> c){	
		Iterator<E> begin = c.iterator();
		while(begin.hasNext())
		{
			E temp = begin.next();
			if(!contains(temp))
				c.remove(temp);
		}
	}

	/**
	 * Returns the number of elements in HashSet
	 *@return size of HashSet. 
	**/
	public int size(){	
		return numberOfElements;
	}

	private void setSize(int size){
		numberOfElements = size;
	}	
}