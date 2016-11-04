#include<stdio.h>
#include<stdlib.h>

typedef char DataType;
//创建二叉树
typedef struct Node{
	DataType data;
	struct Node *Lchild;
	struct Node *Rchild;
}BiTNode,*BiTree;
//先序遍历算法
void PreOrder(BiTree root){
    if(root != NULL){
        printf("%c",root->data);
        PreOrder(root -> Lchild);
        PreOrder(root -> Rchild);
    }
}

//中序遍历
void InOrder(BiTree root){
	if(root != NULL){
		InOrder(root -> Lchild);
		printf("%c",root->data);
		InOrder(root -> Rchild);
	}
}
//后序遍历
void PostOrder(BiTree root){
	if(root != NULL){
		PostOrder(root -> Lchild);
		PostOrder(root -> Rchild);
		Printf("%c",root -> data);
	}
}
//输出二叉树中的节点
void OutPut(BiTree root){
	if(root != NULL){
		printf("%c",root -> data);
		OutPut(root -> Lchild);
		OutPut(root -> Rchild);
	}
}
//输出二叉树的叶子结点
void OutPutLeaf(BiTree root){
	if(root != NULL){
		OutPutLeaf(root -> Lchild);
		if(root -> Lchild==NULL && root->Rchild==NULL)
			printf("%c", root->data);
		OutPutLeaf(root -> Rchild);
	}
}
//统计叶子结点数目
int LeafCount = 0;
void LeafNum(BiTree root){
	if(root != NULL){
		if(root->Lchild==NULL && root->Rchild==NULL){
			LeafCount++;
			LeafNum(root->Lchild);
			LeafNum(root->Rchild);
		}
	}
}
//求二叉树高度
int PostTreeDepth(BiTree root){
	int hl,hr,max;
	if(root != NULL){
		hl = PostTreeDepth(root -> Lchild);
		hr = PostTreeDepth(root -> Rchild);
		max = hl>hr?hl:hr;
		return max+1;
	}
	else
		return 0;
}

int depth=0;
void PreTreeDepth(BiTree root,int h){
	if(root != NULL){
		if(h>depth)
			depth = h;
		PreTreeDepth(root -> Lchild,h+1);
		PreTreeDepth(root -> Rchild, h+1);

	}
}

void LBPath(BiTree bt,char Path[],int pathlen){
	int i;
	if(bt != NULL){
		if(bt->Lchild == NULL && bt->Rchild==NULL){
			for(i=pathlen-1 ; i>=0 ; i--)
				printf("%c",path[i]);
			printf("\n");
		}
		else{
			path[pathlen] = bt->data;
			LBPath(bt->Lchild,path,pathlen+1);
			LBPath(bt->Rchild,path,pathlen+1);
		}
	}
}

//按树状打印二叉树
void PrintTree(BiTree root,int nLayer){
	if(root != NULL){
		PrintTree(root->Rchild,nLayer+1);
		for(int i=0 ; i<nLayer ; i++){
			printf(" ");
		printf("%c\n",root->data);
		PrintTree(root->Lchild,nLayer+1);	
		}
	}
}

//建立二叉树，由结点遍历序列恢复
//先序＋中序
BiTNode *CreatByPI(char *pre,char *in,int n){
	BiTNode *s;int pos;char *p;
	if(n<=0)
		return NULL;
	s = (BiTNode *)malloc(sizeof(BiTNode));
	s->data = *pre;
	for(p=in ; p<in+n ; p++)
		if(*p == *pre)
			break;
	pos = p-in;
	s->Lchild = CreatByPI(pre+1,in,pos);
	s->Rchild = CreatByPI(pre+pos+1,p+1,n-pos-1);
	return s;	
}
//中序＋后序
BiTNode *CreatByIP(char *in,char *post,int n){
	BiTNode *s,int pos;char *p;
	if(n<=0)
		return NULL;
	s = (BiTNode *)malloc(sizeof(BiTNode))
}
//由扩展的结点序列恢复
BiTree CretatBiTree(){
	char ch;
	BiTNode *s;
	ch = getchar();
	if(ch != '#'){
		return NULL
	}
	else{
			s = (BiTreeNode *)malloc(sizeof(BiTreeNode));
			s->data = ch;
			s->Lchild = CretatBiTree();
			s->Rchild = CretatBiTree();
			return s;

	}
}
//按层遍历二叉树
void LayerOrder(){
	SqQueue Q;
	InitQueue(Q);
	BiTNode *p;
	p = root;
	if(p==NULL)
		return ;
	EnQueue(Q,p);
	while(!IsEmpty(Q)){
		DeQueue(Q,q);
		printf("%c ",p->data );
		if(p->Lchild)
			EnQueue(Q,p->Lchild);
		if(p->Rchild)
			EnQueue(Q,p->Rchild);
	}
}


void main(){
	
}