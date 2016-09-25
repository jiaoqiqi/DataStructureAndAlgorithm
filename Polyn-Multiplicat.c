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

	for(int i = 1 ; i <= n ; i ++)
	{
		scanf("\n(%d,%d)",&c,&e);

		s=(Polynomial *)malloc(sizeof(Polynomial));
		s -> coef = c;
		s -> expn = e;
		rear->next = s;
		rear = s;
	}
	rear -> next = NULL;
	return(head);

}

void PrintPolyn(Polyn P)                    
{
	Polyn q = P->next;
	int flag = 1;
	if(!q)
	{
		putchar('0');
		printf("\n");
		return ;
	}
	while(q)
	{
		if(q -> coef > 0 && flag != 1)  putchar('+');
		if(q -> coef != 1 && q -> coef != -1)
		{
			printf("%g",q->coef);
			if(q -> expn == 1)  putchar('X');
			else if(q -> expn)  printf("X^%d",q -> expn);
		}
		else
		{
			if(q->coef == 1)
			{
				if(!q -> expn) putchar('1');
				else if(q ->expn == 1 )  putchar('X');
				else printf("X^%d",q -> expn);
			}
		}
		q = q -> next;
		flag ++;
	}
	printf("\n");
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
	Polyn d=h->next;
	Polyn del,q;
	
	while(d)
	{
		q=d;
		while(q->next)
		{
			if(d->expn == q->next->expn)
			{
				del=q->next;
				q->coef+=del->coef;
				q->next=del->next;
				del->next=NULL;
				free(del);
			}
			q=q->next;
		}
		d=d->next;
	}
	return h;
}

int main()
{
	Polynomial *head1,*head2,*head3;                  
	head1=CreatePoly();                               
	head2=CreatePoly();                               
	head3=MultiplicatPolyn(head1,head2); 
	head3=MergePolyn(head3);                            	
	PrintPolyn(head3);                                
}