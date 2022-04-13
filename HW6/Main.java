
public class Main{

	public static void main(String[] args){

		HashSet<Integer> hashset = new HashSet<Integer>();
		ArrayList<Integer> arraylist = new ArrayList<Integer>();
		LinkedList<Integer> linkedlist = new LinkedList<Integer>();

		hashset.add(5);
		hashset.add(6);
		hashset.add(7);
		hashset.add(8);
		hashset.add(9);
		hashset.add(10);
		hashset.add(11);
		hashset.add(11); // won't add
		hashset.add(9); // won't add

		System.out.println("\t\t## Hashset ##");
		Iterator<Integer> begin = hashset.iterator();
		while(begin.hasNext()){
			System.out.printf("%s ", begin.next());
		}

		if(hashset.contains(5))
			System.out.println("\nHashset contains 5!");

		hashset.remove(7);
		hashset.remove(8);

		System.out.println("\t\t## 7 and 8 removed from Hashset ##");
		begin = hashset.iterator();
		while(begin.hasNext()){
			System.out.printf("%s ", begin.next());
		}

		arraylist.add(3);
		arraylist.add(6);
		arraylist.add(3);
		arraylist.add(6);
		arraylist.add(6);
		arraylist.add(3);
		arraylist.add(11);
		arraylist.add(11);

		System.out.println("\n\t\t## ArrayList ##");
		begin = arraylist.iterator();
		while(begin.hasNext()){
			System.out.printf("%s ", begin.next());
		}

		hashset.addAll(arraylist);
		begin = hashset.iterator();
		System.out.println("\n\t\t## ArrayList added into Hashset ##");
		while(begin.hasNext()){
			System.out.printf("%s ", begin.next());
		}

		if(hashset.containsAll(arraylist))
			System.out.println("\n\t\t## Hashset contains ArrayList! ##");

		arraylist.add(12);
		arraylist.add(13);
		arraylist.add(14);
		arraylist.add(15);

		System.out.println("\t\t## Updated ArrayList ##");
		begin = arraylist.iterator();
		while(begin.hasNext()){
			System.out.printf("%s ", begin.next());
		}

		hashset.retainAll(arraylist);
		System.out.println("\n\t\t## ArrayList retained from HashSet ##");
		begin = arraylist.iterator();
		while(begin.hasNext()){
			System.out.printf("%s ", begin.next());
		}

		hashset.removeAll(arraylist);
		begin = hashset.iterator();
		System.out.println("\n\t\t## ArrayList removed from Hashset ##");
		while(begin.hasNext()){
			System.out.printf("%s ", begin.next());
		}

		linkedlist.add(4);
		linkedlist.add(3);
		linkedlist.add(2);
		linkedlist.add(1);
		linkedlist.add(0);

		begin = linkedlist.iterator();
		System.out.println("\n\t\t## LinkedList ##");
		while(begin.hasNext()){
			System.out.printf("%s ", begin.next());
		}

		linkedlist.addAll(arraylist);
		System.out.println("\n\t\t## ArrayList added into LinkedList ##");
		begin = linkedlist.iterator();
		while(begin.hasNext()){
			System.out.printf("%s ", begin.next());
		}

		HashSet<String> str_hashset = new HashSet<String>();
		ArrayList<String> str_arraylist = new ArrayList<String>();
		LinkedList<String> str_linkedlist = new LinkedList<String>();

		str_hashset.add("One");
		str_hashset.add("Two");
		str_hashset.add("Three");
		str_hashset.add("Four");
		str_hashset.add("One");
		str_hashset.add("Two");

		str_arraylist.addAll(str_hashset);
		str_linkedlist.addAll(str_hashset);

		str_arraylist.add("Five");
		str_arraylist.add("Six");
		str_arraylist.add("Two");
		str_arraylist.add("Two");

		str_linkedlist.add("Five");
		str_linkedlist.add("Six");

		System.out.println("\n\t\t## String Hashset ##");
		Iterator<String> str_begin = str_hashset.iterator();
		while(str_begin.hasNext()){
			System.out.printf("%s ", str_begin.next());
		}
		System.out.println("\n\t\t## String ArrayList ##");
		str_begin = str_arraylist.iterator();
		while(str_begin.hasNext()){
			System.out.printf("%s ", str_begin.next());
		}
		System.out.println("\n\t\t## String LinkedList ##");
		str_begin = str_linkedlist.iterator();
		while(str_begin.hasNext()){
			System.out.printf("%s ", str_begin.next());
		}

		if(str_linkedlist.contains("Five"))
			System.out.println("\n\nLinkedList contains 'Five'");

		System.out.println("Size of ArrayList: " + str_arraylist.size());

		if(!str_hashset.isEmpty())
			System.out.println("Hashset is not empty!");

		str_hashset.clear();
		System.out.println("Clearing the Hashset!");
		if(str_hashset.isEmpty())
			System.out.println("Hashset is empty!");

		System.out.println("\n\nTest for try to remove element from LinkedList(inherites from Queue)");
		LinkedList<Integer> tempList = new LinkedList<Integer>();
		tempList.add(10);
		tempList.add(20);
		tempList.add(30);

		Iterator<Integer> iter = tempList.iterator();
		try{
			int num;
			while(iter.hasNext()){
				num = iter.next();
				iter.remove();
			}
		}
		catch(Exception e){
			System.out.println(e);
		}

		
	} 	

}