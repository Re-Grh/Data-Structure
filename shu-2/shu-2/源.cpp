#include <iostream>
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#pragma warning(disable:4996)
using namespace std;
//���к��ӽ�������ĵ�������
typedef struct CTNode
{
	int child;
	struct CTNode *next;
} CTNode, *Node;
//���������㣨����㣩
typedef struct CTBox
{
	Node link;
	int data;
} CTBox, *Tree;
//ɭ�ֽ��
typedef struct ForestNode
{
	Tree tree;
	struct ForestNode *next;
} ForestNode, *Forest;
//ɭ������ĳ�ʼ������
void InitFTree(Forest &fTree)
{
	fTree = (Forest)malloc(sizeof(ForestNode));
	fTree->next = NULL;
}
//ɭ������Ĳ������
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
//����������
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
//������齨��ɭ������
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

//���������
typedef struct BiTreeNode
{
	int data;
	struct BiTreeNode *lchild;
	struct BiTreeNode *rchild;
} BiTreeNode, *pBiTreeNode;
//������
typedef struct BiTree
{
	pBiTreeNode tree;
} BiTree;
//��������ʼ��
void InitBiTree(BiTree &biTree)
{
	biTree.tree = NULL;
}
void Creat1BT(pBiTreeNode &T)     /*����ݹ鴴��������*/
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

//������ת��Ϊ�����Ƕ�����ת��Ϊɭ�ֵ��Ӻ���
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
//������ת��Ϊɭ��
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
//��ת��Ϊ������
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
//ɭ��ת��Ϊ������
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
//��ת��Ϊ�����
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
//ɭ��ת��Ϊ�����
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
//�����ȸ�����
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
//ɭ�ֵ��ȸ�����
void FTreePreTraverse(Forest &fTree)
{
	Forest link = fTree->next;
	while (link != NULL)
	{
		TreePreTraverse(link->tree, 0);
		link = link->next;
	}
}

//���������������
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

//������
int main(void)
{

	printf("\n����ɭ�֣��Ĺ�������ű�ʾ�����ؽ�����ɭ�֣�\n");
	printf("����������ɭ�֣��Ĺ�������ű�ʾ��������#��������\n");

	Forest fTree1;
	InitFTree(fTree1);
	GListToFTree(fTree1);
	printf("\n����ɭ�֣��Ĺ�������ű�ʾ�����ؽ�����ɭ�֣���ı���\n");
	printf("����ɭ�֣����ȸ�������\n");
	FTreePreTraverse(fTree1);
	printf("\n");
	printf("\n����ɭ�֣�ת���ɶ�������\n\n");
	BiTree biTree1;
	InitBiTree(biTree1);
	FTreeToBiTree(fTree1, biTree1);
	printf("����ɭ�֣�ת���ɶ�������������ı���\n");
	printf("����ɭ�֣�ת���ɵĶ����������������\n");
	BiTreePreTraverse(biTree1.tree);
	printf("\n");
	printf("\n������������ض�������\n");
	pBiTreeNode t;
	Creat1BT(t);
	BiTree biTree2;
	biTree2.tree = t;
	printf("\n������������������\n");
	BiTreePreTraverse(biTree2.tree);

	Forest fTree2;
	InitFTree(fTree2);

	printf("\n������ת��������ɭ�֣���\n\n");
	BiTreetoFTree(fTree2, biTree2.tree);
	printf("������ת��������ɭ�֣�������ɭ�֣��ı�����\n");
	printf("����ɭ�֣����ȸ�������\n");
	FTreePreTraverse(fTree2);
	printf("\n\n");
	printf("\n�������ɵ���(ɭ��)��������Ӧ�Ĺ�������ű�ʾ����\n");
	FTreeToGList(fTree2);
	return 0;
}
