#include<stdio.h>
#include<string.h>
#include<stdlib.h>
typedef char DataType;

typedef struct Node{
	DataType data;
	struct Node* lChild;
	struct Node* rChild;
}BiNode,*BiTree;

BiNode *CreatByPI(char *pre,char *in,int n){
	BiNode *s;int pos;char *p;
	if(n<=0)
		return NULL;
	s = (BiNode *)malloc(sizeof(BiNode));
	s->data = *pre;
	for(p=in ; p<in+n ; p++)
		if(*p == *pre)
			break;
	pos = p-in;
	s->lChild = CreatByPI(pre+1,in,pos);
	s->rChild = CreatByPI(pre+pos+1,p+1,n-pos-1);
	return s;	
}

void PostOrder(BiTree root){
	if(root != NULL){
		PostOrder(root -> lChild);
		PostOrder(root -> rChild);
		printf("%c",root -> data);
	}
}

void main(){
	char pre[50];
	char in[50];
	int n;
	gets(pre);
	gets(in);
	n=strlen(pre);
	BiTree T=CreatByPI(pre,in,n);
	PostOrder(T);
}