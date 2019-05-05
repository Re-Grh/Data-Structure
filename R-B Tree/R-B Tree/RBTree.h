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
	// 设置x的右孩子为y
	RBTNode<T> *y = x->right;

	// 将 “y的左孩子” 设为 “x的右孩子”；
	// 如果y的左孩子非空，将 “x” 设为 “y的左孩子的父亲”
	x->right = y->left;
	if (y->left != NULL)
		y->left->parent = x;

	// 将 “x的父亲” 设为 “y的父亲”
	y->parent = x->parent;

	if (x->parent == NULL)
	{
		root = y;            // 如果 “x的父亲” 是空节点，则将y设为根节点
	}
	else
	{
		if (x->parent->left == x)
			x->parent->left = y;    // 如果 x是它父节点的左孩子，则将y设为“x的父节点的左孩子”
		else
			x->parent->right = y;    // 如果 x是它父节点的左孩子，则将y设为“x的父节点的左孩子”
	}

	// 将 “x” 设为 “y的左孩子”
	y->left = x;
	// 将 “x的父节点” 设为 “y”
	x->parent = y;
}
template <class T>
void RBTree<T>::rightRotate(RBTNode<T>* &root, RBTNode<T>* y)
{
	// 设置x是当前节点的左孩子。
	RBTNode<T> *x = y->left;

	// 将 “x的右孩子” 设为 “y的左孩子”；
	// 如果"x的右孩子"不为空的话，将 “y” 设为 “x的右孩子的父亲”
	y->left = x->right;
	if (x->right != NULL)
		x->right->parent = y;

	// 将 “y的父亲” 设为 “x的父亲”
	x->parent = y->parent;

	if (y->parent == NULL)
	{
		root = x;            // 如果 “y的父亲” 是空节点，则将x设为根节点
	}
	else
	{
		if (y == y->parent->right)
			y->parent->right = x;    // 如果 y是它父节点的右孩子，则将x设为“y的父节点的右孩子”
		else
			y->parent->left = x;    // (y是它父节点的左孩子) 将x设为“x的父节点的左孩子”
	}

	// 将 “y” 设为 “x的右孩子”
	x->right = y;

	// 将 “y的父节点” 设为 “x”
	y->parent = x;
}
template <class T>
void RBTree<T>::insert(T key)
{
	RBTNode<T> *y = NULL;
	RBTNode<T> *x = mRoot;
	RBTNode<T> *node = new  RBTNode<T>(key, BLACK, NULL, NULL, NULL);
	// 1. 将红黑树当作一颗二叉查找树，将节点添加到二叉查找树中。
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

	// 2. 设置节点的颜色为红色
	node->color = RED;

	// 3. 将它重新修正为一颗二叉查找树
	insertFixUp(mRoot, node);
}
template <class T>
void RBTree<T>::insert(T key,char a[])
{
	RBTNode<T> *y = NULL;
	RBTNode<T> *x = mRoot;
	RBTNode<T> *node = new  RBTNode<T>(key, BLACK, NULL, NULL, NULL);
	node->w=a;
	// 1. 将红黑树当作一颗二叉查找树，将节点添加到二叉查找树中。
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

	// 2. 设置节点的颜色为红色
	node->color = RED;

	// 3. 将它重新修正为一颗二叉查找树
	insertFixUp(mRoot, node);
}
template <class T>
void RBTree<T>::insertFixUp(RBTNode<T>* &root, RBTNode<T>* node)
{
	RBTNode<T> *parent, *gparent;

	// 若“父节点存在，并且父节点的颜色是红色”
	while ((parent = node->parent) && parent->color==RED)
	{
		gparent = parent->parent;

		//若“父节点”是“祖父节点的左孩子”
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

			//叔叔是黑色，且当前节点是右孩子
			if (parent->right == node)
			{
				RBTNode<T> *tmp;
				leftRotate(root, parent);
				tmp = parent;
				parent = node;
				node = tmp;
			}

			//叔叔是黑色，且当前节点是左孩子。
			parent->color = BLACK;
			gparent->color = RED;
			rightRotate(root, gparent);
		}
		else//若“z的父节点”是“z的祖父节点的右孩子”
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
			//叔叔是黑色，且当前节点是左孩子
			if (parent->left == node)
			{
				RBTNode<T> *tmp;
				rightRotate(root, parent);
				tmp = parent;
				parent = node;
				node = tmp;
			}

			// 叔叔是黑色，且当前节点是右孩子。
			parent->color = BLACK;
			gparent->color = RED;
			leftRotate(root, gparent);
		}
	}

	// 将根节点设为黑色
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
		cout << "已删除节点" << key << endl;
		RBTNode<T> *child, *parent;
		RBTColor color;
		if ((node->left != NULL) && (node->right != NULL))
		{
			// 被删节点的后继节点。(称为"取代节点")
			// 用它来取代"被删节点"的位置，然后再将"被删节点"去掉。
			RBTNode<T> *replace = node;

			// 获取后继节点
			replace = replace->right;
			while (replace->left != NULL)
				replace = replace->left;

			// "node节点"不是根节点(只有根节点不存在父节点)
			if (node->parent)
			{
				if (node->parent->left == node)
					node->parent->left = replace;
				else
					node->parent->right = replace;
			}
			else
				// "node节点"是根节点，更新根节点。
				mRoot = replace;

			// child是"取代节点"的右孩子，也是需要"调整的节点"。
			// "取代节点"肯定不存在左孩子！因为它是一个后继节点。
			child = replace->right;
			parent = replace->parent;
			// 保存"取代节点"的颜色
			color = replace->color;

			// "被删除节点"是"它的后继节点的父节点"
			if (parent == node)
			{
				parent = replace;
			}
			else
			{
				// child不为空
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
		// 保存"取代节点"的颜色
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
	else cout << "未找到结点" << endl;
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
				//x的兄弟w是红色的  
				other->color = BLACK;
				parent->color=RED;
				leftRotate(root, parent);
				other = parent->right;
			}
			if ((!other->left || other->left->color==BLACK) &&
				(!other->right || other->right->color==BLACK))
			{
				//x的兄弟w是黑色，且w的俩个孩子也都是黑色的  
				other->color=RED;
				node = parent;
				parent = node->parent;
			}
			else
			{
				if (!other->right || other->right->color==BLACK)
				{
					//x的兄弟w是黑色的，并且w的左孩子是红色，右孩子为黑色。  
					other->left->color=BLACK;
					other->color=RED;
					rightRotate(root, other);
					other = parent->right;
				}
				//x的兄弟w是黑色的；并且w的右孩子是红色的，左孩子任意颜色。
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
				//x的兄弟w是红色的  
				other->color = BLACK;
				parent->color = RED;
				rightRotate(root, parent);
				other = parent->left;
			}
			if ((!other->left || other->left->color == BLACK) &&
				(!other->right || other->right->color == BLACK))
			{
				//x的兄弟w是黑色，且w的俩个孩子也都是黑色的  
				other->color=RED;
				node = parent;
				parent = node->parent;
			}
			else
			{
				if (!other->left || other->left->color==BLACK)
				{
					//x的兄弟w是黑色的，并且w的左孩子是红色，右孩子为黑色。  
					other->right->color = BLACK;
					other->color = RED;
					leftRotate(root, other);
					other = parent->left;
				}
				//x的兄弟w是黑色的；并且w的右孩子是红色的，左孩子任意颜色。
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
		cout << "R-B Tree 创建如下:" << endl;
		RBTNode<T>* Q[300];                      /*结点指针队列*/
		int front = 0, rear = 0, i = 1, j = 0, k = 1, n, flag = 0;
		if (mRoot != NULL) Q[++rear] = mRoot;
		while (1)
		{
			RBTNode<T>* tmp = Q[++front];
			if (i == pow(2, j))                /*按2的指数每行打印*/
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
			if (tmp != NULL)                 /*父结点不空即可入队*/
			{
				Q[++rear] = tmp->left;
				i++;
				Q[++rear] = tmp->right;
				i++;
			}
			else{                            /*定义空指针儿子为空*/
				Q[rear + 1] = NULL;
				Q[rear + 2] = NULL;
				rear += 2;
				i += 2;
			}
			for (n = front; n <= rear; n++)   /*遍历队列直到队列内部均为NULL终止循环*/
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