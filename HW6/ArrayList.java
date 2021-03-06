/** 
 * Represents the ArrayList class.
 * ArrayList implement Set interface.
 * @see Set  
 * @param E object-type to hold in set.
 * @author Bahadir Etka Kilinc
 * @version 1.0
 * @since 2021-01-25
*/

public class ArrayList<E> implements Set<E>{
	private E[] elements; // underlying container.
	private int numberOfElements;

	/** No paramater constructor. Initial size is zero, and 
	 *  underlying container created. 
	 */
	public ArrayList(){
		numberOfElements = 0;
	}

	/**
	 * Returns an Iterator over ArrayList. 
	 * Since List is an ordered collection, you have a precise
	 * control over where in the list each is element is inserted
	 * due to insertion order. 
	 * @see Iterator
	 * @return Iterator over a ArrayList.
	 */
	@Override
	public Iterator<E> iterator(){
		@SuppressWarnings("unchecked")
		E[][] temp = (E[][]) new Object[1][numberOfElements];
		temp[0] = elements;

		return new Iterator<E>(temp,this);
	}


	/**
	 * Inserts the specified element into this ArrayList
	 * You can have duplicates of an element and insertion  
	 * order specifies your sequence's order.
	 * @param E, Element to insert.
	**/
	@Override
	public void add(E e){
		if(isEmpty()){
			@SuppressWarnings("unchecked")
			E[] temp = (E[]) new Object[1];
			elements = temp;
			elements[0] = e;
			setSize(size()+1);
		}
		else{
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
	 * Ensures that ArrayList contains all of the elements in the 
	 * specified collection. Duplicates are permitted. 
	 * @param c, collection to insert. 
	**/
	@Override
	public void addAll(Collection<E> c){
		Iterator<E> begin = c.iterator();
		while(begin.hasNext())
			add(begin.next());
	}

	/**
	 * Removes all of the elements from ArrayList 
	**/
	@Override
	public void clear(){
		elements = null;
		setSize(0);
	}

	/**
	 * Returns true if the ArrayList contains the specified element
	 * at least one time. 
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
	* Returns true if this ArrayList contains all of the elements in the
	* specified collection. All of them must be in the ArrayList at least
	* one time.
	* @param c, collection to look for.
	**/
	@Override
	public boolean containsAll(Collection<E> c)
	{
		boolean found = true;
		Iterator<E> begin = c.iterator();
		while(begin.hasNext())
			found = found && contains(begin.next());
		
		return found;
	}

	/**
	 * Returns true if the ArrayList contains no element. 
	 **/
	@Override
	public boolean isEmpty()
	{
		return size()==0;
	}

	/**
	 * Removes the specified element from the ArrayList.
	 * All duplicates of this element in the ArrayList, are removed. 
	 * @param e, element to delete from list.
	**/
	@Override
	public void remove(E e){
		while(contains(e)){
			setSize(size()-1);
			@SuppressWarnings("unchecked")
			E[] temp = (E[])new Object[size()];


			for(int i=0,j=0;i<elements.length;++i){
				if(elements[i] != e)
					temp[j++] = elements[i];
			}
			elements = temp;
		}
		
	}
	/**
	 * Removes all duplicates of ArrayList's elements that 
	 * are also contained in the specified collection. 
	 * @param c, elements in this collection will be deleted.   
	**/
	@Override
	public void removeAll(Collection<E> c){
		Iterator<E> begin = c.iterator();
		while(begin.hasNext())
			remove(begin.next());
	}
	/**
	 * Retains only the elements hashset that are contained in
	 * the specified collection. For satisfaying elements, 
	 * duplicates retains in the collection.
	 * @param c, collection to retain. 
	**/
	@Override
	public void retainAll(Collection<E> c){	
		Iterator<E> begin = c.iterator();
		while(begin.hasNext()){
			E temp = begin.next();
			if(!contains(temp))
				c.remove(temp);
		}
	}

	/**
	 * Returns the number of elements in ArrayList
	 *@return size of ArrayList. 
	**/
	public int size(){	
		return numberOfElements;
	}

	private void setSize(int s){
		numberOfElements = s;
	}	
}