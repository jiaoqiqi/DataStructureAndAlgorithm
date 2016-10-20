#include <stdio.h>

#include <stdlib.h>

#include <string.h>

#define DEBUG

#define NULL 0

#define ERROR -1

#define STACKSIZE 20

/* 定义字符类型栈 */

typedef struct{

char stackname[20];

char *base;

char *top;

} Stack;

/* ----------------- 全局变量--------------- */

Stack OPTR, OPND; /* 定义前个运算符栈，后个操作数栈 */

char expr[255] = ""; /* 存放表达式串 */

char *ptr = expr;

int step = 0; /* 计算的步次 */

int InitStack(Stack *s, char *name)

{

s->base=(char *)malloc(STACKSIZE*sizeof(char));

if(!s->base) exit (ERROR);

strcpy(s->stackname, name);

s->top=s->base;

return 1;

}

int In(char ch)

{

return(ch=='+'||ch=='-'||ch=='*'||ch=='/'||ch=='('||ch==')'||ch=='#');

}

void OutputStatus( )

{

char *s;

/* step */

printf("/n%-8d", ++step);

/* OPTR */

for(s = OPTR.base; s < OPTR.top; s++)

printf("%c", *s);

printf("/t");

/* OPND */

for(s = OPND.base; s < OPND.top; s++)

printf("%d ", *s);

/* input char */

printf("/t/t%c", *ptr);

}

int Push(Stack *s,char ch)

{

#ifdef DEBUG

char *name = s->stackname;

OutputStatus();

if(strcmp(name, "OPND") == 0)

printf("/tPUSH(%s, %d)", name, ch);

else

printf("/tPUSH(%s, %c)", name, ch);

#endif

*s->top=ch;

s->top++;

return 0;

}

char Pop(Stack *s)

{

char p;

#ifdef DEBUG

OutputStatus();

printf("/tPOP(%s)", s->stackname);

#endif

s->top--;

p=*s->top;

return (p);

}

char GetTop(Stack s)

{

char p=*(s.top-1);

return (p);

}

/* 判断运算符优先权，返回优先权高的 */

char Precede(char c1,char c2)

{

int i=0,j=0;

static char array[49]={

      '>', '>', '<', '<', '<', '>', '>',

'>', '>', '<', '<', '<', '>', '>',

'>', '>', '>', '>', '<', '>', '>',

'>', '>', '>', '>', '<', '>', '>',

'<', '<', '<', '<', '<', '=', '!',

'>', '>', '>', '>', '!', '>', '>',

'<', '<', '<', '<', '<', '!', '='};

switch(c1)

{

/* i为下面array的横标 */

case '+' : i=0;break;

case '-' : i=1;break;

case '*' : i=2;break;

case '/' : i=3;break;

case '(' : i=4;break;

case ')' : i=5;break;

case '#' : i=6;break;

}

switch(c2)

{

/* j为下面array的纵标 */

case '+' : j=0;break;

case '-' : j=1;break;

case '*' : j=2;break;

case '/' : j=3;break;

case '(' : j=4;break;

case ')' : j=5;break;

case '#' : j=6;break;

}

return (array[7*i+j]); /* 返回运算符 */

}

/*操作函数 */

int Operate(int a,char op,int b)

{

#ifdef DEBUG

OutputStatus();

printf("/tOPERATE(%d, %c, %d)", a, op, b);

#endif

switch(op)

{

case '+' : return (a+b);

case '-' : return (a-b);

case '*' : return (a*b);

case '/' : return (a/b);

}

}

int EvalExpr( )

{

char c,theta,x,m,ch;

int a,b;

c = *ptr++;

while(c!='#'||GetTop(OPTR)!='#')

{

if(!In(c))

{

m=atoi(&c);

Push(&OPND,m);

c = *ptr++;

}

else

switch(Precede(GetTop(OPTR),c))

{

case '<':

Push(&OPTR,c);

c = *ptr++;

break;

case '=':

x=Pop(&OPTR);

c = *ptr++;

break;

case '>':

theta=Pop(&OPTR);

b=Pop(&OPND); a=Pop(&OPND);

Push(&OPND,Operate(a,theta,b));

break;

}

}

return GetTop(OPND);

}

main( )

{

printf("Input the expression(end with /"#/" sign):");

do{

gets(expr);

}while(!*expr);

InitStack(&OPTR, "OPTR"); /* 初始化运算符栈 */

Push(&OPTR,'#'); /* 将#压入运算符栈 */

InitStack(&OPND, "OPND"); /* 初始化操作数栈 */

printf("/n/nresult:%d/n", EvalExpr());

return;

}