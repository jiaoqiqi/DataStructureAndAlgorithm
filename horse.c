#include <stdio.h>
#include <stdlib.h>
#define STACK_SIZE 100    	
#define STACKINCREMENT 10   
#define N 8 				
int weight[N][N];			
int Board[N][N][8];			
typedef struct{		
	int x;
	int y;
}posType;
typedef struct{		
	int ord;
	posType seat;	
	int di;			
}elemType;
typedef struct{	
	elemType *base;
	elemType *top;
	int stacksize;
}sqStack;
sqStack s;
int initStack()
{
	s.base = (elemType *)malloc(STACK_SIZE*sizeof(elemType));
	if(!s.base) return 0;
	s.top = s.base;
	s.stacksize = STACK_SIZE;
	return 1;
}
elemType getTop()
{
	if (s.top == s.base)
		exit(0);
	return *(s.top-1);
}
void Push(elemType elem)
{
	*s.top++=elem;
}
int Pop(elemType *elem)
{
	if(s.top == s.base)
	*elem = *--s.top;
	return 1;
}
int stackEmpty()
{
	if(s.top == s.base)
		return 1;
	else 
		return 0;
}
void outputPath()
{
	int i,f,k;
	sqStack s1 = s;
	int path[N][N];
	for (i = 0; s1.top != s1.base; ++i)
	{
		path[(*s1.base).seat.x][(*s1.base).seat.y] = i+1;
		++s1.base;
	}
	for (f = 0; f < N; f++)
	{
		printf("\n");
		for (k = 0; k < N; ++k)
		{
			printf("\t%d", (path[f][k]));
		}
	}
	printf("\n");
}
int Pass(posType curpos) 	//判断当前位置是否合法
{
	sqStack s1 = s;
	if(curpos.x < 0 || curpos.x >(N-1) || curpos.y < 0 || curpos.y > (N-1))
		return 0;
	for(;s1.top != s1.base;)
	{
		--s1.top;
		if(curpos.x == (*s1.top).seat.x && curpos.y == (*s1.top).seat.y)
			return 0;
	}
	return 1;
}
posType nextPos(posType curpos,int direction)
{
	switch(direction)
	{
		case 1: 
			curpos.x += 1;
			curpos.y -= 2;
			break;
		case 2:
			curpos.x += 2;
			curpos.y -+ 1;
			break;
		case 3:
			curpos.x += 2;
			curpos.y += 1;
			break;
		case 4:
			curpos.x += 1;
			curpos.y += 2;
			break;
		case 5:
			curpos.x -= 1;
			curpos.y += 2;
			break;
		case 6:
			curpos.x -= 2;
			curpos.y += 1;
			break;
		case 7:
			curpos.x -= 2;
			curpos.y -= 1;
			break;
		case 8:
			curpos.x -= 1;
			curpos.y -= 2;
			break; 		
	}
	return curpos;
}
void setWeight()
{
	int i,j,k;
	posType m;
	elemType elem;
	for (i = 0; i < N; ++i)
	{
		for (j = 0; j < N; ++j)
		{
			elem.seat.x = i;
			elem.seat.y = j;
			weight[i][j] = 0;
			for(k = 0; k < N; k++)
			{
				m = nextPos(elem.seat,k+1);
				if(m.x >= 0 && m.x < N && m.y >= 0 && m.y < N)
					weight[i][j]++;
			}
		}
	}
}
void setMap()
{
	int a[N];
	int i,j,k,min,m,s,h;
	posType n1,n2;
	for (i = 0; i < N; ++i)
	{
		for(j = 0; j < N; j++)
		{
			for(h = 0; h < N; h++)
			{
				n2.x = i;
				n2.y = j;
				n1 = nextPos(n2,h+1);
				if(n1.x >= 0 && n1.x < N && n1.y >= 0 && n1.y < N)
					a[h] = weight[n1.x][n1.y];
				else 
					a[h] = 0;
			}
			for(m = 0; m < N; m++)
			{
				min = N+1;
				for(k = 0; k < N; k++)
				{
					if(min > a[k])
					{
						min = a[k];
						Board[i][j][m] = k;
						s = k;
					}
					a[s] = N+1;
				}
			}
		}
	}
}
int horsePath(posType start)
{
	posType curpos;
	int horsestep = 0,off;
	elemType elem;
	curpos = start;
	do{
		if(Pass(curpos))
		{
			horsestep++;
			elem.di = 0;
			elem.ord = horsestep;
			elem.seat = curpos;
			Push(elem);
			if(N*N == horsestep)
				return 1;
			off = Board[elem.seat.x][elem.seat.y][elem.di]+1;
			curpos = nextPos(elem.seat,off);
		}
		else
		{
			if(!stackEmpty())
			{
				while(!stackEmpty() && elem.di ==N)
				{
					Pop(&elem);
					if(!stackEmpty())
					{
						elem = getTop();
						horsestep = elem.ord;
					}
				}
				if(!stackEmpty() && elem.di < N)
				{
					Pop(&elem);
					off = Board[elem.seat.x][elem.seat.y][++elem.di];
					curpos = nextPos(elem.seat,off+1);
					Push(elem);
				}
			}
		}
	}while(!stackEmpty());
	printf("%s\n","走不通");
	return 0;
}
void main()
{
	posType start;
	initStack();
	printf("%s\nX:","输入起始位置:(0-7)" );
	scanf("%d",&start.x);
	printf("Y:");
	scanf("%d",&start.y);
	setWeight();
	setMap();
	horsePath(start);
	outputPath();
}
