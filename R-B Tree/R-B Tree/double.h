#include<stdio.h>
#include<stdlib.h>


typedef int KeyType;
typedef struct Node
{
	KeyType key;         
	struct Node * left;  
	struct Node * right; 
	struct Node * parent; 
}Node, *PNode;

void inseart(PNode * root, KeyType key)
{
	PNode p = (PNode)malloc(sizeof(Node));
	p->key = key;
	p->left = p->right = p->parent = NULL;
	if ((*root) == NULL){
		*root = p;
		return;
	}
	if ((*root)->left == NULL && (*root)->key > key){
		p->parent = (*root);
		(*root)->left = p;
		return;
	}
	if ((*root)->right == NULL && (*root)->key < key){
		p->parent = (*root);
		(*root)->right = p;
		return;
	}
	if ((*root)->key > key)
		inseart(&(*root)->left, key);
	else if ((*root)->key < key)
		inseart(&(*root)->right, key);
	else
		return;
}

PNode search(PNode root, KeyType key)
{
	if (root == NULL)
		return NULL;
	if (key > root->key) 
		return search(root->right, key);
	else if (key < root->key) 
		return search(root->left, key);
	else
		return root;
}

PNode searchMin(PNode root)
{
	if (root == NULL)
		return NULL;
	if (root->left == NULL)
		return root;
	else  
		return searchMin(root->left);
}
PNode searchMax(PNode root)
{
	if (root == NULL)
		return NULL;
	if (root->right == NULL)
		return root;
	else  
		return searchMax(root->right);
}

PNode searchPredecessor(PNode p)
{
	if (p == NULL)
		return p;
	//有左子树、左子树中最大的那个
	if (p->left)
		return searchMax(p->left);
	//无左子树,查找某个结点的右子树遍历完了
	else{
		if (p->parent == NULL)
			return NULL;
		//向上寻找前驱
		while (p){
			if (p->parent->right == p)
				break;
			p = p->parent;
		}
		return p->parent;
	}
}

//查找某个结点的后继
PNode searchSuccessor(PNode p)
{
	//空树
	if (p == NULL)
		return p;
	//有右子树、右子树中最小的那个
	if (p->right)
		return searchMin(p->right);
	//无右子树,查找某个结点的左子树遍历完了
	else{
		if (p->parent == NULL)
			return NULL;
		//向上寻找后继
		while (p){
			if (p->parent->left == p)
				break;
			p = p->parent;
		}
		return p->parent;
	}
}

int deleteNode(PNode* root, KeyType key)
{
	PNode q;
	//查找到要删除的结点
	PNode p = search(*root, key);
	KeyType temp;    //暂存后继结点的值
	//没查到此关键字
	if (!p)
		return 0;
	if (p->left == NULL && p->right == NULL){
		//只有一个元素，删完之后变成一颗空树
		if (p->parent == NULL){
			free(p);
			(*root) = NULL;
		}
		else{
			//删除的结点是父节点的左孩子
			if (p->parent->left == p)
				p->parent->left = NULL;
			else  //删除的结点是父节点的右孩子
				p->parent->right = NULL;
			free(p);
		}
	}
	else if (p->left && !(p->right)){
		p->left->parent = p->parent;
		//如果删除是父结点，要改变父节点指针
		if (p->parent == NULL)
			*root = p->left;
		//删除的结点是父节点的左孩子
		else if (p->parent->left == p)
			p->parent->left = p->left;
		else //删除的结点是父节点的右孩子
			p->parent->right = p->left;
		free(p);
	}
	else if (p->right && !(p->left)){
		p->right->parent = p->parent;
		//如果删除是父结点，要改变父节点指针
		if (p->parent == NULL)
			*root = p->right;
		//删除的结点是父节点的左孩子
		else if (p->parent->left == p)
			p->parent->left = p->right;
		else //删除的结点是父节点的右孩子
			p->parent->right = p->right;
		free(p);
	}
	else{
		//找到要删除结点的后继
		q = searchSuccessor(p);
		temp = q->key;
		//删除后继结点
		deleteNode(root, q->key);
		p->key = temp;
	}
	return 1;
}

void create(PNode* root, KeyType *keyArray, int length)
{
	int i;
	//逐个结点插入二叉树中
	for (i = 0; i<length; i++)
		inseart(root, keyArray[i]);
}
