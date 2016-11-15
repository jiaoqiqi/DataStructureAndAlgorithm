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

void exchange(BiTree root){
	BiTree x;
	if(root){
		exchange(root->lChild);
		exchange(root->rChild);
		x=root->lChild;
		root->lChild = root->rChild;
		root->rChild = x;
	}

}

//先序遍历算法
void PreOrder(BiTree root){
    if(root != NULL){
        printf("%c",root->data);
        PreOrder(root -> lChild);
        PreOrder(root -> rChild);
    }
}

//中序遍历
void InOrder(BiTree root){
	if(root != NULL){
		InOrder(root -> lChild);
		printf("%c",root->data);
		InOrder(root -> rChild);
	}
}
//后序遍历
void PostOrder(BiTree root){
	if(root != NULL){
		PostOrder(root -> lChild);
		PostOrder(root -> rChild);
		printf("%c",root -> data);
	}
}

void main(){
	BiTree T;
	Creat_BiTree(&T);
	exchange(T);
	PreOrder(T);
	printf("\n");
	InOrder(T);
	printf("\n");
	PostOrder(T);
}