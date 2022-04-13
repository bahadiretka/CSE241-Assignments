/** 
 * Represents the Iterator class.
 * @see Collection  
 * @param E object-type to hold in set.
 * @author Bahadir Etka Kilinc
 * @version 1.0
 * @since 2021-01-25
*/
public class Iterator<E>{
	private E[][] buffer; // underlying buffer.
	private int index; // location of iterator in buffer.
	private E lastElement; // last element returned by this iterator.
	private Collection<E> obj = null;
	
	public Iterator(E[][] arr,Collection<E> temp){
		buffer = arr;
		index = 0;
		obj = temp;
	}

	/** 
	 * Returns true if the iteration has more elements.
	 * @return true if iteration has more elements.
	*/
	public boolean hasNext(){
		return index<buffer[0].length;
	}

	/**
	 * Returns the next element in the iteration and advances the
 	 * iterator.
 	 * @return E, the next element in the iteration.
 	*/
	public E next(){
		lastElement = buffer[0][index++];
		return lastElement;
	}
	
	/**
	 * Removes from the underlying collection the last element returned
	 * by this iterator. This method does not work for Queues, it throws
	 * an exception.
	 * @exception notQueue, throws if the coming object is Queue.
	*/

	@SuppressWarnings("unchecked")
	public void remove() throws notQueue{
		
		if(obj instanceof Queue) throw new notQueue();
		E[] newArr = (E[]) new Object[buffer[0].length -1];

		for(int i=0, k=0;i<newArr.length;++i){

			if(lastElement == buffer[0][i])
				continue;
			
			newArr[k++] = buffer[0][i];
		}

		//change the real reference to new array.
		buffer[0] = newArr; 
	}
	


}


