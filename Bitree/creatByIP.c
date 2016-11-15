#include<stdio.h>
#include<string.h>
#include<stdlib.h>
typedef char DataType;

typedef struct Node{
	DataType data;
	struct Node* lChild;
	struct Node* rChild;
}BiNode,*BiTree;

BiNode *CreatByIP(char *in,char *post,int n){
	BiNode *s;
	int pos;
	char *p;
	if(n<=0)
		return NULL;
	s = (BiNode *)malloc(sizeof(BiNode));
	s->data=*(post+n-1);
    for(p=in;p<in+n;p++)
    	if(*p==*(post+n-1))
			break;
 	pos=p-in;
 	s->lChild=CreatByIP(in,post,pos);
 	s->rChild=CreatByIP(p+1,post+pos,n-pos-1);
 	return s;
}

void PreOrder(BiTree root){
    if(root != NULL){
        printf("%c",root->data);
        PreOrder(root -> lChild);
        PreOrder(root -> rChild);
    }
}


void main(){
	char pre[50];
	char in[50];
	int n;
	gets(pre);
	gets(in);
	n=strlen(pre);
	BiTree T=CreatByIP(pre,in,n);
	PreOrder(T);
}