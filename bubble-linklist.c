#include<stdio.h>
#include<stdlib.h>
typedef struct student{
	int num;
	struct student *next;
}st;
int count;
st *create()
{
	st *head,*q;
	int num;
	head=(st *)malloc(sizeof(st));
	head->next = NULL;
	scanf("%d",&num);
	while(num!=0)
	{
		q=(st *)malloc(sizeof(st));
		q->num=num;
		q->next=head->next;
		head->next = q;
		scanf("%d",&num);
		count++;
	}
	return head;
}
st *sort(st *head)
{
	st *f,*p,*x,*y;
	f= NULL;
	if(head->next == NULL || head->next->next == NULL){
		return 0;
	} 
	while (f != head->next->next){
		for(p=head ; p->next->next!=f ; p=p->next){
			if(p->next->num > p->next->next->num){
				x = p -> next;  
                y = p -> next -> next;  
                p -> next = y;  
                x -> next = y -> next;  
                y -> next = x; 
			}
		}
		f= p->next;
	}

}


print(st *head)
{
	st *p=head->next;
	while(p!=NULL)
	{
		printf("%d\n",p->num);
		p=p->next;
	}
}
int main()
{
	st *head;
	head=create();
	sort(head);
	print(head);
	return 0;
}
