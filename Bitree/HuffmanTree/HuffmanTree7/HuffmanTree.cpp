#include<iostream>
#include<map>//映射 
#include<stack> //堆栈 
#include<string>//字符串
#include<cstring>
#include<list>//双向链表 
#include<cassert>// 断言 
#define MAX 27
//防止命名冲突 
using std::map; 
using std::stack; 
using std::list; 
using std::string;
using std::cout;
using std::endl;
//定义结点类的虚基类，用于叶子结点和内部结点的继承
class BinNode
{
public:
    virtual bool isleaf()=0;
    virtual int wit()=0;
    //virtual ~BinNode()//=0;
};
//定义叶子结点类
class LeafNode :public BinNode
{
private:
    int weight;//叶子结点的权重
    char value;//叶子结点对应的字符
public:
    LeafNode(int fre,char val)
	{
		weight=fre;
		value=val;
	};//叶子结点构造函数，频率为权重
    bool isleaf(){return true;};//叶子结点返回为真
    int wit(){return weight;};//返回权重
    char val(){return value;};//返回字符
};
//定义内部结点
class IntlNode:public BinNode
{
private:
    int weight;
    BinNode *left,*right;//左右指针
public:
    IntlNode(BinNode *l,BinNode *r)//由左右子树构造内部结点
    {
        weight=l->wit()+r->wit();
        left=l;
        right=r;
    };
    bool isleaf(){return false;};//内部结点返回为假
    int wit(){return weight;};//返回权重

    BinNode *lt(){return left;};//返回左结点
    void setleft(BinNode *l){left=(BinNode *)l;};//设置左结点,强制类型转换

    BinNode *rt(){return right;};
    void setright(BinNode *r){right=(BinNode *)r;};
};
//哈夫曼树类
class HuffTree
{
private:
    BinNode *root;
public:
    HuffTree(int fre,char val)//从一个叶子开始构造树
    {
        root=(BinNode *)new LeafNode(fre,val);
        assert(root); //返回失败，使用断言 
    };
    HuffTree(HuffTree *l,HuffTree *r)//由两棵树合并成一棵树
    {
        root=(BinNode *) new IntlNode(l->rot(),r->rot());
    };
    int wit()
	{
		return root->wit();
	};
    BinNode *rot(){return root;};
};

//使用后序遍历,根节点到到每个叶子结点的路径结点的编码(左0右1)
bool  traverse(BinNode *root,string prefix=" ")
{
	assert(root);  
    if(root->isleaf())
    {
        cout<<((LeafNode*)root)->val()<<prefix<<endl;
        return true;
    }
    else
    {
        traverse(((IntlNode*)root)->lt(),prefix+"0");
        traverse(((IntlNode*)root)->rt(),prefix+"1");
    }
}
//字符串解码，输入01字符串解码为字符，用string返回。 
string decode(BinNode* r,string encoded_str)
{
	string res = "";
    BinNode* node= r;
    for (int i = 0; i != encoded_str.size(); ++i)
    {
        if (encoded_str[i] == '0') 
          	r=((IntlNode*)r)->lt();
		else 
		{ 
           assert(encoded_str[i] == '1');
           r=((IntlNode*)r)->rt();
        }
        if (r->isleaf())
        {
            res += ((LeafNode*)r)->val();
            r = node;
        }
    }
    return res;
}
/*****一系列关于最小堆的操作*****/
//从1号开始建堆。 
 
//find the left child index
inline unsigned int Left(unsigned int i)
{
	return i<<1;
}
//find the right child index
inline unsigned int Right(unsigned int i)
{
	return ((i<<1)+1);
}
//find the parent index
inline unsigned int Parent(unsigned int i)
{
	return i>>1;
}
//交换 
void exchange(HuffTree* &a,HuffTree* &b)
{
	HuffTree* c=a;
	a=b;
	b=c;
}
//维护i位置的堆的性质
void Min_Heapify(HuffTree* A[],unsigned int i,unsigned int heap_size,const int A_length)
{
	unsigned int smallest=i,l,r;
	do
	{
		i=smallest;
		l=Left(smallest),r=Right(smallest);
		if(l<=heap_size&&A[smallest]->wit()>A[l]->wit())
			smallest=l;
		if(r<=heap_size&&A[smallest]->wit()>A[r]->wit())
			smallest=r;
	
		exchange(A[i],A[smallest]);
	}while(smallest!=i);
				
}
//建立最小值堆
 void Build_Min_Heap(HuffTree* A[], unsigned int heap_size,const int A_length)
{
	unsigned int i;
	for(i=heap_size/2;i>0;i--)
		{
			Min_Heapify(A,i,heap_size,A_length);
		 } 
}
//返回并移除堆中的最小值
HuffTree *Heap_Extract_Min(HuffTree* A[],int &heap_size)
{
 	assert(heap_size>0);//堆中元素个数大于0 
 	HuffTree *min=A[1];
	A[1]=A[heap_size--];
	Min_Heapify(A,1,heap_size,heap_size);
	return min; 
}
//插入元素到堆中，保持最小值堆的性质
void Heap_Insert(HuffTree* A[],HuffTree* &x,int &heap_size,int A_length)
{
	assert(heap_size<A_length);//堆中元素个数小于数组最大元素个数
	A[++heap_size]=x;
	unsigned int son=heap_size;
	while(son>1&&(A[Parent(son)]->wit())>(A[son]->wit()))
	{
		exchange(A[son],A[Parent(son)]); 
		son=Parent(son);
	}
} 
//用用最小值堆建立霍夫曼树 
HuffTree *BuildHuffTree(HuffTree *initree[],int& heap_size,int A_length )
{
	Build_Min_Heap(initree,heap_size,A_length);
	HuffTree *temp1=NULL;
	HuffTree *temp2=NULL;
	HuffTree *temp3=NULL;
	while(heap_size>1)
	{
		temp1=Heap_Extract_Min(initree,heap_size);
		
		temp2=Heap_Extract_Min(initree,heap_size);
	
		temp3= new HuffTree(temp1,temp2);
	
		Heap_Insert(initree,temp3,heap_size,A_length);	
		delete temp1;
		delete temp2;
	}
	return temp3;
}
int main()
{
	string ready_str="AADATARAEFRTAAFTER";//待编码串 
	string encode_str="001000111010101011110";//待解码串 
	int i,heap_size,j=0,A_length=MAX;
	int fre[MAX];//频率表 
	memset(fre,0,MAX*sizeof(int));//初始每个字符频率为0 
	HuffTree *initree1[MAX]; 
   //哈希函数 ,扫描字符串，得到每个字符的频率 
	for(i=0;i<ready_str.size();i++)
		fre[ready_str[i]-'A'+1]++;
	//指针数组建立每棵树 
    for(i=1;i<MAX;i++)
   	{
   		if(fre[i]) 
		   {
		   	initree1[++j] = new HuffTree(fre[i],i+'A'-1);
		   }
	 }
	heap_size=j;  
    //建树返回根节点 
      BinNode *r=(BuildHuffTree(initree1,heap_size,A_length))->rot();
      cout<<"编码:"<<endl; 
      traverse(r);//输出每个字符的编码 
	  cout<<"解码:"<<endl;
      cout<<decode(r,encode_str);
      delete r;//！！！释放 
      return  0;
}
/*bool BuildHuffTree(list<HuffTree> &tr)
{
    if(tr.empty()) return false;
    list<HuffTree>::iterator  it;

    while(tr.size()>1)
    {
        it=tr.begin();
        HuffTree temp1=*it++;
        HuffTree temp2=*it++;
        HuffTree  temp(&temp1,&temp2);
        tr.pop_front();
        tr.pop_front();
        while(it!=tr.end()&&temp.wit()>(*it).wit())
            it++;
	    tr.insert(it,temp);
    }
    return true;
}*/ 
/*//1递归方法
void Min_Heapify001(HuffTree* A[],unsigned int i,int heap_size,int A_length)
{
	int smallest=i,r=Right(i),l=Left(i);
	if(l<=heap_size&&(A[i]->wit())>=(A[l]->wit()))
		smallest=l;
	if(r<=heap_size&&(A[i]->wit())>=(A[r]->wit()))
		smallest=r;
		
	if(smallest!=i)
	{
		exchange(A[i],A[smallest]);
		Min_Heapify001(A,smallest,heap_size,A_length);
	}
} */
/*int main()
{
	string encode_str="001000111010101011110";
   	string ready_str="AADATARAEFRTAAFTER";
	int fre[MAX];
	memset(fre,0,MAX*sizeof(int));
   	list<HuffTree> tr;
	HuffTree *initree[MAX]; 
	int i,k,j=0;
	int A_length=MAX,heap_size;
	//用大小为26的数组来统计，通过数组下标和字符A，B，C的哈希函数 
   //只需要扫描一遍字符串，可以将时间复杂度降低到O(n) 
	for(i=0;i<ready_str.size();i++)
		fre[ready_str[i]-'A']++;
    for(i=0;i<MAX;i++)
   	{
   		if(fre[i]) 
		   {
		   	initree[j] = new HuffTree(fre[i],i+'A');
		   	++j;
		   }
	 }
	 heap_size=j;
	 
	 	 //插入排序，可用堆排序代替 
	for(i=1;i<j;i++)
		{
			HuffTree *temp=initree[i];
			k=i;
			while(k>0&&temp->wit()<initree[k-1]->wit())
				{
					initree[k]=initree[k-1];
					k--;
				} 
			initree[k]=temp;
		 }
	for(i=0;i<j;i++)
		tr.push_back(*initree[i]);
    //数组必须有默认构造函数，没法用数组建立对象，只有用变量
  	//在网上找了一下，可以用指针数组代替，但是要记得释放空间 
    if(BuildHuffTree(tr))//建树 
    {
      BinNode *r=(tr.front()).rot();
      cout<<"编码:"<<endl; 
      traverse(r);//输出每个字符的编码 
	  cout<<"解码:"<<endl;
      cout<<decode(r,encode_str);
    }
    for(i=0;i<j;i++)
   		 delete  A[i] ;
    return  0;
}*/
//递归方法 
/*
void traverse(BinNode *root,string prefix)
{
    if(root->isleaf())
    {
        cout<<((LeafNode*)root)->val()<<endl;
       // cout<<1;
        return;
    }
    else
    {
        //cout<<((IntlNode*)root)->wit()<<endl;
        traverse(((IntlNode*)root)->lt(),prefix+"0");
      //  cout<<0;
        traverse(((IntlNode*)root)->rt(),prefix+"1");
        //cout<<1;
    }*/
    
/*//树的遍历
void traverse01(BinNode *root)
{
	stack<BinNode *> pos;
	vector<int > code;
	vector<int >::iterator it;
	pos.push(root);
	while(!pos.empty())
	{
		while(!root->isleaf())
		{
			pos.push(root);
			code.push_back(0);
			root=((IntlNode*)root)->lt();
		}
		//输出每个节点及其编码 
		cout<<((LeafNode*)root)->val()<<": ";
		for(it=code.begin();it!=code.end();it++)
			cout<<*it;
		cout<<endl;
		if(((LeafNode*)root)->val()=='E') 
		{
			code.pop_back();
			code.pop_back();
		}
		//弹栈 
		root=pos.top();
		pos.pop();
		code.pop_back();
		root=((IntlNode*)root)->rt();
		code.push_back(1);
	}
}*/ 
