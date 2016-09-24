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

		s = (Polynomial *)malloc(sizeof(Polynomial));
		s -> coef = c;
		s -> expn = e;
		rear -> next = s ;
		rear = s;
	}
	rear -> next = NULL;
	return(head);

}

void PrintPolyn(Polyn P)                    
{
	Polyn q = P -> next;
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
			printf("%g",q -> coef);
			if(q -> expn == 1)  putchar('X');
			else if(q -> expn)  printf("X^%d",q -> expn);
		}
		else
		{
			if(q -> coef == 1)
			{
				if(! q -> expn) putchar('1');
				else if(q -> expn == 1)  putchar('X');
				else printf("X^%d",q -> expn);
			}
		}
		q = q -> next;
		flag++;
	}
	printf("\n");
}

Polyn AddPolyn(Polyn pa,Polyn pb)          
{
	Polyn qa = pa -> next;
	Polyn qb = pb -> next;
	Polyn headc,pc,qc;
	pc = (Polyn)malloc(sizeof(struct Polynomial));
	pc -> next = NULL;
	headc = pc;
	while(qa != NULL && qb != NULL)
	{
		qc = (Polyn)malloc(sizeof(struct Polynomial));
		if(qa -> expn < qb -> expn)
		{
			qc -> coef = qa -> coef;
			qc -> expn = qa -> expn;
			qa = qa -> next;
		}
		else if(qa -> expn == qb -> expn)
		{
			qc -> coef = qa -> coef + qb -> coef;
			qc -> expn = qa -> expn;
			qa = qa -> next;
			qb = qb -> next;
		}
		else
		{
			qc -> coef = qb -> coef;
			qc -> expn = qb -> expn;
			qb = qb -> next;
		}

		if(qc -> coef != 0)
		{
			qc -> next = pc -> next;
			pc -> next = qc;
			pc = qc; 
		}
		else
			free(qc);
	}
	while(qa != NULL)
	{
		qc=(Polyn)malloc(sizeof(struct Polynomial));
		qc -> coef = qa -> coef;
		qc -> expn = qa -> expn;
		qa = qa -> next;
		qc -> next = pc -> next;
		pc -> next = qc;
		pc = qc;
	}
	while(qb!=NULL)
	{
		qc=(Polyn)malloc(sizeof(struct Polynomial));
		qc -> coef = qb -> coef;
		qc -> expn = qb -> expn;
		qb = qb -> next;
		qc -> next = pc -> next;
		pc -> next = qc;
		pc = qc;
	}
	return headc;
}

int main()
{
	Polynomial *head1,*head2,*headc;                  
	head1 = CreatePoly(); 
	head2 = CreatePoly();
	headc = AddPolyn(head1,head2);                                                	
	PrintPolyn(headc);                                
}
