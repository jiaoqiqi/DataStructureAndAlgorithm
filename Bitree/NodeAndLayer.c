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

int depth = 0;
int PostTreeDepth(BiTree root,int h)
{
	if(root)
	{
		if(h>depth)
			depth = h;
		printf("(%c,%d)",root->data,h);
		PostTreeDepth(root->lChild,h+1);
		PostTreeDepth(root->rChild,h+1);
	}
}

void main(){
	BiTree T;
	Creat_BiTree(&T);
	PostTreeDepth(T,1);
}