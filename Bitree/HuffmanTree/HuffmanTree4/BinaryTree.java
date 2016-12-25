
import java.io.*;
import java.util.Scanner;

public class BinaryTree<E> {
	
	protected Node<E> root;
	protected int age;

	public BinaryTree(){
		root = null;
	}
	
	protected BinaryTree(Node<E> root){
		this.root = root;
	}
	
	public BinaryTree(E data, BinaryTree<E> leftTree, BinaryTree<E> rightTree, int age){
		this.age = age;
		root = new Node<E>(data);
		if(leftTree != null)
			root.left = leftTree.root;
		else
			root.left = null;
		if(rightTree != null)
			root.right = rightTree.root;
		else
			root.right = null;
	}
	
	public BinaryTree<E> getLeftSubtree(){
		if(root != null && root.left != null)
			return new BinaryTree<E>(root.left);
		else
			return null;
	}
	
	public BinaryTree<E> getRightSubtree(){
		if(root != null && root.right != null)
			return new BinaryTree<E>(root.right);
		else
			return null;
	}
	
	public E getData(){
		if(root != null)
			return root.data;
		else
			return null;
	}
	
	public boolean isLeaf(){
		return (root.left == null && root.right == null);
	}
	
	// Node
	/** Node class */
	protected class Node<E>{
		E data;
		Node<E> left = null;
		Node<E> right = null;
		
		public Node(E data, Node<E> L, Node<E> R){
			this.data = data;
			left = L;
			right = R;
		}
		
		public Node(E data){
			this.data = data;
		}
	}
}
