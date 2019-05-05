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
	//�����������������������Ǹ�
	if (p->left)
		return searchMax(p->left);
	//��������,����ĳ��������������������
	else{
		if (p->parent == NULL)
			return NULL;
		//����Ѱ��ǰ��
		while (p){
			if (p->parent->right == p)
				break;
			p = p->parent;
		}
		return p->parent;
	}
}

//����ĳ�����ĺ��
PNode searchSuccessor(PNode p)
{
	//����
	if (p == NULL)
		return p;
	//��������������������С���Ǹ�
	if (p->right)
		return searchMin(p->right);
	//��������,����ĳ��������������������
	else{
		if (p->parent == NULL)
			return NULL;
		//����Ѱ�Һ��
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
	//���ҵ�Ҫɾ���Ľ��
	PNode p = search(*root, key);
	KeyType temp;    //�ݴ��̽���ֵ
	//û�鵽�˹ؼ���
	if (!p)
		return 0;
	if (p->left == NULL && p->right == NULL){
		//ֻ��һ��Ԫ�أ�ɾ��֮����һ�ſ���
		if (p->parent == NULL){
			free(p);
			(*root) = NULL;
		}
		else{
			//ɾ���Ľ���Ǹ��ڵ������
			if (p->parent->left == p)
				p->parent->left = NULL;
			else  //ɾ���Ľ���Ǹ��ڵ���Һ���
				p->parent->right = NULL;
			free(p);
		}
	}
	else if (p->left && !(p->right)){
		p->left->parent = p->parent;
		//���ɾ���Ǹ���㣬Ҫ�ı丸�ڵ�ָ��
		if (p->parent == NULL)
			*root = p->left;
		//ɾ���Ľ���Ǹ��ڵ������
		else if (p->parent->left == p)
			p->parent->left = p->left;
		else //ɾ���Ľ���Ǹ��ڵ���Һ���
			p->parent->right = p->left;
		free(p);
	}
	else if (p->right && !(p->left)){
		p->right->parent = p->parent;
		//���ɾ���Ǹ���㣬Ҫ�ı丸�ڵ�ָ��
		if (p->parent == NULL)
			*root = p->right;
		//ɾ���Ľ���Ǹ��ڵ������
		else if (p->parent->left == p)
			p->parent->left = p->right;
		else //ɾ���Ľ���Ǹ��ڵ���Һ���
			p->parent->right = p->right;
		free(p);
	}
	else{
		//�ҵ�Ҫɾ�����ĺ��
		q = searchSuccessor(p);
		temp = q->key;
		//ɾ����̽��
		deleteNode(root, q->key);
		p->key = temp;
	}
	return 1;
}

void create(PNode* root, KeyType *keyArray, int length)
{
	int i;
	//����������������
	for (i = 0; i<length; i++)
		inseart(root, keyArray[i]);
}
