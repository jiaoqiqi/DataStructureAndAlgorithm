#include<stdio.h>
#include<stdlib.h>

typedef struct Polynomial{
	int coef;
	int expn;
	struct Polynomial *next;
}Polyn;

Polyn *Creat(int n ){
	Polyn *p,*head,*s;
	int e,c;
	char a,b;
	head= (Polyn *)malloc(sizeof(Polyn));
	head -> next = NULL;
	s = head;
	getchar();
	for(int i = 0 ; i<n ; i++){
		p = (Polyn *)malloc(sizeof(Polyn));
		scanf("%c%d,%d%c",&a,&c,&e,&b);
		p->coef=c;
		p->expn=e;
		s->next=p;
		s=p;
	}
	p->next=NULL;
	return(head);
}

void pritPolyn(Polyn *head , int n){
	Polyn *t;
	t= head -> next;
	for(int i = 0 ; i< n ; i++){
		if(t->expn ==0){
			printf("%d",t->coef );
		}
		else if(t -> expn == 1){
			printf("%dX",t->coef);
		}
		else{
			printf("%dX^%d",t -> coef , t-> expn );
		}
		t = t-> next;
		if(t != NULL){
			if(t -> coef > 0){
				printf("+");
			}
		}
	}
}


 int main(){
 	Polyn *phead;
 	int n ;
 	scanf("%d",&n);
 	phead=Creat(n);
 	pritPolyn(phead,n);
 }

