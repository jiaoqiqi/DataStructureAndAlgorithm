#include<stdio.h>
#include<malloc.h>
#define TRUE 1
#define OK 1
#define ERROR 0
typedef int ElemType; 
typedef struct node{
	ElemType date;
	struct node *next; 
}LNode,*LinkList;

// 初始化
LinkList InitList(LinkList L)
{
	L=(LinkList)malloc(sizeof(LNode));
	L->next=NULL;
	if(L->next == NULL)
	printf("初始化成功\n");
	return L;
}

//头插法创建 
LinkList creat_LinkList1() 
{
	LinkList H=(LinkList)malloc(sizeof(LNode));
	H->next=NULL;
	LNode *s;
	int x;
	printf("链表创建开始，输入0结束.\n");
	scanf("%d",&x);
	while(x != 0)
	{
		s=(LinkList)malloc(sizeof(LNode));
		s->date=x;
		s->next=H->next;
		H->next=s;
		scanf("%d",&x);
	}
	printf("创建完成\n");
	return H;
}

//尾插法创建
LinkList creat_LinkList2()
{
	LinkList H=(LinkList)malloc(sizeof(LNode));
	H->next=NULL;
	LNode *s,*r=H;
	int x;
	printf("链表创建开始，输入0结束.\n");
	scanf("%d",&x);
	while(x != 0)
	{
		s=(LinkList)malloc(sizeof(LNode));
		s->date=x;
		r->next=s;
		r=s;
		scanf("%d",&x);	
	}
	s->next=NULL;
	return H;	
}

//求表长
int Length_LinkList(LinkList L)
{
	int i=0;
	LNode *p = L;
	while(p->next != NULL)
	{
		p=p->next;
		i++;
	}
	return i;
 } 
 
 //查找 (按位置) 
LinkList Get_LinkList1(LinkList L,int k)
{
	LNode *p=L;
	int j=0;
	while(p->next != NULL && j<k)
	{
		p=p->next;
		j++;
	}
	return p;
}

//查找 (按值) 
LinkList Get_LinkList2(LinkList L,ElemType e)
{
	LNode *p=L->next;
	while(p!=NULL && p->date!=e)
	{
		p=p->next;
	}
	return p;  
}

//插入
LinkList Insert_LinkList(LinkList L,int k,ElemType e)
{
	LNode *p,*s;
	p=Get_LinkList1(L,k-1);
	if(p=NULL)
	{
		printf("插入位置k错误",k);
		return ERROR;
	}
	else 
	{
		s=(LinkList)malloc(sizeof(LNode));
		s->date=e;
		s->next=p->next;
		p->next=s;
	}
	
}

// 打印
void print(LinkList L)
{
	LNode *p=L->next;
	while(p)
	{
		printf("%d\n",p->date);
		p=p->next;
	}
 } 
int main()
{
	LinkList L;
	LNode *p;
	char ch,temp;
	int k,e,choose;
	
	do{
		printf("<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n");
		 printf("a.初始化\n");
		 printf("b.创建链表\n");
		 printf("c.查找\n");
		 printf("d.插入\n");
		 printf("e.表长\n");
		 printf("f.打印\n");
		 ch=getchar();
		 switch(ch)
		 {
		 	case 'A':
		 	case 'a':
		 		L=InitList(L);fflush(stdin);break;
		 	case 'B':
		 	case 'b':
		 		printf("方法：\n");
		 		printf("	1-头插创建\n");
				printf("	2-尾插创建");
				scanf("%d",&choose);
				if(choose == 1)
				 	L=creat_LinkList1();
				else
					L=creat_LinkList2(); 
				fflush(stdin);break;
		 	case 'C':
		 	case 'c':
		 		printf("方法：\n");
		 		printf("	1-按值\n");
				printf("	2-按位置");
				scanf("%d",&choose);
				if(choose == 1) 
				{
					printf("请输入值：");
					scanf("%d",&e);
					p=Get_LinkList1(L,e);
				}
				else
				{
					printf("请输入位置：");
					scanf("%d",&k);
					p=Get_LinkList2(L,e);
					printf("该元素是%d\n",p->date);
				}
				fflush(stdin);break;
		 	case 'D':
		 	case 'd':
		 		printf("请输入插入位置和值：");
		 		scanf("%d%d",&k,&e);
		 		Insert_LinkList(L,k,e);fflush(stdin);break;
		 	case 'E':
		 	case 'e':
		 		printf("表长：%d\n",Length_LinkList(L));fflush(stdin);break;
		 	case 'F':
			case 'f':	
				 print(L);fflush(stdin);break;	
		 }
		 printf("输入任意字符继续"); 
		 temp=getch();
		 system("cls");
		 
	}while(ch != 'Q' || ch != 'q');
}