#ifndef _RED_BLACK_TREE_HPP_
#define _RED_BLACK_TREE_HPP_ 

#include <iomanip>
#include <iostream>
#include<math.h>
#include <string>
using namespace std;
enum RBTColor{ RED, BLACK };
template <class T>
class RBTNode{
public:
	RBTColor color;   
	T key;         
	string w;
	RBTNode *left;  
	RBTNode *right;   
	RBTNode *parent; 
	RBTNode() : key(0), color(RED), parent(NULL), left(NULL), right(NULL) {}
	RBTNode(T value, RBTColor c, RBTNode *p, RBTNode *l, RBTNode *r) :
		key(value), color(c), parent(p), left(l), right(r){}
};

template <class T>
class RBTree {
private:
	RBTNode<T> *mRoot;   
public:
	RBTree();
	~RBTree();
	void insert(T key);
	void insert(T key,char a[]);
	void remove(T key);
	RBTNode<T>* search(T key);
	void print();
private:
	void leftRotate(RBTNode<T>* &root, RBTNode<T>* x);
	void rightRotate(RBTNode<T>* &root, RBTNode<T>* y);
	void insertFixUp(RBTNode<T>* &root, RBTNode<T>* node);
	RBTNode<T>* search(RBTNode<T>* x, T key) const;
	void removeFixUp(RBTNode<T>* &root, RBTNode<T> *node, RBTNode<T> *parent);
};

template <class T>
RBTree<T>::RBTree()
{
	mRoot = NULL;
}
template <class T>
void RBTree<T>::leftRotate(RBTNode<T>* &root, RBTNode<T>* x)
{
	// ����x���Һ���Ϊy
	RBTNode<T> *y = x->right;

	// �� ��y�����ӡ� ��Ϊ ��x���Һ��ӡ���
	// ���y�����ӷǿգ��� ��x�� ��Ϊ ��y�����ӵĸ��ס�
	x->right = y->left;
	if (y->left != NULL)
		y->left->parent = x;

	// �� ��x�ĸ��ס� ��Ϊ ��y�ĸ��ס�
	y->parent = x->parent;

	if (x->parent == NULL)
	{
		root = y;            // ��� ��x�ĸ��ס� �ǿսڵ㣬��y��Ϊ���ڵ�
	}
	else
	{
		if (x->parent->left == x)
			x->parent->left = y;    // ��� x�������ڵ�����ӣ���y��Ϊ��x�ĸ��ڵ�����ӡ�
		else
			x->parent->right = y;    // ��� x�������ڵ�����ӣ���y��Ϊ��x�ĸ��ڵ�����ӡ�
	}

	// �� ��x�� ��Ϊ ��y�����ӡ�
	y->left = x;
	// �� ��x�ĸ��ڵ㡱 ��Ϊ ��y��
	x->parent = y;
}
template <class T>
void RBTree<T>::rightRotate(RBTNode<T>* &root, RBTNode<T>* y)
{
	// ����x�ǵ�ǰ�ڵ�����ӡ�
	RBTNode<T> *x = y->left;

	// �� ��x���Һ��ӡ� ��Ϊ ��y�����ӡ���
	// ���"x���Һ���"��Ϊ�յĻ����� ��y�� ��Ϊ ��x���Һ��ӵĸ��ס�
	y->left = x->right;
	if (x->right != NULL)
		x->right->parent = y;

	// �� ��y�ĸ��ס� ��Ϊ ��x�ĸ��ס�
	x->parent = y->parent;

	if (y->parent == NULL)
	{
		root = x;            // ��� ��y�ĸ��ס� �ǿսڵ㣬��x��Ϊ���ڵ�
	}
	else
	{
		if (y == y->parent->right)
			y->parent->right = x;    // ��� y�������ڵ���Һ��ӣ���x��Ϊ��y�ĸ��ڵ���Һ��ӡ�
		else
			y->parent->left = x;    // (y�������ڵ������) ��x��Ϊ��x�ĸ��ڵ�����ӡ�
	}

	// �� ��y�� ��Ϊ ��x���Һ��ӡ�
	x->right = y;

	// �� ��y�ĸ��ڵ㡱 ��Ϊ ��x��
	y->parent = x;
}
template <class T>
void RBTree<T>::insert(T key)
{
	RBTNode<T> *y = NULL;
	RBTNode<T> *x = mRoot;
	RBTNode<T> *node = new  RBTNode<T>(key, BLACK, NULL, NULL, NULL);
	// 1. �����������һ�Ŷ�������������ڵ���ӵ�����������С�
	while (x != NULL)
	{
		y = x;
		if (node->key < x->key)
			x = x->left;
		else
			x = x->right;
	}

	node->parent = y;
	if (y != NULL)
	{
		if (node->key < y->key)
			y->left = node;
		else
			y->right = node;
	}
	else
		mRoot = node;

	// 2. ���ýڵ����ɫΪ��ɫ
	node->color = RED;

	// 3. ������������Ϊһ�Ŷ��������
	insertFixUp(mRoot, node);
}
template <class T>
void RBTree<T>::insert(T key,char a[])
{
	RBTNode<T> *y = NULL;
	RBTNode<T> *x = mRoot;
	RBTNode<T> *node = new  RBTNode<T>(key, BLACK, NULL, NULL, NULL);
	node->w=a;
	// 1. �����������һ�Ŷ�������������ڵ���ӵ�����������С�
	while (x != NULL)
	{
		y = x;
		if (node->key < x->key)
			x = x->left;
		else
			x = x->right;
	}

	node->parent = y;
	if (y != NULL)
	{
		if (node->key < y->key)
			y->left = node;
		else
			y->right = node;
	}
	else
		mRoot = node;

	// 2. ���ýڵ����ɫΪ��ɫ
	node->color = RED;

	// 3. ������������Ϊһ�Ŷ��������
	insertFixUp(mRoot, node);
}
template <class T>
void RBTree<T>::insertFixUp(RBTNode<T>* &root, RBTNode<T>* node)
{
	RBTNode<T> *parent, *gparent;

	// �������ڵ���ڣ����Ҹ��ڵ����ɫ�Ǻ�ɫ��
	while ((parent = node->parent) && parent->color==RED)
	{
		gparent = parent->parent;

		//�������ڵ㡱�ǡ��游�ڵ�����ӡ�
		if (parent == gparent->left)
		{
			RBTNode<T> *uncle = gparent->right;
			if (uncle && uncle->color==RED)
			{
				uncle->color = BLACK;
				parent->color = BLACK;
				gparent->color = RED;
				node = gparent;
				continue;
			}

			//�����Ǻ�ɫ���ҵ�ǰ�ڵ����Һ���
			if (parent->right == node)
			{
				RBTNode<T> *tmp;
				leftRotate(root, parent);
				tmp = parent;
				parent = node;
				node = tmp;
			}

			//�����Ǻ�ɫ���ҵ�ǰ�ڵ������ӡ�
			parent->color = BLACK;
			gparent->color = RED;
			rightRotate(root, gparent);
		}
		else//����z�ĸ��ڵ㡱�ǡ�z���游�ڵ���Һ��ӡ�
		{
			RBTNode<T> *uncle = gparent->left;
			if (uncle && uncle->color==RED)
			{
				uncle->color = BLACK;
				parent->color = BLACK;
				gparent->color = RED;
				node = gparent;
				continue;
			}
			//�����Ǻ�ɫ���ҵ�ǰ�ڵ�������
			if (parent->left == node)
			{
				RBTNode<T> *tmp;
				rightRotate(root, parent);
				tmp = parent;
				parent = node;
				node = tmp;
			}

			// �����Ǻ�ɫ���ҵ�ǰ�ڵ����Һ��ӡ�
			parent->color = BLACK;
			gparent->color = RED;
			leftRotate(root, gparent);
		}
	}

	// �����ڵ���Ϊ��ɫ
	root->color = BLACK;
}
template <class T>
RBTNode<T>* RBTree<T>::search(RBTNode<T>* x, T key) const
{
	if (x == NULL || x->key == key)
		return x;

	if (key < x->key)
		return search(x->left, key);
	else
		return search(x->right, key);
}

template <class T>
RBTNode<T>* RBTree<T>::search(T key)
{
	return search(mRoot, key);
}

template <class T>
void RBTree<T>::remove(T key)
{
	RBTNode<T> *node;
	if ((node = search(mRoot, key)) != NULL)
	{
		cout << "��ɾ���ڵ�" << key << endl;
		RBTNode<T> *child, *parent;
		RBTColor color;
		if ((node->left != NULL) && (node->right != NULL))
		{
			// ��ɾ�ڵ�ĺ�̽ڵ㡣(��Ϊ"ȡ���ڵ�")
			// ������ȡ��"��ɾ�ڵ�"��λ�ã�Ȼ���ٽ�"��ɾ�ڵ�"ȥ����
			RBTNode<T> *replace = node;

			// ��ȡ��̽ڵ�
			replace = replace->right;
			while (replace->left != NULL)
				replace = replace->left;

			// "node�ڵ�"���Ǹ��ڵ�(ֻ�и��ڵ㲻���ڸ��ڵ�)
			if (node->parent)
			{
				if (node->parent->left == node)
					node->parent->left = replace;
				else
					node->parent->right = replace;
			}
			else
				// "node�ڵ�"�Ǹ��ڵ㣬���¸��ڵ㡣
				mRoot = replace;

			// child��"ȡ���ڵ�"���Һ��ӣ�Ҳ����Ҫ"�����Ľڵ�"��
			// "ȡ���ڵ�"�϶����������ӣ���Ϊ����һ����̽ڵ㡣
			child = replace->right;
			parent = replace->parent;
			// ����"ȡ���ڵ�"����ɫ
			color = replace->color;

			// "��ɾ���ڵ�"��"���ĺ�̽ڵ�ĸ��ڵ�"
			if (parent == node)
			{
				parent = replace;
			}
			else
			{
				// child��Ϊ��
				if (child)
					child->parent= parent;
				parent->left = child;

				replace->right = node->right;
				node->right->parent= replace;
			}

			replace->parent = node->parent;
			replace->color = node->color;
			replace->left = node->left;
			node->left->parent = replace;

			if (color == BLACK)
				removeFixUp(mRoot, child, parent);

			delete node;
			return;
		}

		if (node->left != NULL)
			child = node->left;
		else
			child = node->right;

		parent = node->parent;
		// ����"ȡ���ڵ�"����ɫ
		color = node->color;

		if (child)
			child->parent = parent;

		if (parent)
		{
			if (parent->left == node)
				parent->left = child;
			else
				parent->right = child;
		}
		else
			mRoot = child;

		if (color == BLACK)
			removeFixUp(mRoot, child, parent);
		delete node;
	}
	else cout << "δ�ҵ����" << endl;
}
template <class T>
void RBTree<T>::removeFixUp(RBTNode<T>* &root, RBTNode<T> *node, RBTNode<T> *parent)
{
	RBTNode<T> *other;

	while ((!node || node->color==BLACK) && node != root)
	{
		if (parent->left == node)
		{
			other = parent->right;
			if (other->color==RED)
			{
				//x���ֵ�w�Ǻ�ɫ��  
				other->color = BLACK;
				parent->color=RED;
				leftRotate(root, parent);
				other = parent->right;
			}
			if ((!other->left || other->left->color==BLACK) &&
				(!other->right || other->right->color==BLACK))
			{
				//x���ֵ�w�Ǻ�ɫ����w����������Ҳ���Ǻ�ɫ��  
				other->color=RED;
				node = parent;
				parent = node->parent;
			}
			else
			{
				if (!other->right || other->right->color==BLACK)
				{
					//x���ֵ�w�Ǻ�ɫ�ģ�����w�������Ǻ�ɫ���Һ���Ϊ��ɫ��  
					other->left->color=BLACK;
					other->color=RED;
					rightRotate(root, other);
					other = parent->right;
				}
				//x���ֵ�w�Ǻ�ɫ�ģ�����w���Һ����Ǻ�ɫ�ģ�����������ɫ��
				other->color=parent->color;
				parent->color = BLACK;
				other->right->color=BLACK;
				leftRotate(root, parent);
				node = root;
				break;
			}
		}
		else
		{
			other = parent->left;
			if (other->color==RED)
			{
				//x���ֵ�w�Ǻ�ɫ��  
				other->color = BLACK;
				parent->color = RED;
				rightRotate(root, parent);
				other = parent->left;
			}
			if ((!other->left || other->left->color == BLACK) &&
				(!other->right || other->right->color == BLACK))
			{
				//x���ֵ�w�Ǻ�ɫ����w����������Ҳ���Ǻ�ɫ��  
				other->color=RED;
				node = parent;
				parent = node->parent;
			}
			else
			{
				if (!other->left || other->left->color==BLACK)
				{
					//x���ֵ�w�Ǻ�ɫ�ģ�����w�������Ǻ�ɫ���Һ���Ϊ��ɫ��  
					other->right->color = BLACK;
					other->color = RED;
					leftRotate(root, other);
					other = parent->left;
				}
				//x���ֵ�w�Ǻ�ɫ�ģ�����w���Һ����Ǻ�ɫ�ģ�����������ɫ��
				other->color = parent->color;
				parent->color = BLACK;
				other->left->color = BLACK;
				rightRotate(root, parent);
				node = root;
				break;
			}
		}
	}
	if (node) node->color=BLACK;
}
template <class T>
void RBTree<T>::print()
{
		cout << "R-B Tree ��������:" << endl;
		RBTNode<T>* Q[300];                      /*���ָ�����*/
		int front = 0, rear = 0, i = 1, j = 0, k = 1, n, flag = 0;
		if (mRoot != NULL) Q[++rear] = mRoot;
		while (1)
		{
			RBTNode<T>* tmp = Q[++front];
			if (i == pow(2, j))                /*��2��ָ��ÿ�д�ӡ*/
			{
				for (k; k <= rear; k++)
				{
					if (Q[k] != NULL) cout << Q[k]->key << "   ";
					else  cout << "N   ";
				}
				j++;
				i = 0;
				cout << endl;
			}
			if (tmp != NULL)                 /*����㲻�ռ������*/
			{
				Q[++rear] = tmp->left;
				i++;
				Q[++rear] = tmp->right;
				i++;
			}
			else{                            /*�����ָ�����Ϊ��*/
				Q[rear + 1] = NULL;
				Q[rear + 2] = NULL;
				rear += 2;
				i += 2;
			}
			for (n = front; n <= rear; n++)   /*��������ֱ�������ڲ���ΪNULL��ֹѭ��*/
			{
				if (Q[n] != NULL)
				{
					flag = 1;
					break;
				}
			}
			if (flag == 0) break;
			flag = 0;
		}
}
#endif