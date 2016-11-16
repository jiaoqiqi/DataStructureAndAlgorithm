
#include<stdio.h>
#include<stdlib.h>
typedef char DataType;

typedef struct Node{
	DataType data;
	struct Node* lChild;
	struct Node* rChild;
}BiNode,*BiTree;

int depth=0;
void PreTreeDepth(BiTree root,int h){
	if(root != NULL){
		if(h>depth)
			depth = h;
		PreTreeDepth(root -> lChild,h+1);
		PreTreeDepth(root -> rChild, h+1);
	}
} 

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

void PrintAtLevel(BiTree T,int level)
  {
      // 空树或层级不合理
      if (NULL == T || level < 1 )
          return;
  
      if (1 == level)
      {
      	printf("%c",T->data );
        return;
     }
 
     // 左子树的 level - 1 级
     PrintAtLevel(T->lChild,  level - 1);
 
     // 右子树的 level - 1 级
     PrintAtLevel(T->rChild, level - 1);
 }
 
 
 void LevelTraverse(BiTree T)
 {
     if (NULL == T)
         return;
 
 
     int i;
     for (i = 1; i <= depth+1; i++)
     {
         PrintAtLevel(T, i);
         
     }
 }   

int main(){
 	BiTree T;
	Creat_BiTree(&T);
	PreTreeDepth(T,0);
	LevelTraverse(T);

 }          