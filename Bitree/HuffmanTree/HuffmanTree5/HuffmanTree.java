import java.util.*;
import java.io.*;

public class HuffmanTree implements HuffmanInterface{
	
	public String alphabet = "muckd!ap,.re ";
	public ArrayList<alphabits> symbols = new ArrayList<alphabits>();
	public alphabits[] letters = new alphabits[13];
	public BinaryTree<alphabits> root = null;
	public int age = 0;
	
	public static void main(String args[]){
		HuffmanTree temp = new HuffmanTree();
		temp.createTree("EEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEmud!ap.  r mkucd!ap,.reemk e");
		System.out.println(temp.encodeMessage("eEeEeE"));
	}
	
	public void createTree(String sampleText){
		for(int i = 0; i < sampleText.length(); i++){
			char inspect = Character.toLowerCase(sampleText.charAt(i));
			if(alphabet.indexOf(inspect) != -1){
				addToHuff(inspect);
			}
		}
		for(int i=0; i<symbols.size(); i++){
			letters[i] = symbols.get(i);
		} 
		buildTree(letters);
	}
	
	private int findInSymbols(char letter){
		int index = -1;
		for(int j=0; j < symbols.size(); j++){
			if(symbols.get(j).symbol.equals(letter)){
				return j;
			}
		}
		return index;
	}
	
	private void addToHuff(char letter){
		if(symbols.isEmpty())
			symbols.add(new alphabits(1, letter));
		else {
			if(findInSymbols(letter) != -1)
				symbols.get(findInSymbols(letter)).weight++;
			else
				symbols.add(new alphabits(1, letter));
		}
	}
	
	private void buildTree(alphabits[] symbols){
		Queue<BinaryTree<alphabits>> theQueue = new PriorityQueue<BinaryTree<alphabits>>(symbols.length, new CompareHuffmanTrees());
		for(alphabits nextSymbol : symbols){
			BinaryTree<alphabits> aBinaryTree = new BinaryTree<alphabits>(nextSymbol, null, null, age++);
			theQueue.offer(aBinaryTree);
		}
		while(theQueue.size() > 1){
			BinaryTree<alphabits> left = theQueue.poll();
			BinaryTree<alphabits> right = theQueue.poll();
			double wl = left.getData().weight;
			double wr = right.getData().weight;
			alphabits sum = new alphabits(wl + wr, null);
			BinaryTree<alphabits> newTree = new BinaryTree<alphabits>(sum, left, right, age++);
			theQueue.offer(newTree);
		}
		
		root = theQueue.poll();
	}
	
	private boolean in(BinaryTree<alphabits> root, char symbol){
		if(root.isLeaf()){
			if(root.getData().symbol.equals(symbol))
				return true;
			else
				return false;
		}
		else 
			return (in(root.getLeftSubtree(),symbol) || in(root.getRightSubtree(), symbol));
	}
	
	private String code(char symbol){
		BinaryTree<alphabits> currentTree = root;
		StringBuilder binary = new StringBuilder();
		while(!currentTree.isLeaf()){
			if(in(currentTree.getLeftSubtree(), symbol)){
				binary.append("0");
				currentTree = currentTree.getLeftSubtree();
			}
			else if(in(currentTree.getRightSubtree(), symbol)){
				binary.append("1");
				currentTree = currentTree.getRightSubtree();
			}
		}
		return binary.toString();
	}
	
	public String encodeMessage(String message){
		StringBuilder result = new StringBuilder();
		message = message.toLowerCase();
		for(int i=0; i < message.length(); i++){
			if(findInSymbols(message.charAt(i)) != -1){
				result.append(code(message.charAt(i)));
			}
		}
		return result.toString();
	}
	
	public String decodeMessage(String encodedMessage){
		StringBuilder result = new StringBuilder();
		BinaryTree<alphabits> currentTree = root;
		for(int i = 0; i < encodedMessage.length(); i++){
			if(encodedMessage.charAt(i) == '1')
				currentTree = currentTree.getRightSubtree();
			else
				currentTree = currentTree.getLeftSubtree();
			if(currentTree.isLeaf()){
				alphabits theData = currentTree.getData();
				result.append(theData.symbol);
				currentTree = root;
			}
		}
		return result.toString();
	}
	
	private static class alphabits implements Serializable {
	
		private double weight;
		public Character symbol;
		
		public alphabits(double weight, Character symbol){
			this.weight = weight;
			this.symbol = symbol;
		}
	}
	
	private static class CompareHuffmanTrees implements Comparator<BinaryTree<alphabits>> {
		
		public int compare(BinaryTree<alphabits> treeLeft, BinaryTree<alphabits> treeRight) {
			double wLeft = treeLeft.getData().weight;
			double wRight = treeRight.getData().weight;
			if(Double.compare(wLeft, wRight) == 0){
				if(treeLeft.isLeaf() && !treeRight.isLeaf())
					return -1;
				else if(!treeLeft.isLeaf() && treeRight.isLeaf())
					return 1;
				else if(treeLeft.isLeaf() && treeRight.isLeaf()){
					if(treeLeft.getData().symbol < treeRight.getData().symbol)
						return -1;
					else if(treeLeft.getData().symbol > treeRight.getData().symbol)
						return 1;
				}
				else if(!treeLeft.isLeaf() && !treeRight.isLeaf()){
					if(treeLeft.age < treeRight.age)
						return -1;
					else if (treeLeft.age > treeRight.age)
						return 1;
				}
			}
			return Double.compare(wLeft, wRight);
		}
		
	}

}
