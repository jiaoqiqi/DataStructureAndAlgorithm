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


void PreOrder(BiTree root){
	SeqStack *S;
	BiTree p;
	Init_SeqStack(S);
	p=root;
	while(p!=NULL || !IsEmpty(S)){
		if(p){
			printf("%c\n",p->data );
			Push(S,p);
			p = p->lChild;
		}
		else{
			Pop(S,p);
			p=p->rChild;
		}
	}
}

void InOrder(BiTree root){
	SeqStack *S;
	Init_SeqStack(S);
	BiNode *p;
	p=root;
	while(p || !IsEmpty(S)){
		if(p){
			Push(S,p);
			p = p->lChild;
		}
		else{
			Pop(S,p);
			printf("%c ",p->data );
			p=p->rChild;
		}
	}
}

void main(){
	BiTree T;
	Creat_BiTree(&T);
	PreOrder(T);
	InOrder(T);
}
