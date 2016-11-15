// #include<stdio.h>
// #include<stdlib.h>
// typedef char DataType;

// typedef struct Node{
// 	DataType data;
// 	struct Node* lChild;
// 	struct Node* rChild;
// }BiNode,*BiTree;

// void Creat_BiTree(BiTree *T){
// 	char ch;
// 	scanf("%c",&ch);
// 	if(ch == '#')
// 		*T=NULL;
// 	else{
// 		*T = (BiTree)malloc(sizeof(BiNode));
// 		(*T)->data = ch;
// 		Creat_BiTree(&((*T)->lChild));
// 		Creat_BiTree(&((*T)->rChild));
// 	}
// }

// void LevelOrder(BiTree root){
// 	SqQueue *Q;
// 	BiTree p;
// 	InitQueue(Q);
// 	EnterQueue(Q,root);
// 	while(!IsEmpty(Q)){
// 		DeleteQueue(Q,&p);
// 		printf("%c",p->data);
// 		if(p->lChild!=NULL){
// 			EnterQueue(p->lChild);
// 		}
// 		if(p->rChild!=NULL){
// 			EnterQueue(p->rChild);
// 		}
// 	}
// }

// #define MAXSIZE 100
// typedef struct
// {
// 	DataType elem[MAXSIZE];
// 	int front;
// 	int rear;
// }SqQueue;

// void InitQueue(SqQueue *Q){
// 	Q->front=0;	
// 	Q->rear=0;
// }

// int IsEmpty(SqQueue *Q){
// 	if(Q->front==Q->rear)
// 		return true;
//  	return false;
// }

// int EnterQueue(SqQueue *Q,DataType e){
// 	if((Q->rear+1)%MAXSIZE==Q->front)
//  		return false;
// 	Q->elem[Q->rear]=e;
// 	Q->rear=(Q->rear+1)%MAXSIZE;
// 	return true;
// }

// int DeleteQueue(SqQueue *Q,DataType *e)
// {
// 	if(Q->front==Q->rear)
//  		return false;
// 	*e=Q->elem[Q->front];
// 	Q->front=(Q->front+1)%MAXSIZE;
// 	return true;
// }
// void main()
// {
// 	BiTree T;
// 	Creat_BiTree(&T);
// 	LevelOrder(T);
// }

// #include <stdio.h>
// #include <stdlib.h>

// typedef struct btnode//二叉链表类型定义
// {
// 	char data;
// 	struct btnode *lchild,*rchild;
// }bintree,*Bintree;

// typedef struct LinkQueueNode//链队列类型定义
// {
// 	bintree *data;
// 	struct LinkQueueNode *next;
// }LKQueNode;

// typedef struct LKQueue
// {
// 	LKQueNode *front,*rear;
// }LKQue;

// void InitQueue(LKQue *LQ)//初始化队列
// {
// 	LKQueNode *p;
// 	p=(LKQueNode*)malloc(sizeof(LKQueNode));
// 	LQ->front=p;
// 	LQ->rear=p;
// 	(LQ->front)->next=NULL;
// }

// int EmptyQueue(LKQue *LQ)//判断队列是否为空
// {
// 	if(LQ->front==LQ->rear)
// 		return 1;
// 	else 
// 		return 0;
// }

// void EnQueue(LKQue *LQ,Bintree x)//入队列
// {
// 	LKQueNode *p;
// 	p=(LKQueNode*)malloc(sizeof(LKQueNode));
// 	p->data=x;
// 	p->next=NULL;
// 	(LQ->rear)->next=p;
// 	LQ->rear=p;
// }

// int OutQueue(LKQue *LQ)//出队列
// {
// 	LKQueNode *s;
// 	if ( EmptyQueue(LQ)){
// 		exit(0);
// 		return 0;
// 	}
// 	else
// 	{
// 		s=(LQ->front)->next;
// 	(LQ->front)->next=s->next;
// 	if(s->next==NULL)
// 		LQ->rear=LQ->front;
// 	free(s);
// 	return 1;}
// }

// Bintree GetHead(LKQue *LQ)//取队列首元素
// {
// 	LKQueNode *p;bintree *q;q->data=-1;
// 	if(EmptyQueue(LQ))
// 		return q;
// 	else {
// 		p=LQ->front->next;
// 		return p->data;
// 	}
// } 

// Bintree initiate()//建二叉树 
// {
// 	char ch;Bintree t;
// 	ch=getchar(); 
// 	if(ch=='#') t=NULL;
// 	else
// 	{
// 		t=(Bintree)malloc(sizeof(bintree));
// 		t->data=ch;
// 		t->lchild=initiate();
// 		t->rchild=initiate();
// 	}
// 	return t;
// }
// void Visit(Bintree p)//访问节点
// {
// 	printf("%c",p->data);
// }

// void levelorder(Bintree bt)//层次遍历
// {
// 	LKQue Q;Bintree p;
// 	InitQueue(&Q);
// 	if(bt!=NULL){
// 		EnQueue(&Q,bt);
// 		while(!EmptyQueue(&Q))
// 		{
// 			p=GetHead(&Q);
// 			OutQueue(&Q);
// 			Visit(p);
// 			if(p->lchild!=NULL)
// 				 EnQueue(&Q,p->lchild);
// 			if(p->rchild!=NULL) 
// 				EnQueue(&Q,p->rchild);
// 		}
// 	}
// }

// void main()
// {
// 	Bintree T;
// 	T=initiate();
// 	levelorder(T);
// }

#include<stdio.h>
#include<stdlib.h>
typedef char DataType;

typedef struct Node{
	DataType data;
	struct Node* lChild;
	struct Node* rChild;
}BiNode,*BiTree;

int depth=0;
void PreTreeDepth(BiTree root,int h){
	if(root != NULL){
		if(h>depth)
			depth = h;
		PreTreeDepth(root -> lChild,h+1);
		PreTreeDepth(root -> rChild, h+1);
	}
} 

void Creat_BiTree(BiTree *T){
	char ch;
	scanf("%c",&ch);
	if(ch == '#')
		*T=NULL;
	else{
		*T = (BiTree)malloc(sizeof(BiNode));
		(*T)->data = ch;
		Creat_BiTree(&((*T)->lChild));
		Creat_BiTree(&((*T)->rChild));
	}
}

void PrintAtLevel(BiTree T,int level)
  {
      // 空树或层级不合理
      if (NULL == T || level < 1 )
          return;
  
      if (1 == level)
      {
      	printf("%c",T->data );
        return;
     }
 
     // 左子树的 level - 1 级
     PrintAtLevel(T->lChild,  level - 1);
 
     // 右子树的 level - 1 级
     PrintAtLevel(T->rChild, level - 1);
 }
 
 
 void LevelTraverse(BiTree T)
 {
     if (NULL == T)
         return;
 
 
     int i;
     for (i = 1; i <= depth+1; i++)
     {
         PrintAtLevel(T, i);
         
     }
 }   

int main(){
 	BiTree T;
	Creat_BiTree(&T);
	PreTreeDepth(T,0);
	LevelTraverse(T);

 }          