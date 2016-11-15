#include<stdio.h>
#include<stdlib.h>
typedef char DataType;

typedef struct Node{
	DataType data;
	struct Node* lChild;
	struct Node* rChild;
}BiNode,*BiTree;

void Creat_BiTree(BiTree *T){
	char ch;
	scanf("%c",&ch);
	if(ch == '#')
		*T=NULL;
	else{
		*T = (BiTree)malloc(sizeof(BiNode));
		(*T)->data = ch;
		Creat_BiTree(&((*T)->lChild));
		Creat_BiTree(&((*T)->rChild));
	}
}

void LeavePath(BiTree bt,char path[],int pathlen)
{
	int i;
	if(bt != NULL)
	{
		if(bt->lChild == NULL && bt->rChild == NULL)
		{
			printf("%c:",bt->data);
			for(i = 0;i<pathlen;i++)
			{
				printf("%c",path[i] );
			}
			printf("\n");
		}
		else
		{
			path[pathlen] = bt->data;
			LeavePath(bt->lChild,path,pathlen+1);
			LeavePath(bt->rChild,path,pathlen+1);
		}
	}
}

void main(){
	BiTree T;
	Creat_BiTree(&T);
	char path[20];
	LeavePath(T,path,0);

}
