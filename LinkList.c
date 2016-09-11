#include <stdio.h>
#include <stdlib.h>
#define ERROR 0
#define OK 1

typedef int ElemType;
typedef struct node
{
	ElemType data;
	struct node *next;
}LNode, *LinkList;

LinkList initList(LinkList L){
	L = (LinkList)malloc(sizeof(LNode));
	L -> next = NULL;
	return L;
}

void CreatFromTail(LinkList L){
	LNode *r,*s;
	char c;
	r=L;
	while(1){
		c = getchar();
		if(c != '$'){
			s = (LNode *)malloc(sizeof(LNode));
			s -> data = c;
			r->next = s;
			r=s;
		}
		else{
			r->next = NULL;
			break;
		}
	}
}

void CreatFromHead(LinkList L){
	LNode *s;
	char c ; 
	while(1){
		c= getchar();
		if(c != '$'){
			s = (LNode *)malloc(sizeof(LNode));
			s->data = c;
			s->next = L->next ;
			L->next = s;
		}else{
			break;
		}
	}
}

LinkList GetDataByNumber(LinkList L,int i){
	LNode *p = L;
	int j=0 ; 
	while(p != NULL && j<i){
		p = p->next ;
		j++;
	}
	return p;
}

LinkList Locate(LinkList L,ElemType e){
	LNode *p = L->next;
	while(p != NULL){
		if(p->data != e){
			p = p->next;
		}else break;
	}
	return p;
}

int ListInsert(LinkList L,int i,ElemType e){
	LNode *p =L , *s;
	int j=0;
	while(p!=NULL && j<i-1){
		p = p-> next;
		j++;

	}
	if( p!= NULL){
		s = (LinkList)malloc(sizeof(LNode));
		s->data =e;
		s->next = p->next;
		p->next = s;
		return OK;
	}
	else 
		return ERROR;

}


int ListDelete(LinkList L,int i, ElemType e){
	LNode *p=L , *s,*q;
	int j=0;
	while(p!=NULL && j<i-1){
		p=p->next;
		j++;
	}
		if(p->next = NULL){
			q = p->next;
			e = q->data;
			p->next = p->next->next;
			free(q);
			return OK;
		}
		else{
			return ERROR;
		}
	
}

void ListReverse(LinkList L){
	LNode *q,*p;
	p = L->next;
	L->next = NULL;
	while(p!=NULL){
		q = p->next;
		p->next = L->next;
		L->next =p;
		p=q;
	}
}

int main(){
	initList(L);
	CreatFromTail(L);
	for(int i=1 ; i<5 ; i++){
		ListInsert(L,i,i);
	
	}
}