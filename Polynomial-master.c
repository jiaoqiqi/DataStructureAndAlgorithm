#include<stdio.h>
#include<malloc.h>

typedef struct Polynomial{
	float coef;
	int expn;
	struct Polynomial *next;
}Polynomial,*Polyn;
//创建
Polyn createPoly()
{
	Polynomial *head,*p,*q;
	float coef;
	int expn;
	printf("请输入多项式系数和指数：");
	head = (Polyn)malloc(sizeof(Polynomial));
	p = head;
	scanf("%f%d",&coef,&expn);
	while(coef != 0)
	{
		q = (Polyn)malloc(sizeof(Polynomial));
		q->coef = coef;
		q->expn = expn;
		p->next = q;
		p = q;
		scanf("%f%d",&coef,&expn);
	}
	q->next = NULL;
	return head;
}
void print(Polyn head)
{
	Polyn q = head;
	int flag = 1;
	if(!q)
	{
		putchar('0');
		printf("\n");
		return;
	}
	while(q)
	{
		if(q->coef>0 && flag != 1)
		putchar('+');
		if(q->coef != 1 && q->coef != -1)
		{
			printf("%.1f",q->coef);
			if(q->expn ==1)
			putchar('X');
			else if(q->expn)
				printf("X^%d",q->expn);
		}
		else 
		{
			if(q->coef == 1)
			{
				if(!q->expn == 1)
					putchar('1');
				else if(q->expn == 1)
					putchar('X');
				else
					printf("X^%d",q->expn);
			}
			if(q->coef == -1)
			{
				if(!q->expn)
					printf("-1");
				else if(q->expn == 1)
					printf("-X");
				else
					printf("-X^%d",q->expn);
			}
		}
		q = q->next;
		flag++;
	}
	printf("\n");

}
// 两个多项式相加
Polyn AddPolyn(Polyn pa,Polyn pb)
{
	Polyn qa = pa->next;
	Polyn qb = pb->next;
	Polyn headc,pc,qc;
	pc = (Polyn)malloc(sizeof(Polynomial));
	pc->next = NULL;
	headc = pc;
	while(qa != NULL && qb != NULL)
	{
		qc = (Polyn)malloc(sizeof(Polynomial));
		if(qa->expn < qb->expn)
		{
			qc->coef=qa->coef;
			qc->expn=qa->expn;
			qa = qa->next; 
		}
		else if(qa->expn == qb->expn)
		{
			qc->coef = qa->coef+qb->coef;
			qc->expn = qa->expn;
			qa = qa->next;
			qb = qb->next;
		}
		else 
		{
			qc->coef = qb->coef;
			qc->expn = qb->expn;
			qb =qb->next;
		}
		if(qc->coef != 0)
		{
			qc->next = pc->next;
			pc->next = qc;
			pc = qc;
		}
		while(qa != NULL)
		{
			qc = (Polyn)malloc(sizeof(Polynomial));
			qc->coef=qa->coef;
			qc->expn=qa->expn;
			qa = qa->next; 
			qc->next = pc->next;
			pc->next = qc;
			pc = qc;
		}
		while(qb != NULL)
		{
			qc = (Polyn)malloc(sizeof(Polynomial));
			qc->coef=qb->coef;
			qc->expn=qb->expn;
			qb = qb->next; 
			qc->next = pc->next;
			pc->next = qc;
			pc = qc;
		}
	 } 
 } 
 Polyn subtractPolyn(Polyn pa,Polyn pb)
 {
 	Polyn h=pb;
 	Polyn p=pb->next;
 	Polyn pd;
 	while(p)
 	{
 		p->coef *= -1;
 		p=p->next;
	}
	pd = AddPolyn(pa,h);
	for(p=h->next;p;p=p->next)
	p->coef *= -1;
	return pd;
  } 
int main()
{
	Polyn pa,pb;
	printf("输入pa:\n");
	pa=createPoly();
	printf("pa:\n");
	print(pa);
	printf("输入pb:\n");
	pb=createPoly();
	printf("pb:\n");
	print(pb);
	getch();
	printf("AddPolyn：\n");
	print(AddPolyn(pa,pb));
	getch();
	printf("subtractPolyn:\n");
	print(subtractPolyn(pa,pb));
	
	
	
 } 
