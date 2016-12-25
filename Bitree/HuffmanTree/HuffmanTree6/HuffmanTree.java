import java.io.File;
import java.io.FileNotFoundException;
import java.util.HashMap;
import java.util.Map;
import java.util.PriorityQueue;
import java.util.Scanner;
import java.util.Stack;
import java.util.TreeMap;

class Node
{
public int iData;              
public char dData;           
public Node leftChild;         
public Node rightChild;        

public void displayNode()      
   {
   System.out.print('{');
   System.out.print(iData);
   System.out.print(", ");
   System.out.print(dData);
   System.out.print("} ");
   }
}

class Tree implements Comparable<Tree>
{
	private Node root;             
	public Tree(char data,int frequency)                  
	{ 
		root = new Node();
		root.iData = frequency;
		root.dData = data;
    } 
 
	public Tree(Tree leftChild,Tree rightChild)
	{
		root = new Node();
		root.leftChild = leftChild.root;
		root.rightChild = rightChild.root;
		root.iData=leftChild.root.iData +
				rightChild.root.iData;
	}
  
	protected Tree(Node root)
	{
		this.root = root;
    }
	
	public Tree getLeftTree()
	{
		if(root!=null)
			return new Tree(root.leftChild);
		else
			return null;
	}

	public Tree getRightTree()
	{
		if(root!= null)
			return new Tree(root.rightChild);
		else 
			return null;
	}

	public char getRootChar()
	{
		if(root!= null)
			return root.dData;
		else return'\0';
	}

	
	public void displayTree()
	{
		Stack<Node> globalStack = new Stack<Node>();
		globalStack.push(root);
		int nBlanks = 32;
		boolean isRowEmpty = false;
		System.out.println(
				"......................................................");
		while(isRowEmpty==false)
		{
			Stack<Node> localStack = new Stack<Node>();
			isRowEmpty = true;	
			for(int j=0; j<nBlanks; j++)
				System.out.print(' ');
			while(globalStack.isEmpty()==false)
			{
				Node temp = (Node)globalStack.pop();
				if(temp != null)
				{ 
					if(temp.dData=='\0')
					{ 
						System.out.print("\\0");
					}
					else if (temp.dData == ' ')
					{ 
						System.out.print("sp");
					}
					else if(temp.dData ==' ')
					{
						System.out.print("if"); 
					}
					else
					{
						System.out.print(""+temp.dData);
					}
					localStack.push(temp.leftChild);
					localStack.push(temp.rightChild);
					if(temp.leftChild!= null||temp.rightChild!=null)
						isRowEmpty = false;
				}
				else 
				{ 
					System.out.print("--"); 
					localStack.push(null);
					localStack.push(null);
				}
           
				for(int j=0; j<nBlanks*2-2; j++)
					System.out.print(' ');
			}  
			System.out.println();
			nBlanks /= 2;
			while(localStack.isEmpty()==false)
				globalStack.push( localStack.pop() );
		}  
		System.out.println(
				"......................................................");
	}  // end displayTree()
 
	@Override
	public int compareTo(Tree tree) {
		Integer freq1 = new Integer(this.root.iData);
		Integer freq2 = new Integer(tree.root.iData);
		return freq1.compareTo(freq2);
	}
   
  
}  // end class Tree


public class n00757541 {
	
	Tree tree;
    TreeMap<Character,String> codeTable;
    protected HashMap<Character, Integer> calculateFrequency(String message)
    {
    	int messageLen = message.length();
	    char ch;
	    int count;
	    HashMap<Character, Integer> charCounts = new HashMap<Character, Integer>();
	    for(int i = 0; i<messageLen;++i)
	    {
	    	ch = message.charAt(i);
	    	if(ch < 'A' || ch > 'G') continue;
	    	if(charCounts.containsKey(ch))
	    	{
	    		count = charCounts.get(ch);
	    		++count;
	    		charCounts.put(ch,count);
	    	}
	    	else
	    	{ 
	    		charCounts.put(ch,1);
	        }
	        
	    }
	    return charCounts;
    }
     
    protected void createn00757541Tree(String message)
    {
    	HashMap<Character, Integer> charCounts = calculateFrequency(message);
    	PriorityQueue<Tree> trees = new PriorityQueue<Tree>();
    	Tree temp;
    	for(Map.Entry<Character, Integer> e : charCounts.entrySet())
    	{
    		temp = new Tree(e.getKey(),e.getValue());
    		trees.add(temp);
    	}
       
    	while(trees.size()>1)
    	{
    		temp = new Tree(trees.remove(),trees.remove());
    		trees.add(temp);
    	}	
    
    	tree = trees.remove();
     }
  
    public void displayn00757541Tree()
    {
    	if(tree!=null)
    		tree.displayTree();
    	else
    		System.out.println("Tree not created. Use method  CreateCodeTable first");
    }
    
    public void createCodeTable(String message)
    {
    	createn00757541Tree(message);
    	codeTable=new TreeMap<Character,String>();
    	createCodeTable(tree,"");
    }
   
    protected void createCodeTable(Tree tree, String code)
    { 
    	if(tree==null)
    	{ 
    		return;
    	}
    	char c = tree.getRootChar();
    	if(c!='\0')
    	{
    		if(c >='A' && c <= 'G')
    			codeTable.put(c,code);
    	}  
    
    	else
    	{
    		createCodeTable(tree.getLeftTree(),code + "0");
    		createCodeTable(tree.getRightTree(),code + "1");
    	}
    }
      
    public void displayCodeTable()
    {
    	System.out.println("Character Code");
       
    	for(Map.Entry<Character,String> entry : codeTable.entrySet())
    	{
    		char key = entry.getKey();
    		if (key == ' ')
    		{
    			System.out.println("sp : " + entry.getValue());
    		}
    		else if (key == ' ')
    		{ 
    			System.out.println("if" + entry.getValue());
    		}
    		else
    		{ 
    			System.out.println(key + " : " + entry.getValue());
    		}
    	}
    }
    
    public void displayAGCodeTable()
    {
    	System.out.println("Character Code");
       
    	for(Map.Entry<Character,String> entry : codeTable.entrySet())
    	{
    		char key = entry.getKey();
    		if (key >= 'A' && key <='G')
    		{
    			System.out.println(key + " : " + entry.getValue());
    		}
    	}
    }
   
  public String encodeMessage(String message)
  {
	  if (codeTable == null)
	  { 
		  System.out.println("No code table created.");
		  return"";
	  }
	  String codedMessage = "";
	  for(int i = 0;i<message.length();++i)
	  {
		  char c = message.charAt(i);
		  codedMessage += codeTable.get(c);
	  }
    
	  return codedMessage;
  }
  
  public String encodeAGMessage(String message)
  {
	  if (codeTable == null)
	  { 
		  System.out.println("No code table created.");
		  return "";
	  }
	  int i,len = message.length();
	  String codedMessage = "";
	  for(i = 0;i<len;++i)
	  {
		  char c = message.charAt(i);
		  if(c >='A' && c <= 'G'){ 
			  codedMessage += codeTable.get(c);
		  }
	  }
      len = codedMessage.length();
	  for(i=0;i<len;i++){
		  System.out.print(codedMessage.charAt(i));
		  if((i+1) % 24 == 0) System.out.println();//New line after 3 bytes
		  else if((i+1) % 8 == 0) System.out.print(" ");//Space between each byte
	  }
	  System.out.println();
	  
	  return codedMessage;
  }
   
  public String decodeMessage(String codedMessage)
  {
	  String decodedMessage = "";
	  Tree temp = tree;
    
	  for(int i = 0; i<codedMessage.length();++i)
	  {
		  if (codedMessage.charAt(i) == '0')
		  {
			  temp = temp.getLeftTree();
		  }
		  else
		  {
			  temp = temp.getRightTree();
		  }
		  if(temp.getRootChar() !='\0')
		  {
			  decodedMessage += temp.getRootChar();
			  temp= tree;
		  }
	  }
      return decodedMessage;
  }

	private static void displayMenu(){
		System.out.println(" choose from below: ");
		System.out.println("a. Create the Huffman Tree");
		System.out.println("b. Display the code table");
		System.out.println("c. Display binary encoding of the file");
		System.out.println("d. Display the decoded message");
		System.out.println("e. Exit");
	}
	public  static void main(String args[]) throws FileNotFoundException
	{ 
		 Scanner in = new Scanner(System.in);
		 String input,codedMessage = null,message = "";
		 n00757541 code = new n00757541();
		 System.out.print(" Enter the File Name : ");
		 //String fileName = in.next();
		 //File file = new File(fileName);
       File file;
       if(args.length > 0) {
       file = new File(args[0]);
		 Scanner sc = new Scanner(file);
		 char choice='a';
		 while(choice != 'e'){
			 displayMenu();
			 choice = in.next().charAt(0);
			 switch(choice){
			 	case 'a': //System.out.println ("Enter a message to encode. Type --- on a new line to end the message.");
			 		 input= sc.nextLine();
					 while (sc.hasNextLine())
					 {
						 message += input+"";
						 input = sc.nextLine();
					 }
					 code.createCodeTable(message);
					 System.out.println("The tree created:");
                code.displayn00757541Tree();
					 break;
			 	case 'b': code.displayAGCodeTable();
			 	 	 break;
			 	case 'c': codedMessage = code.encodeAGMessage(message);
			 	
				 	 break;
			 	case 'd': System.out.println("the coded message decoded:");
			 	 	 System.out.println(code.decodeMessage(codedMessage));
			 	 	 break;
			 	case 'e': break;	 
			 	 default: System.out.println("Invalid choice! Please select (a-d)");
			 	 	 break;
			 }
		 }
	 
		 sc.close();
       }
		 in.close();
	}
}
