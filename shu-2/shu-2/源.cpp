#include <iostream>
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#pragma warning(disable:4996)
using namespace std;
//存有孩子结点索引的单链表结点
typedef struct CTNode
{
	int child;
	struct CTNode *next;
} CTNode, *Node;
//孩子链表结点（树结点）
typedef struct CTBox
{
	Node link;
	int data;
} CTBox, *Tree;
//森林结点
typedef struct ForestNode
{
	Tree tree;
	struct ForestNode *next;
} ForestNode, *Forest;
//森林链表的初始化操作
void InitFTree(Forest &fTree)
{
	fTree = (Forest)malloc(sizeof(ForestNode));
	fTree->next = NULL;
}
//森林链表的插入操作
void InsertFTree(Forest &fTree, Tree node)
{
	Forest t_node = fTree;
	Forest newnode = (Forest)malloc(sizeof(ForestNode));

	while (t_node->next != NULL)
	{
		t_node = t_node->next;
	}

	newnode->tree = node;
	t_node->next = newnode;
	newnode->next = NULL;
}
//表建立树链表
void GListToTree(Tree &tree, int &current_index, int parent_index)
{
	char ch;
	Node newnode;
	Node link = (Node)malloc(sizeof(CTNode));
	link->child = current_index;
	link->next = NULL;
	tree[parent_index].link = link;
	while (true)
	{
		scanf("%c", &ch);

		if (ch == '(')
		{
			parent_index = current_index;
			current_index++;
			scanf("%d", &tree[current_index].data);
			tree[current_index].link = NULL;

			GListToTree(tree, current_index, parent_index);
		}
		else if (ch == ',')
		{
			current_index++;
			scanf("%d", &tree[current_index].data);
			tree[current_index].link = NULL;

			newnode = (Node)malloc(sizeof(CTNode));
			newnode->child = current_index;
			newnode->next = NULL;
			link->next = newnode;
			link = link->next;
		}
		else
		{
			return;
		}
	}
}
//广义表组建立森林链表
void GListToFTree(Forest &fTree)
{
	char ch;
	int current_index, parent_index;
	Tree tree;
	scanf("%c", &ch);
	tree = (Tree)malloc(50 * sizeof(CTBox));
	while (ch != '#')
	{
		current_index = -1;
		current_index++;
		scanf("%d", &tree[current_index].data);
		tree[current_index].link = NULL;
		scanf("%c", &ch);

		if (ch != ')')
		{
			parent_index = current_index;
			current_index++;
			scanf("%d", &tree[current_index].data);
			tree[current_index].link = NULL;

 			GListToTree(tree, current_index, parent_index);
			scanf("%c", &ch);
		}

		InsertFTree(fTree, tree);
		scanf("%c", &ch);
	}
}

//二叉树结点
typedef struct BiTreeNode
{
	int data;
	struct BiTreeNode *lchild;
	struct BiTreeNode *rchild;
} BiTreeNode, *pBiTreeNode;
//二叉树
typedef struct BiTree
{
	pBiTreeNode tree;
} BiTree;
//二叉树初始化
void InitBiTree(BiTree &biTree)
{
	biTree.tree = NULL;
}
void Creat1BT(pBiTreeNode &T)     /*先序递归创建二叉树*/
{
	char ch;
	cin >> ch;
	if (ch == '#')
	{
		T = NULL;
	}
	else
	{
		T = new BiTreeNode;
		T->data = ch;
		Creat1BT(T->lchild);
		Creat1BT(T->rchild);
	}
}

//二叉树转化为树，是二叉树转化为森林的子函数
void BiTreeToTree(Tree &tree, pBiTreeNode &biTree,
	int &current_index, int parent_index)
{
	pBiTreeNode p_biTree = biTree->lchild;
	Node newnode;

	if (p_biTree != NULL)
	{
		current_index++;
		tree[current_index].data = p_biTree->data;
		tree[current_index].link = NULL;

		newnode = (Node)malloc(sizeof(CTNode));
		newnode->child = current_index;
		newnode->next = NULL;
		tree[parent_index].link = newnode;

		BiTreeToTree(tree, p_biTree, current_index, newnode->child);

		while (p_biTree->rchild != NULL)
		{
			p_biTree = p_biTree->rchild;

			current_index++;
			tree[current_index].data = p_biTree->data;
			tree[current_index].link = NULL;

			newnode->next = (Node)malloc(sizeof(CTNode));
			newnode = newnode->next;
			newnode->child = current_index;
			newnode->next = NULL;

			BiTreeToTree(tree, p_biTree, current_index, newnode->child);
		}
	}
}
//二叉树转化为森林
void BiTreetoFTree(Forest &fTree, pBiTreeNode &biTree)
{
	int current_index, parent_index;
	Tree newnode;
	pBiTreeNode p_biTree = biTree;

	do
	{
		newnode = (Tree)malloc(sizeof(CTBox)* 50);

		current_index = 0;
		parent_index = current_index;
		newnode[current_index].data = p_biTree->data;
		newnode[current_index].link = NULL;

		BiTreeToTree(newnode, p_biTree, current_index, parent_index);
		InsertFTree(fTree, newnode);

		p_biTree = p_biTree->rchild;
	} while (p_biTree != NULL);
}
//树转化为二叉树
void TreeToBiTree(Tree &tree, pBiTreeNode &biTree, int index)
{
	pBiTreeNode newnode = (pBiTreeNode)malloc(sizeof(BiTreeNode));
	newnode->data = tree[index].data;
	newnode->lchild = NULL;
	newnode->rchild = NULL;
	biTree = newnode;

	Node link = tree[index].link;
	pBiTreeNode tempNode = biTree;

	if (link != NULL)
	{
		TreeToBiTree(tree, tempNode->lchild, link->child);
		link = link->next;
		tempNode = tempNode->lchild;
		while (link != NULL)
		{
			TreeToBiTree(tree, tempNode->rchild, link->child);
			link = link->next;
			tempNode = tempNode->rchild;
		}
	}
}
//森林转化为二叉树
void FTreeToBiTree(Forest &fTree, BiTree &biTree)
{
	Forest p_fTree = fTree->next;
	pBiTreeNode p_biTree = biTree.tree;

	while (p_fTree != NULL)
	{
		if (biTree.tree == NULL)
		{
			TreeToBiTree(p_fTree->tree, biTree.tree, 0);
			p_biTree = biTree.tree;
		}
		else
		{
			TreeToBiTree(p_fTree->tree, p_biTree->rchild, 0);
			p_biTree = p_biTree->rchild;
		}
		p_fTree = p_fTree->next;
	}
}
//树转化为广义表
void TreeToGList(Tree &tree, int parent_index)
{
	Node p_treeLink = tree[parent_index].link;

	if (p_treeLink != NULL)
	{
		printf("(");
		printf("%d", tree[p_treeLink->child].data);
		TreeToGList(tree, p_treeLink->child);
		p_treeLink = p_treeLink->next;

		while (p_treeLink != NULL)
		{
			printf(",");
			printf("%d", tree[p_treeLink->child].data);
			TreeToGList(tree, p_treeLink->child);

			p_treeLink = p_treeLink->next;
		}

		printf(")");
	}
}
//森林转化为广义表
void FTreeToGList(Forest &fTree)
{
	int parent_index;
	Forest p_fTree = fTree->next;

	while (p_fTree != NULL)
	{
		parent_index = 0;

		printf("(");
		printf("%d", p_fTree->tree[0].data);
		TreeToGList(p_fTree->tree, parent_index);
		printf(")");

		p_fTree = p_fTree->next;
	}
	printf("#");
}
//树的先跟遍历
void TreePreTraverse(Tree &tree, int index)
{
	Node link;
	printf("%d ", tree[index].data);

	link = tree[index].link;
	while (link != NULL)
	{
		TreePreTraverse(tree, link->child);
		link = link->next;
	}
}
//森林的先根遍历
void FTreePreTraverse(Forest &fTree)
{
	Forest link = fTree->next;
	while (link != NULL)
	{
		TreePreTraverse(link->tree, 0);
		link = link->next;
	}
}

//二叉树的先序遍历
void BiTreePreTraverse(pBiTreeNode &tree)
{
	if (tree != NULL)
	{
		printf("%d ", tree->data);

		if (tree->lchild != NULL)
		{
			BiTreePreTraverse(tree->lchild);
		}

		if (tree->rchild != NULL)
		{
			BiTreePreTraverse(tree->rchild);
		}
	}
}

//主函数
int main(void)
{

	printf("\n树（森林）的广义表（括号表示法）重建树（森林）\n");
	printf("请输入树（森林）的广义表（括号表示法）（以#结束）：\n");

	Forest fTree1;
	InitFTree(fTree1);
	GListToFTree(fTree1);
	printf("\n树（森林）的广义表（括号表示法）重建树（森林）后的遍历\n");
	printf("树（森林）的先根遍历：\n");
	FTreePreTraverse(fTree1);
	printf("\n");
	printf("\n树（森林）转化成二叉树：\n\n");
	BiTree biTree1;
	InitBiTree(biTree1);
	FTreeToBiTree(fTree1, biTree1);
	printf("树（森林）转换成二叉树后二叉树的遍历\n");
	printf("树（森林）转换成的二叉树的先序遍历：\n");
	BiTreePreTraverse(biTree1.tree);
	printf("\n");
	printf("\n先序遍历序列重二叉树：\n");
	pBiTreeNode t;
	Creat1BT(t);
	BiTree biTree2;
	biTree2.tree = t;
	printf("\n二叉树后的先序遍历：\n");
	BiTreePreTraverse(biTree2.tree);

	Forest fTree2;
	InitFTree(fTree2);

	printf("\n二叉树转化成树（森林）：\n\n");
	BiTreetoFTree(fTree2, biTree2.tree);
	printf("二叉树转换成树（森林）后，树（森林）的遍历：\n");
	printf("树（森林）的先根遍历：\n");
	FTreePreTraverse(fTree2);
	printf("\n\n");
	printf("\n上面生成的树(森林)生成其相应的广义表（括号表示法）\n");
	FTreeToGList(fTree2);
	return 0;
}
