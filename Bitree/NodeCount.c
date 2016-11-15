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

int LeafCount = 0;
void LeafNum(BiTree root){
	if(root != NULL){
		if(root->lChild==NULL && root->rChild==NULL)
			LeafCount++;
		LeafNum(root->lChild);
		LeafNum(root->rChild);
		
	}
}

int OneDepth = 0;
void OneNum(BiTree root){
	if(root != NULL){
		if(((root->lChild)==NULL && (root->rChild)!=NULL)|| ((root->rChild)==NULL && (root->lChild)!=NULL))
			OneDepth++;
		OneNum(root->lChild);
		OneNum(root->rChild);
	}
}

int TwoDepth = 0;
void TwoNum(BiTree root){
	if(root != NULL){
		if(root->lChild!=NULL && root->rChild!=NULL)
			TwoDepth++;
		TwoNum(root->lChild);
		TwoNum(root->rChild);
		
	}
}


void OutPutLeaf(BiTree root){
	if(root != NULL){
		OutPutLeaf(root -> lChild);
		if(root -> lChild==NULL && root->rChild==NULL)
			printf("%c", root->data);
		OutPutLeaf(root -> rChild);
	}
}
void main(){
	BiTree T;
	Creat_BiTree(&T);
	LeafNum(T);
	printf("%d ",LeafCount );
	OneNum(T);
	printf("%d ",OneDepth );
	TwoNum(T);
	printf("%d\n",TwoDepth );
	OutPutLeaf(T);
}
