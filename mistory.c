#include<stdio.h>

#include<stdlib.h>

#define n1 10

#define n2 10

typedef struct node

{

int x; //存x坐标

int y; //存Y坐标

int c;  //存该点可能的下点所在的方向,1表示向右,2向上,3向左,4向下

}linkstack;

linkstack top[100];

//迷宫矩阵

int maze[n1][n2]={

1,1,1,1,1,1,1,1,1,1,

0,0,0,1,0,0,0,1,0,1,

1,1,0,1,0,0,0,1,0,1,

    1,0,0,0,0,1,1,0,0,1,

    1,0,1,1,1,0,0,0,0,1,

    1,0,0,0,1,0,0,0,0,0,

    1,0,1,0,0,0,1,0,0,1,

    1,0,1,1,1,0,1,1,0,1,

    1,1,0,0,0,0,0,0,0,1,

    1,1,1,1,1,1,1,1,1,1,};

int i,j,k,m=0;

main( )

{

//初始化top[],置所有方向数为右

for(i=0;i<n1*n2;i++)

{

top[i].c=1;

}

printf("the maze is:n");

//打印原始迷宫矩阵

for(i=0;i<n1;i++)

{

       for(j=0;j<n2;j++)

       printf(maze[i][j]?"* ":"  ");

printf("n");

}

i=0;top[i].x=1;top[i].y=0;

maze[1][0]=2;

/*回溯算法*/

do

{

       if(top[i].c<5)    //还可以向前试探

       {

              if(top[i].x==5 && top[i].y==9) //已找到一个组合

              {

              //打印路径

                     printf("The way %d is:n",m++);

                     for(j=0;j<=i;j++)

                     {

                            printf("(%d,%d)-->",top[j].x,top[j].y);

                     }

                      printf("n");

                     //打印选出路径的迷宫

                             for(j=0;j<n1;j++)

                            {

                                   for(k=0;k<n2;k++)

{

                                       if(maze[j][k]==0) printf("  ");

                                      else if(maze[j][k]==2)  printf("O ");

                                      else printf("* ");

                               }

                               printf("n");

                         }

                         maze[top[i].x][top[i].y]=0;

                         top[i].c = 1;

                               i--;

                         top[i].c += 1;

                               continue;

                 }

           switch (top[i].c)   //向前试探

           {

                   case 1:

{

              if(maze[top[i].x][top[i].y+1]==0)

              {

                      i++;

                     top[i].x=top[i-1].x;

                     top[i].y=top[i-1].y+1;

                     maze[top[i].x][top[i].y]=2;

               }

               else

               {

                     top[i].c += 1;

              }

               break;

       }

        case 2:

       {

               if(maze[top[i].x-1][top[i].y]==0)

               {

                       i++;

                     top[i].x=top[i-1].x-1;

                      top[i].y=top[i-1].y;

                     maze[top[i].x][top[i].y]=2;

              }

               else

               {

                      top[i].c += 1;

               }

              break;

       }

       case 3:

       {

               if(maze[top[i].x][top[i].y-1]==0)

              {

                      i++;

                     top[i].x=top[i-1].x;

                     top[i].y=top[i-1].y-1;

                     maze[top[i].x][top[i].y]=2;

              }

               else

               {

                      top[i].c += 1;

              }

              break;

       }

    case 4:

    {

              if(maze[top[i].x+1][top[i].y]==0)

                    {

                      i++;

                      top[i].x=top[i-1].x+1;

                     top[i].y=top[i-1].y;

                     maze[top[i].x][top[i].y]=2;

              }

              else

              {

                     top[i].c += 1;

              }

               break;

       }

  }

}

else    

 {

       if(i==0) return;   //已找完所有解

        maze[top[i].x][top[i].y]=0;

     top[i].c = 1;

     i--;

     top[i].c += 1;

}

}while(1);

}