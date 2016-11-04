#include<stdio.h>

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
//
//中序遍历
//后序遍历
//输出二叉树中的节点
//输出二叉树的叶子结点
//统计叶子结点数目
//求二叉树高度
//按树状打印二叉树
//建立二叉树，由结点遍历序列恢复
//先序＋中序
//中序＋后序
//由扩展的结点序列恢复
//按层遍历二叉树
