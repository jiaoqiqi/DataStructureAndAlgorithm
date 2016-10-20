#include <stdio.h>
#define Stack_Size 100
 
typedef struct //定义栈
{
	char elem[Stack_Size];
    int top;
}SeqStack;
 
/*初始化栈*/
void InitStack(SeqStack *s)
{
	s->top=-1;
}
 
/*进栈操作*/
void Push(SeqStack *s,char x)
{
	if(s->top==Stack_Size-1)
		printf("\n\t栈已满！");
    else
	{
		s->top++;s->elem[s->top]=x;
	}
}
 
/*出栈操作*/
void Pop(SeqStack *s,char *x)
{
	if(s->top==-1)
		printf("\n\t栈为空！");
	else
	{
		*x=s->elem[s->top];
		s->top--;
	}
}
 
/*取栈顶元素*/
void GetTop(SeqStack *s,char *x)
{
	if(s->top==-1)
		printf("\n\t栈为空！");
	else
		*x=s->elem[s->top];
}
 
/*判断栈是否为空*/
int IsEmpty(SeqStack *s)
{
	if(s->top==-1)
		return(0);
	else
		return(1);
}
 
/*主函数*/
void main()
{
	SeqStack B,A,s,B1,A1,r,M;//定义栈
	char ch,ch1,ch2,x; //定义需要的字符
	char aa[100];
	int i=0,n;
	InitStack(&B);InitStack(&A);InitStack(&s);InitStack(&r);InitStack(&M);//对定义的栈初始化
 
	printf("\n\t请输入要翻译的魔王语言\n\t");//输入要翻译的魔王语言
	scanf("%s",aa);
	Push(&B,'t');Push(&B,'A');Push(&B,'d');Push(&B,'A');//进栈B→tAdA
	Push(&A,'s');Push(&A,'a');Push(&A,'e');//进栈A→sae
	for(i=0;aa[i]!='\0';i++)//将输入的魔王语言进栈s
		Push(&s,aa[i]);
	while(IsEmpty(&s))
	{
		Pop(&s,&ch);//将栈s的栈顶提取出来赋值给ch
		if(ch=='B')
		{
			B1=B;//将栈B赋值给栈B1
 
			while(IsEmpty(&B1))
			{
				Pop(&B1,&ch1);//B1不为空栈，则将栈B1的栈顶提取出来赋值给ch1
				if(ch1=='A')
				{
					A1=A;//将栈A赋值给栈A1
					while(IsEmpty(&A1))
					{
						Pop(&A1,&ch2);//将栈A1的栈顶提取出来赋值给ch2
						Push(&r,ch2);//ch2进栈r
					}
				}
				else Push(&r,ch1);//ch1不等于A的话，ch1进栈r
			}
		}
		else if(ch=='A')
		{
			A1=A;//ch=A的话，将栈A赋值给栈A1
			while(IsEmpty(&A1))
			{
				Pop(&A1,&ch2);//将栈A1的栈顶提取出来赋值给ch2
				Push(&r,ch2);//ch2进栈r
			}
		}
		else if(ch==')')
		{
			Pop(&s,&ch2);//ch=(,将栈s的栈顶提取出来赋值给ch2
			while(ch2!='(')
			{
				Push(&M,ch2);//ch2进栈M
				Pop(&s,&ch2);//将栈s的栈顶提取出来赋值给ch2
			}
			GetTop(&M,&ch2);//将栈M的栈顶提取出来赋值给ch2
			x=ch2;
			Pop(&M,&ch2);//将栈M的栈顶提取出来赋值给ch2
			while(IsEmpty(&M))
			{
				Push(&r,x);
				Pop(&M,&ch2);
				Push(&r,ch2);
			}
			Push(&r,x);
		}
		else Push(&r,ch);
	}
	M=r;
	printf("\n\n\t翻译的结果为：");//输出翻译的结果
	while(IsEmpty(&M))
	{
		Pop(&M,&ch);
		printf("%c",ch);
	}
	printf("\n\n\t是否继续翻译为汉语：（1-继续，0-不继续）\n\t");  //将魔王语言进一步转变成中文
	scanf("%d",&n);
	if(n==1)
	{
		printf("\n\n\t翻译为汉语的结果为：\n\n\t");
		M=r;
		while(IsEmpty(&M))
		{
			Pop(&M,&ch);
			if(ch=='t')      printf("天");
			else if(ch=='d') printf("地");
			else if(ch=='s') printf("上");
			else if(ch=='a') printf("一只");
			else if(ch=='e') printf("鹅");
			else if(ch=='z') printf("追");
			else if(ch=='g') printf("赶");
			else if(ch=='x') printf("下");
			else if(ch=='n') printf("蛋");
			else if(ch=='h') printf("恨");
		}
		printf("\n");
	}
	else ;
}