#include <stdio.h>
#include <stdlib.h>
#define MAX 100

typedef struct NodeType  //自定义结构体类型
{
	int id;
	int password;
	struct NodeType *next;  //用于指向下一个结点的指针
}NodeType;
//函数声明
void CreaList(NodeType **,int);   //创建单项循环链表
NodeType *GetNode(int ,int);   //得到一个节点
void PritList(NodeType *);
int IsEmptyList(NodeType *);  //测试链表是否为空
void JosephusOperate(NodeType **, int);  //运行约瑟夫环问题

void CreaList(NodeType **ppHead ,int n){
	int i=0;
	int iPassword = 0 ;
	NodeType *pNew = NULL;
	NodeType *pCur = NULL;
	for (i=1 ; i<=n ; i++){
		printf("请输入第%d个人的密码" , i);
		scanf("%d" ,&iPassword);
		pNew = GetNode(i,iPassword);
		if(*ppHead == NULL){
			*ppHead = pCur = pNew;
		}else
		{
			pNew -> next = pCur -> next;
			pCur -> next = pNew;
			pCur = pNew;
		}
	}
	printf("Complite the list create\n");

}

NodeType *GetNode(int iId , int iPassword){
	NodeType *pNew = NULL;
	pNew = (NodeType *)malloc(sizeof(NodeType));
	if( !pNew){
		printf("Error,the memory is not enough!\n");
		exit(-1);
	}
	pNew -> id = iId;
	pNew -> password = iPassword;
	pNew -> next = NULL;

	return pNew;
}

void PritList(NodeType *pHead){
	NodeType *pCur = pHead;
	if(!IsEmptyList(pHead)){
		printf("--ID-- -- PASSWORD--\n");
		do{
			printf("%3d %7d\n",pCur->id , pCur->password );
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

void JosephusOperate(NodeType **ppHead ,int iPassword){
	int iCounter = 0;
	int iFlag = 1;
	NodeType *pPrv = NULL;
	NodeType *pCur = NULL;
	NodeType *pDel = NULL;
	pPrv = pCur = *ppHead;
	while(pPrv->next != *ppHead){
		pPrv = pPrv->next;
	}
	while(iFlag){
		for(iCounter = 1 ; iCounter<iPassword ; iCounter++){
			pPrv = pCur;
			pCur = pCur->next;
		}
		if(pPrv == pCur) iFlag=0;
		pDel = pCur;
		pPrv -> next = pCur->next;
		pCur = pCur->next;
		iPassword = pDel->password;
		printf("the %d go out of the list (password:%d)\n",pDel->id , pDel->password );
		free(pDel);
	}
	*ppHead = NULL;
	getchar();
}

int main(){
	int n =0 ;
	int m = 0;
	NodeType *pHead = NULL;
	do{
		if(n>MAX){
			printf("the people is to much\n");

		}
		printf("the most numer is: %d",MAX );
		scanf("%d" ,&n);
	}while( n > MAX);
	printf("Please input the original password:");
	scanf("%d" ,&m);
	CreaList(&pHead,n);
	printf("\n ----------printf the circle list----------\n" );
	PritList(pHead);
	printf("\n ----------printf the queued list----------\n" );
	JosephusOperate(&pHead,m);
	return 1;
}

