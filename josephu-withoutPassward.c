#include <stdio.h>
#include <stdlib.h>
#define MAX 100

typedef struct NodeType  //自定义结构体类型
{
	int id;
	struct NodeType *next;  //用于指向下一个结点的指针
}NodeType;
//函数声明
NodeType *CreaList(NodeType *,int);   //创建单项循环链表
NodeType *GetNode(int);   //得到一个节点
void PritList(NodeType *);
int IsEmptyList(NodeType *);  //测试链表是否为空
void JosephusOperate(NodeType *, int);  //运行约瑟夫环问题

NodeType *CreaList(NodeType *pHead ,int n){
	NodeType *p,*t;
	int i=0;
	int id,iPassword  ;
	
	for (i=1 ; i<=n ; i++){
		
		p=(NodeType *)malloc(sizeof(NodeType));
		p->id=i;
		if(i==1){
			pHead=t=p;
			t->next = pHead;
		}
		else{
			p->next = t->next;
			t->next=p;
			t=p;
		}
	}
	
	return pHead;
}

NodeType *GetNode(int iId ){
	NodeType *pNew = NULL;
	pNew = (NodeType *)malloc(sizeof(NodeType));
	if( !pNew){
		printf("Error,the memory is not enough!\n");
		exit(-1);
	}
	pNew -> id = iId;
	pNew -> next = NULL;

	return pNew;
}

void PritList(NodeType *pHead){
	NodeType *pCur = pHead;
	if(!IsEmptyList(pHead)){
		do{
			printf("%3d %7d\n",pCur->id );
			pCur = pCur->next;
		}while(pCur != pHead);
	}
}

int IsEmptyList(NodeType *pHead){
	if(!pHead){
		printf("The list is empty!\n");
		return 1;
	}
	return 0;
}

void JosephusOperate(NodeType *pHead ,int iPassword){
	NodeType *p,*t,*q;
	int i;
	int flag =1 ;
	t=p=pHead;
	while(t->next != pHead){
		t= t->next;
	}
	while(flag){
		for(i=1 ; i<iPassword ; i++){
			t=p;
			p=p->next;
		}
		if(p==t){
			flag = 0;
		}
		q=p;
		t->next = p->next;
		p=p->next;
		printf("%d ",q->id );
		free(q);
	}
}

int main(){
	int n =0 ;
	int m = 0;
	NodeType *pHead = NULL;
	do{
		if(n>MAX){
			printf("the people is to much\n");

		}
		scanf("%d" ,&n);
	}while( n > MAX);
	scanf("%d" ,&m);
	pHead=CreaList(pHead,n);
	JosephusOperate(pHead,m);
	return 1;
}

