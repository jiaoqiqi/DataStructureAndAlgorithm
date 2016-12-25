
import java.util.*;

public class KWPriorityQueue<E> extends AbstractQueue<E> implements Queue<E>{

	// Data Fields
	/** the ArrayList to hold the data */
	private ArrayList<E> theData;
	/** An optional reference to a Comparator object. */
	Comparator<E> comparator = null;
	
	// Methods
	/** constructors */
	public KWPriorityQueue(){
		theData = new ArrayList<E>();
	}
	/** Creates a heap-based priority queue wit the specified initial capacity that orders its elements according to the 
	 * specified comparator.
	 * @param comp
	 */
	public KWPriorityQueue(int cap, Comparator<E> comp){
		if(cap < 1)
			throw new IllegalArgumentException();
		theData = new ArrayList<E>();
		comparator = comp;
	}
	
	public E element() {
		return null;
	}
	
	public void swap(int parent, int child){
		E pitem = theData.get(parent);
		E citem = theData.get(child);
		theData.set(parent, citem);
		theData.set(child, pitem);
	}
	
	@SuppressWarnings("unchecked")
	public int compare(E left, E right){
		if(comparator != null){
			return comparator.compare(left, right);
		} else {
			return ((Comparable<E>) left).compareTo(right);
		}
	}
	
	/** Insert an item into the priority queue.
	 * pre: The ArrayList theData is in heap order
	 * post: the item is in the priority queue and theData is in heap order
	 * @param item - the item to be inserted
	 * @throws NullPointerException - if the item to tbe inserted is null
	 */
	public boolean offer(E item) {
		theData.add(item);	// Add the item to the heap
		int child = theData.size() - 1;		// child is newly inserted item
		int parent = (child - 1)/2;		// find the child's parent
		while(parent >= 0 && compare(theData.get(parent), theData.get(child)) > 0){
			swap(parent, child);
			child = parent;
			parent = (child - 1) / 2;
		}
		return true;
	}

	public E peek() {
		return null;
	}
	
	/** Remove an item for the priority queue
	 * pre: the ArrayList theData is in heap order
	 * post: removed smallest item, theData is in heap order
	 * @return the item with the smallest priority value or null if empty
	 */
	public E poll() {
		if(isEmpty()){
			return null;
		}
		E result = theData.get(0); 	// Save the top of the heap
		if(theData.size() == 1){	// if only one item...
			theData.remove(0);			// remove it
			return result;
		}
		
		/* Remove the last item from the ArrayList and place it into the first position */
		theData.set(0, theData.remove(theData.size() - 1));
		int parent = 0;		// parent starts at top
		while(true){
			int leftChild = 2 * parent + 1;
			if(leftChild >= theData.size()){
				break;	// out of heap
			}
			int rightChild = leftChild + 1;
			int minChild = leftChild;	// assume leftChild is smaller
			if(rightChild < theData.size() && compare(theData.get(leftChild), theData.get(rightChild)) > 0) {
														// see whether rightChild is smaller
				minChild = rightChild;
			}
			// assert: minChild is the index of the smaller child -- move smaller child up the heap if necessary
			if(compare(theData.get(parent), theData.get(minChild)) > 0 ){
				swap(parent, minChild);
				parent = minChild;
			} else {	// heap property is restored
				break;
			}
		}
		return result;
	}

	public E remove() {
		return null;
	}
	
	public boolean isEmpty(){
		return (size() == 0);
	}

	public Iterator<E> iterator() {
		return theData.iterator();
	}

	public int size() {
		return theData.size();
	}

}
