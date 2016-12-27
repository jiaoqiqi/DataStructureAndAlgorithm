#include <stdio.h>
#include <stdlib.h>
typedef char DateType;
typedef struct Node{
	DateType date;
	struct Node *LChild;
	struct Node *RChild;
}BiTNode,*BiTree;
void *createBiTree()
{
	char ch;
	BiTNode *root;
	ch = getchar();
	if(ch == '#')
		return NULL;
	else
	{
		root = (BiTree)malloc(sizeof(BiTNode));
		root->date = ch;
		root->LChild = createBiTree();
		root->RChild = createBiTree();
		return root;
	}
}

//visit
void PreOrder(BiTree root)
{
	if(root)
	{
		printf("%c",root->date);
		PreOrder(root->LChild);
		PreOrder(root->RChild);
	}
}
void InOrder(BiTree root)
{
	if(root)
	{
		InOrder(root->LChild);
		printf("%c",root->date);
		InOrder(root->RChild);
	}
}
void PostOrder(BiTree root)
{
	if(root)
	{
		PostOrder(root->LChild);
		PostOrder(root->RChild);
		printf("%c",root->date);
	}
}

//leafOutput
void leafOutput(BiTree root)
{
	if(root != NULL)
	{
		leafOutput(root->LChild);
		if(root->LChild == NULL && root->RChild == NULL)
		{
			printf("%c",root->date );
		}
		leafOutput(root->RChild);
	}
}

//leadCount
int leadCount = 0;
void LeafNum(BiTree root)
{
	if(root)
	{
		if(root->LChild == NULL && root->RChild == NULL)
			leadCount++;
		LeafNum(root->LChild);
		LeafNum(root->RChild);
	}
}

//TerrDepth  h = 1
int depth = 0;
int PostTreeDepth(BiTree root,int h)
{
	if(root)
	{
		if(h>depth)
			depth = h;
		PostTreeDepth(root->LChild,h+1);
		PostTreeDepth(root->RChild,h+1);
	}
}

//TreePath == 0
void LRPath(BiTree bt,char path[],int pathlen)
{
	int i;
	if(bt != NULL)
	{
		if(bt->LChild == NULL && bt->RChild == NULL)
		{
			for(i = pathlen-1; i>=0; i--)
			{
				printf("%c ",path[i] );
			}
			printf("\n");
		}
		else
		{
			path[pathlen] = bt->date;
			LRPath(bt->LChild,path,pathlen+1);
			LRPath(bt->RChild,path,pathlen+1);
		}
	}
}

//printTreeShape
void printTreeShape(BiTree root,int nLayer)
{
	int i = 0;
	if(root)
	{
		printTreeShape(root->RChild,nLayer+1);
		for(;i<nLayer;i++)
			printf(" ");
		printf("%c\n",root->date);
		printTreeShape(root->LChild,nLayer+1);
	}
}


int main()
{
	BiTree *root;
	root = createBiTree();
	PreOrder(root);
	printf("\n");
	InOrder(root); 
	printf("\n");
	PostOrder(root);
	
	return 0;
}
