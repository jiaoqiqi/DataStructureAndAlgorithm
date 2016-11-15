#include<stdio.h>
#include<stdlib.h>
#define MAX 100

typedef char DataType;

typedef struct Node{
	DataType data;
	struct Node* lChild;
	struct Node* rChild;
}BiNode,*BiTree;

typedef struct{
	BiNode *data[MAX];
	int top;
}SeqStack;

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

void *Init_SeqStack(SeqStack *s){
	s->top=-1;
}

int IsEmpty(SeqStack *s){
	if((s->top)==-1)
		return 1;
	else
		return 0;
}

int Push(SeqStack *s,BiNode *x){
	if(s->top == MAX-1){
		return 0;
	}
	else{
		s->top ++;
		s->data[s->top] = x;
		return 1;
	}
}

int Pop(SeqStack *s,BiNode *x){
	if(IsEmpty(s)){
		return 0 ;
	}
	else{
		x = s->data[s->top];
		s->top --;
		return 1;
	}
}

char Top(SeqStack *s,char x){
	if(IsEmpty(s))
		return 0;
	else
		return s->data[s->top];
}


void PostOrder(BiTree root){ 
	SeqStack S; 
	Init_SeqStack(S);
	BiNode *p,*q;
	while(p || !IsEmpty(S)){
		if(p){
			Push(S,q);
			p=p->lChild;
		}
		else{
			GetTop(S,q);
			if(p->lChild==NULL || p->rChild==q){
				Pop(S,q);
				printf("%c\n",p->data );
				q=p;
				p=NULL;
			}
			else{
				p=p->rChild;
			}
		}
	}
}

void main(){
	BiTree T;
	Creat_BiTree(&T);
	PostOrder(T);
}