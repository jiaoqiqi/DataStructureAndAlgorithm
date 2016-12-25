//-------------���������Ľ���-------------- 
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
}Weight; // ���������Ϣ; 

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
  // w���n���ַ���Ȩֵ(��>0)�������������HT��
  // �����n���ַ��Ĺ���������HC
  //������ʵ��ѡ��ʽ����������ѡ������СȨֵ��㣬�����Ϣ��ǰ���Ϊ�����������Ϊ������
//�޸�ѡ��ʽ������ѡ������СȨֵ��㣬ȨֵС��Ϊ������������

  int i, j, m, s1,s2;
  char *cd;
  int p;
  int cdlen;

  if (n<=1) return;
  m = 2 * n - 1;
  HT = (HuffmanTree)malloc((m+1) * sizeof(HTNode));   // 0�ŵ�Ԫδ��
  for (i=1; i<=n; i++)
   { //��ʼ��
	    HT[i].elem=w[i-1].elem;
	    HT[i].weight=w[i-1].m_weight;
	    HT[i].parent=0;
	    HT[i].lchild=0;
	    HT[i].rchild=0;
  }
  for (i=n+1; i<=m; i++)
   { //��ʼ��
	    HT[i].weight=0;
	    HT[i].parent=0;
	    HT[i].lchild=0;
	    HT[i].rchild=0;
  }
	  printf("\n���������Ĺ������������ʾ��\n");
	  printf("HT��̬:\n  ���  weight  parent  lchild  rchild");
	  for (i=1; i<=m; i++)
	     printf("\n%4d%8d%8d%8d%8d",i,HT[i].weight,HT[i].parent,HT[i].lchild, HT[i].rchild);
	  printf("    ������������� ...");
	      getchar();
  for (i=n+1; i<=m; i++)
   {     // ����������
    // ��HT[1..i-1]��ѡ��parentΪ0��weight��С��������㣬
    // ����ŷֱ�Ϊs1��s2��
    Select(HT, i-1, s1, s2);
    HT[s1].parent = i;  HT[s2].parent = i;
    HT[i].lchild = s1;  HT[i].rchild = s2;
    HT[i].weight = HT[s1].weight + HT[s2].weight;
    printf("\nselect: s1=%d   s2=%d\n", s1, s2);
    printf("  ���  weight  parent  lchild  rchild");
    for (j=1; j<=i; j++)
      {
	      printf("\n%4d%8d%8d%8d%8d",j,HT[j].weight,
	      HT[j].parent,HT[j].lchild, HT[j].rchild);
      }
    printf("    ������������� ...");
    getchar();
  }//for

 //------��ջ�ǵݹ�������������������������
  HC=(HuffmanCode)malloc((n+1)*sizeof(char*));
  cd = (char *)malloc((n+1)*sizeof(char)); // ���������Ĺ����ռ�
  p = m;  cdlen = 0;
  for (i=1; i<=m; ++i)  // ������������ʱ�������״̬��־
     HT[i].tag = 0;
  while (p) 
  {
    if (HT[p].tag==0) 
	{               // ����
      HT[p].tag = 1;
      if (HT[p].lchild != 0) 
	  { 
	      p = HT[p].lchild;  cd[cdlen++] ='0'; 
	  }
      else if (HT[p].rchild == 0) 
	  {     // �Ǽ�Ҷ�ӽ����ַ��ı���
        HC[p] = (char *)malloc((cdlen+1) * sizeof(char));
        cd[cdlen] ='\0';  strcpy(HC[p], cd);    // ���Ʊ���(��)
      }
    } else 
		if (HT[p].tag==1) 
		{        // ����
	      HT[p].tag = 2;
	      if (HT[p].rchild != 0) 
		  { 
		      p = HT[p].rchild;  cd[cdlen++] ='1'; 
		  }
	    } 
		else 
		{   // HT[p].weight==2���˻��˵�����㣬���볤�ȼ�1
	      HT[p].tag = 0; p = HT[p].parent; --cdlen;  
	    }//else
  }//while
} // HuffmanCoding

/*
    //--- ��Ҷ�ӵ���������ÿ���ַ��Ĺ��������� ---
  cd = (char *)malloc(n*sizeof(char));    // ���������Ĺ����ռ�
  cd[n-1] = '\0';                         // �����������
  for (i=1; i<=n; ++i) {                  // ����ַ������������
    start = n-1;                          // ���������λ��
    for (c=i, f=HT[i].parent; f!=0; c=f, f=HT[f].parent) 
      // ��Ҷ�ӵ������������
      if (HT[f].lchild==c) cd[--start] = '0';
      else cd[--start] = '1';
    HC[i] = (char *)malloc((n-start)*sizeof(char)); 
         // Ϊ��i���ַ��������ռ�
    strcpy(HC[i], &cd[start]);    // ��cd���Ʊ���(��)��HC
  }
  free(cd);   // �ͷŹ����ռ�
*/

void OutputHuffmanCode(HuffmanTree HT,HuffmanCode HC,int n) 
{ 
	  int i; 
	  printf("\nnumber---element---weight---huffman code\n"); 
	  for(i=1;i<=n;i++) 
	    printf("  %d        %c         %d        %s\n",i,HT[i].elem,HT[i].weight,HC[i]); 
}  

//������
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
	
	  printf("�����빹�����������Ľ����:" ); 
	  cin>>n; //cout<<endl;
	  w=(Weight *)malloc(n*sizeof(Weight)); 
	  for(i=0;i<n;i++)
	  { 
		    //cout<<"�������"<<i+1<<"������ż���Ȩֵ����a 100��:"<<endl; 
		    printf("���������ż���Ȩֵ����a 100��:" ); 
		   scanf("%1s%d",&c,&wei); 
		    w[i].elem=c; 
		    w[i].m_weight=wei; 
	  } 
	
	  HuffmanCoding(HT,HC,w,n); 
	  OutputHuffmanCode(HT,HC,n);
	  return 0;
}
