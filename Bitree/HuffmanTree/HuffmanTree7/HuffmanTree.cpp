#include<iostream>
#include<map>//ӳ�� 
#include<stack> //��ջ 
#include<string>//�ַ���
#include<cstring>
#include<list>//˫������ 
#include<cassert>// ���� 
#define MAX 27
//��ֹ������ͻ 
using std::map; 
using std::stack; 
using std::list; 
using std::string;
using std::cout;
using std::endl;
//�������������࣬����Ҷ�ӽ����ڲ����ļ̳�
class BinNode
{
public:
    virtual bool isleaf()=0;
    virtual int wit()=0;
    //virtual ~BinNode()//=0;
};
//����Ҷ�ӽ����
class LeafNode :public BinNode
{
private:
    int weight;//Ҷ�ӽ���Ȩ��
    char value;//Ҷ�ӽ���Ӧ���ַ�
public:
    LeafNode(int fre,char val)
	{
		weight=fre;
		value=val;
	};//Ҷ�ӽ�㹹�캯����Ƶ��ΪȨ��
    bool isleaf(){return true;};//Ҷ�ӽ�㷵��Ϊ��
    int wit(){return weight;};//����Ȩ��
    char val(){return value;};//�����ַ�
};
//�����ڲ����
class IntlNode:public BinNode
{
private:
    int weight;
    BinNode *left,*right;//����ָ��
public:
    IntlNode(BinNode *l,BinNode *r)//���������������ڲ����
    {
        weight=l->wit()+r->wit();
        left=l;
        right=r;
    };
    bool isleaf(){return false;};//�ڲ���㷵��Ϊ��
    int wit(){return weight;};//����Ȩ��

    BinNode *lt(){return left;};//��������
    void setleft(BinNode *l){left=(BinNode *)l;};//��������,ǿ������ת��

    BinNode *rt(){return right;};
    void setright(BinNode *r){right=(BinNode *)r;};
};
//����������
class HuffTree
{
private:
    BinNode *root;
public:
    HuffTree(int fre,char val)//��һ��Ҷ�ӿ�ʼ������
    {
        root=(BinNode *)new LeafNode(fre,val);
        assert(root); //����ʧ�ܣ�ʹ�ö��� 
    };
    HuffTree(HuffTree *l,HuffTree *r)//���������ϲ���һ����
    {
        root=(BinNode *) new IntlNode(l->rot(),r->rot());
    };
    int wit()
	{
		return root->wit();
	};
    BinNode *rot(){return root;};
};

//ʹ�ú������,���ڵ㵽��ÿ��Ҷ�ӽ���·�����ı���(��0��1)
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
//�ַ������룬����01�ַ�������Ϊ�ַ�����string���ء� 
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
/*****һϵ�й�����С�ѵĲ���*****/
//��1�ſ�ʼ���ѡ� 
 
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
//���� 
void exchange(HuffTree* &a,HuffTree* &b)
{
	HuffTree* c=a;
	a=b;
	b=c;
}
//ά��iλ�õĶѵ�����
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
//������Сֵ��
 void Build_Min_Heap(HuffTree* A[], unsigned int heap_size,const int A_length)
{
	unsigned int i;
	for(i=heap_size/2;i>0;i--)
		{
			Min_Heapify(A,i,heap_size,A_length);
		 } 
}
//���ز��Ƴ����е���Сֵ
HuffTree *Heap_Extract_Min(HuffTree* A[],int &heap_size)
{
 	assert(heap_size>0);//����Ԫ�ظ�������0 
 	HuffTree *min=A[1];
	A[1]=A[heap_size--];
	Min_Heapify(A,1,heap_size,heap_size);
	return min; 
}
//����Ԫ�ص����У�������Сֵ�ѵ�����
void Heap_Insert(HuffTree* A[],HuffTree* &x,int &heap_size,int A_length)
{
	assert(heap_size<A_length);//����Ԫ�ظ���С���������Ԫ�ظ���
	A[++heap_size]=x;
	unsigned int son=heap_size;
	while(son>1&&(A[Parent(son)]->wit())>(A[son]->wit()))
	{
		exchange(A[son],A[Parent(son)]); 
		son=Parent(son);
	}
} 
//������Сֵ�ѽ����������� 
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
	string ready_str="AADATARAEFRTAAFTER";//�����봮 
	string encode_str="001000111010101011110";//�����봮 
	int i,heap_size,j=0,A_length=MAX;
	int fre[MAX];//Ƶ�ʱ� 
	memset(fre,0,MAX*sizeof(int));//��ʼÿ���ַ�Ƶ��Ϊ0 
	HuffTree *initree1[MAX]; 
   //��ϣ���� ,ɨ���ַ������õ�ÿ���ַ���Ƶ�� 
	for(i=0;i<ready_str.size();i++)
		fre[ready_str[i]-'A'+1]++;
	//ָ�����齨��ÿ���� 
    for(i=1;i<MAX;i++)
   	{
   		if(fre[i]) 
		   {
		   	initree1[++j] = new HuffTree(fre[i],i+'A'-1);
		   }
	 }
	heap_size=j;  
    //�������ظ��ڵ� 
      BinNode *r=(BuildHuffTree(initree1,heap_size,A_length))->rot();
      cout<<"����:"<<endl; 
      traverse(r);//���ÿ���ַ��ı��� 
	  cout<<"����:"<<endl;
      cout<<decode(r,encode_str);
      delete r;//�������ͷ� 
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
/*//1�ݹ鷽��
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
	//�ô�СΪ26��������ͳ�ƣ�ͨ�������±���ַ�A��B��C�Ĺ�ϣ���� 
   //ֻ��Ҫɨ��һ���ַ��������Խ�ʱ�临�ӶȽ��͵�O(n) 
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
	 
	 	 //�������򣬿��ö�������� 
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
    //���������Ĭ�Ϲ��캯����û�������齨������ֻ���ñ���
  	//����������һ�£�������ָ��������棬����Ҫ�ǵ��ͷſռ� 
    if(BuildHuffTree(tr))//���� 
    {
      BinNode *r=(tr.front()).rot();
      cout<<"����:"<<endl; 
      traverse(r);//���ÿ���ַ��ı��� 
	  cout<<"����:"<<endl;
      cout<<decode(r,encode_str);
    }
    for(i=0;i<j;i++)
   		 delete  A[i] ;
    return  0;
}*/
//�ݹ鷽�� 
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
    
/*//���ı���
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
		//���ÿ���ڵ㼰����� 
		cout<<((LeafNode*)root)->val()<<": ";
		for(it=code.begin();it!=code.end();it++)
			cout<<*it;
		cout<<endl;
		if(((LeafNode*)root)->val()=='E') 
		{
			code.pop_back();
			code.pop_back();
		}
		//��ջ 
		root=pos.top();
		pos.pop();
		code.pop_back();
		root=((IntlNode*)root)->rt();
		code.push_back(1);
	}
}*/ 
