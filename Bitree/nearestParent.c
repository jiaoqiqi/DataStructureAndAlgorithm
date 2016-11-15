#include<stdio.h>
#include<stdlib.h>
#define N 20

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

//TreePath == 0
void LRPath(BiTree root,char path[],int pathlen)
{
	int i;
	if(root != NULL)
	{
		if(root->lChild == NULL && root->rChild == NULL)
		{
			printf("%c:",root->data);
			for(i = 0;i<pathlen;i++)
			{
				printf("%c",path[i] );
			}
			printf("\n");
		}
		else
		{
			path[pathlen] = root->data;
			LRPath(root->lChild,path,pathlen+1);
			LRPath(root->rChild,path,pathlen+1);
		}
	}
}
int main()
{
	BiTree T;
	Creat_BiTree(&T);
	char path[N];
	LRPath(T,path,0);
	return 0;
}