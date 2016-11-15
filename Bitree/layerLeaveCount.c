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

int depth=0;
void PreTreeDepth(BiTree root,int h){
	if(root != NULL){
		if(h>depth)
			depth = h;
		PreTreeDepth(root -> lChild,h+1);
		PreTreeDepth(root -> rChild, h+1);
	}
} 
int count=0;
void DepthLeave(BiTree root,int level)
{
	
	if(NULL==root || level <1)
		return;
	if(level==1){
		if(root->lChild==NULL && root->rChild==NULL){
			count ++;
		}
	}
	DepthLeave(root->lChild,level-1);
	DepthLeave(root->rChild,level-1);
}

int main(){
 	BiTree T;
	Creat_BiTree(&T);
	PreTreeDepth(T,1);
	int level;
	scanf("%d",&level);
	DepthLeave(T,level);
	printf("%d",count );
 }          