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

Polyn AddPolyn(Polyn pa,Polyn pb)          
{
	Polyn qa=pa->next;
	Polyn qb=pb->next;
	Polyn headc,pc,qc;
	pc=(Polyn)malloc(sizeof(struct Polynomial));
	pc->next=NULL;
	headc=pc;
	while(qa!=NULL && qb!=NULL)
	{
		qc=(Polyn)malloc(sizeof(struct Polynomial));
		if(qa->expn<qb->expn)
		{
			qc->coef=qa->coef;
			qc->expn=qa->expn;
			qa=qa->next;
		}
		else if(qa->expn == qb->expn)
		{
			qc->coef=qa->coef+qb->coef;
			qc->expn=qa->expn;
			qa=qa->next;
			qb=qb->next;
		}
		else
		{
			qc->coef=qb->coef;
			qc->expn=qb->expn;
			qb=qb->next;
		}

		if(qc->coef!=0)
		{
			qc->next=pc->next;
			pc->next=qc;
			pc=qc;
		}
		else
			free(qc);
	}
	while(qa!=NULL)
	{
		qc=(Polyn)malloc(sizeof(struct Polynomial));
		qc->coef=qa->coef;
		qc->expn=qa->expn;
		qa=qa->next;
		qc->next=pc->next;
		pc->next=qc;
		pc=qc;
	}
	while(qb!=NULL)
	{
		qc=(Polyn)malloc(sizeof(struct Polynomial));
		qc->coef=qb->coef;
		qc->expn=qb->expn;
		qb=qb->next;
		qc->next=pc->next;
		pc->next=qc;
		pc=qc;
	}
	return headc;
}

Polyn SubtractPolyn(Polyn pa,Polyn pb)     
{
	Polyn h=pb;
	Polyn p=pb->next;
	Polyn pd;
	while(p)
	{
		p->coef*=-1;
		p=p->next;
	}
	pd=AddPolyn(pa,h);
	for(p=h->next;p;p=p->next)
	p->coef*=-1;
	return pd;
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
}

Polyn MultiplicatPolyn(Polyn h1,Polyn h2)  
{
	Polyn h,p,p1,p2,q;
    p1=h1->next;
    h=p=(Polyn)malloc(sizeof(struct Polynomial));
    p->next=NULL;
    while(p1)
    {
        p2=h2->next;
        while(p2)
        {
            q=(Polyn)malloc(sizeof(struct Polynomial));
        	q->coef=p1->coef*p2->coef;
            q->expn=p1->expn+p2->expn;
            p->next=q;
            p=q;
            p2=p2->next;
        }
        p1=p1->next;
    	}
       	p->next=NULL;
       	return(h);
}

Polyn MergePolyn(Polyn h)                  
{
	Polyn ddd=h->next;
	Polyn del,qqq;
	
	while(ddd)
	{
		qqq=ddd;
		while(qqq->next)
		{
			if(ddd->expn == qqq->next->expn)
			{
				del=qqq->next;
				qqq->coef+=del->coef;
				qqq->next=del->next;
				del->next=NULL;
				free(del);
			}
			qqq=qqq->next;
		}
		ddd=ddd->next;
	}
	return h;
}

Polyn InsortPolyn(Polyn h)                 
{
	Polyn s,p;
	int ddd,qqq;
	for(p=h->next;p!=NULL;p=p->next)
	{
		for(s=h->next;s->next!=NULL;s=s->next)
		{
			if(s->expn>s->next->expn)
			{
				ddd=s->expn;
				s->expn=s->next->expn;
				s->next->expn=ddd;
				qqq=s->coef;
				s->coef=s->next->coef;
				s->next->coef=qqq;
			}
		}
	}
	return h;
}

// int EvaluatPolyn(Polyn P)                   
// {
// 	Polyn p=P->next;
// 	int m,qqq=0;
// 	scanf("%d",&m);
// 	while(p!=NULL)
// 	{
// 		if(p->coef!=0)
// 		{	
// 			qqq=qqq+p->coef*pow(m,p->expn);
// 		}
// 		p=p->next;
// 	}
// 	printf("%d",qqq);
// 	return qqq;
// } 

int main()
{
	Polynomial *head1,*head2,*headc;                  
	head1=CreatePoly();                               
	head2=CreatePoly();                               
// 	headc=AddPolyn(head1,head2);                     
	headc=SubtractPolyn(head1,head2);                  
// 	headc=MultiplicatPolyn(head1,head2);             
// 	headc=MergePolyn(headc);                          
// 	EvaluatPolyn(head1);                              
//	headc=DerivatPolyn(head1);                        
//	headc=InsortPolyn(headc);                        	
	PrintPolyn(head1);                                
}
