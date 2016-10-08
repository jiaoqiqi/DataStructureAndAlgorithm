#include<stdio.h>
#include<stdlib.h>
#include<math.h>

typedef struct Polynomial                 
{
	float    coef;   
	int      expn;   
	struct   Polynomial *next;
}Polynomial,*Polyn;

Polyn CreatePoly()                        
{
	Polynomial *head,*rear,*s;
	int c,e,n;

	head=(Polynomial *)malloc(sizeof(Polynomial));
	rear = head;

	scanf("%d\n",&n);

	for(int i=1;i<=n;i++)
	{
		scanf("\n(%d,%d)",&c,&e);

		s=(Polynomial *)malloc(sizeof(Polynomial));
		s->coef=c;
		s->expn=e;
		rear->next=s;
		rear=s;
	}
	rear->next=NULL;
	return(head);

}

void PrintPolyn(Polyn P)                    
{
	Polyn q=P->next;
	int flag=1;
	if(!q)
	{
		putchar('0');
		printf("\n");
		return ;
	}
	while(q)
	{
		if(q->coef>0&&flag!=1)  putchar('+');
		if(q->coef!=1&&q->coef!=-1)
		{
			printf("%g",q->coef);
			if(q->expn==1)  putchar('X');
			else if(q->expn)  printf("X^%d",q->expn);
		}
		else
		{
			if(q->coef==1)
			{
				if(!q->expn) putchar('1');
				else if(q->expn==1)  putchar('X');
				else printf("X^%d",q->expn);
			}
		}
		q=q->next;
		flag++;
	}
	printf("\n");
}
Polyn DerivatPolyn(Polyn P)                 
{
	Polyn q=P->next;
	Polyn ddd,qqq,H;
	qqq=(Polyn)malloc(sizeof(struct Polynomial));
	qqq->next=NULL;
	H=qqq;
	while(q!=NULL)
	{
		ddd=(Polyn)malloc(sizeof(struct Polynomial));
		if(q->coef!=0)
		{
			if(q->expn==0)
			{
				ddd->coef=0;
				ddd->expn=0;
			}
			else
			{
				ddd->coef=q->coef*q->expn;
				ddd->expn=q->expn-1;
			}
		}
		if(ddd->coef!=0)
		{
			qqq->next=ddd;
			qqq=ddd;
		}
		q=q->next;
	}
	qqq->next=NULL;
	return H;
}int main()
{
	Polynomial *head1,*head2,*headc;                  
	head1=CreatePoly();                               
	head2=CreatePoly();                               
              
	headc=DerivatPolyn(head1);                        
	PrintPolyn(headc);                                
}
