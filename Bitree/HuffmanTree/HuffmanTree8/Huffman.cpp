//-------------哈弗曼树的建立-------------- 
#include<iostream>
using namespace std;
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

typedef char ElemType;
typedef struct
{
	 ElemType elem;
	 unsigned int weight;
	 unsigned int parent,lchild,rchild,tag;
}HTNode,*HuffmanTree;
typedef char** HuffmanCode;

typedef int Status; 
typedef struct weight
{
  char elem; 
  unsigned int m_weight; 
}Weight; // 保存符号信息; 

void Select(HuffmanTree HT,int n,int &s1,int &s2) 
{ 
	  int i; 
	  s1=s2=0; 
	  for(i=1;i<=n;i++)
	  { 
	    if(HT[i].weight<HT[s2].weight&&HT[i].parent==0&&s2!=0)
		{ 
		      if(HT[i].weight<HT[s1].weight)  
			  { 
		     		s2=s1;    
					s1=i; 
			  } 
		      else 
			  s2=i; 
	    } 
	    if((s1==0||s2==0)&&HT[i].parent==0)
		{ 
		      if(s1==0) s1=i; 
		      else 
			  if(s2==0)  
			  { 
		        if(HT[i].weight<HT[s1].weight)  
			    {
		             s2=s1; 
					 s1=i; 
			    } 
		        else 
			         s2=i;
	
	          } // end of else if 
	          if(s1>s2) {i=s1; s1=s2; s2=i;} 
	    } // end of if 
	  }// end of for 
 
} 

void HuffmanCoding(HuffmanTree &HT, HuffmanCode &HC, Weight* &w, int n)
 {
  // w存放n个字符的权值(均>0)，构造哈夫曼树HT，
  // 并求出n个字符的哈夫曼编码HC
  //本函数实现选择方式：从左往右选择两个小权值结点，结点信息在前面的为左子树，其后为右子树
//修改选择方式：依序选择两个小权值结点，权值小的为左子树。！！

  int i, j, m, s1,s2;
  char *cd;
  int p;
  int cdlen;

  if (n<=1) return;
  m = 2 * n - 1;
  HT = (HuffmanTree)malloc((m+1) * sizeof(HTNode));   // 0号单元未用
  for (i=1; i<=n; i++)
   { //初始化
	    HT[i].elem=w[i-1].elem;
	    HT[i].weight=w[i-1].m_weight;
	    HT[i].parent=0;
	    HT[i].lchild=0;
	    HT[i].rchild=0;
  }
  for (i=n+1; i<=m; i++)
   { //初始化
	    HT[i].weight=0;
	    HT[i].parent=0;
	    HT[i].lchild=0;
	    HT[i].rchild=0;
  }
	  printf("\n哈夫曼树的构造过程如下所示：\n");
	  printf("HT初态:\n  结点  weight  parent  lchild  rchild");
	  for (i=1; i<=m; i++)
	     printf("\n%4d%8d%8d%8d%8d",i,HT[i].weight,HT[i].parent,HT[i].lchild, HT[i].rchild);
	  printf("    按任意键，继续 ...");
	      getchar();
  for (i=n+1; i<=m; i++)
   {     // 建哈夫曼树
    // 在HT[1..i-1]中选择parent为0且weight最小的两个结点，
    // 其序号分别为s1和s2。
    Select(HT, i-1, s1, s2);
    HT[s1].parent = i;  HT[s2].parent = i;
    HT[i].lchild = s1;  HT[i].rchild = s2;
    HT[i].weight = HT[s1].weight + HT[s2].weight;
    printf("\nselect: s1=%d   s2=%d\n", s1, s2);
    printf("  结点  weight  parent  lchild  rchild");
    for (j=1; j<=i; j++)
      {
	      printf("\n%4d%8d%8d%8d%8d",j,HT[j].weight,
	      HT[j].parent,HT[j].lchild, HT[j].rchild);
      }
    printf("    按任意键，继续 ...");
    getchar();
  }//for

 //------无栈非递归遍历哈夫曼树，求哈夫曼编码
  HC=(HuffmanCode)malloc((n+1)*sizeof(char*));
  cd = (char *)malloc((n+1)*sizeof(char)); // 分配求编码的工作空间
  p = m;  cdlen = 0;
  for (i=1; i<=m; ++i)  // 遍历哈夫曼树时用作结点状态标志
     HT[i].tag = 0;
  while (p) 
  {
    if (HT[p].tag==0) 
	{               // 向左
      HT[p].tag = 1;
      if (HT[p].lchild != 0) 
	  { 
	      p = HT[p].lchild;  cd[cdlen++] ='0'; 
	  }
      else if (HT[p].rchild == 0) 
	  {     // 登记叶子结点的字符的编码
        HC[p] = (char *)malloc((cdlen+1) * sizeof(char));
        cd[cdlen] ='\0';  strcpy(HC[p], cd);    // 复制编码(串)
      }
    } else 
		if (HT[p].tag==1) 
		{        // 向右
	      HT[p].tag = 2;
	      if (HT[p].rchild != 0) 
		  { 
		      p = HT[p].rchild;  cd[cdlen++] ='1'; 
		  }
	    } 
		else 
		{   // HT[p].weight==2，退回退到父结点，编码长度减1
	      HT[p].tag = 0; p = HT[p].parent; --cdlen;  
	    }//else
  }//while
} // HuffmanCoding

/*
    //--- 从叶子到根逆向求每个字符的哈夫曼编码 ---
  cd = (char *)malloc(n*sizeof(char));    // 分配求编码的工作空间
  cd[n-1] = '\0';                         // 编码结束符。
  for (i=1; i<=n; ++i) {                  // 逐个字符求哈夫曼编码
    start = n-1;                          // 编码结束符位置
    for (c=i, f=HT[i].parent; f!=0; c=f, f=HT[f].parent) 
      // 从叶子到根逆向求编码
      if (HT[f].lchild==c) cd[--start] = '0';
      else cd[--start] = '1';
    HC[i] = (char *)malloc((n-start)*sizeof(char)); 
         // 为第i个字符编码分配空间
    strcpy(HC[i], &cd[start]);    // 从cd复制编码(串)到HC
  }
  free(cd);   // 释放工作空间
*/

void OutputHuffmanCode(HuffmanTree HT,HuffmanCode HC,int n) 
{ 
	  int i; 
	  printf("\nnumber---element---weight---huffman code\n"); 
	  for(i=1;i<=n;i++) 
	    printf("  %d        %c         %d        %s\n",i,HT[i].elem,HT[i].weight,HC[i]); 
}  

//主函数
//huffman.cpp
//#include"huffman_h.h"
int main() 
{ 
	  HuffmanTree HT; 
	  HuffmanCode HC; 
	  Weight *w; 
	  char c;     // the symbolizes;
	  int i,n;      // the number of elements; 
	  int wei;    // the weight of a element; 
	
	  printf("请输入构建哈夫曼树的结点数:" ); 
	  cin>>n; //cout<<endl;
	  w=(Weight *)malloc(n*sizeof(Weight)); 
	  for(i=0;i<n;i++)
	  { 
		    //cout<<"请输入第"<<i+1<<"个结点编号及其权值（如a 100）:"<<endl; 
		    printf("请输入结点编号及其权值（如a 100）:" ); 
		   scanf("%1s%d",&c,&wei); 
		    w[i].elem=c; 
		    w[i].m_weight=wei; 
	  } 
	
	  HuffmanCoding(HT,HC,w,n); 
	  OutputHuffmanCode(HT,HC,n);
	  return 0;
}
