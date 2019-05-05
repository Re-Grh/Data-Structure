#include <iostream>
#include <cstdio>
#pragma warning(disable:4996)
#define maxlen 100
#define maxint 10000
using namespace std;
int D[maxlen], P[maxlen], S[maxlen];
int D1[maxlen][maxlen], P1[maxlen][maxlen];
struct matrix_graph
{
	int n, e; 
	int mat[maxlen][maxlen];
};
typedef struct matrix_graph juzhen; /*�ڽӾ���*/

void cre1(juzhen  &G) /*�����ڽӾ���*/
{
	FILE* fstream;
	fstream = fopen("2.txt", "r+");
	int i, j, x, y,w;
	cout << "���붥����������" << endl;
	fscanf(fstream, "%d %d", &G.n, &G.e);
	cout << "���붥����Ϣ" << endl;
	for (i = 1; i<=G.n; i++)
	for (j = 1; j <=G.n; j++)
	{
		G.mat[i][j] = maxint;
	}
	cout << "����������������ż���Ȩֵ" << endl;
	for (i = 0; i<G.e; i++)
	{
		fscanf(fstream, "%d %d %d", &x, &y,&w);
		G.mat[x][y] = w;
	}
	cout << "�ڽӾ���" << endl;
	for (i = 1; i<=G.n; i++)
	{
		for (j = 1; j<=G.n; j++)
			cout << G.mat[i][j] << " ";
		cout << endl;
	}
	fclose(fstream);
}
void Dijkstra(juzhen G, int v,int c)
{
	int i, j,k,min;
	for (i = 1; i <= G.n; i++)
	{
		S[i] = 0;
	}
	for (i = 1; i <= G.n; i++)
	{
		D[i] = G.mat[v][i];
		if (D[i] < maxint) P[i] = v;
		else P[i] = 0;
	}
	P[v] = 0, S[v] = 1;
	for (i = 2; i <= G.n; i++)
	{
		min = maxint;
		for (j = 1; j <= G.n; j++)
		{
			if (D[j] < min&&S[j]==0)
			{
				k = j;
				min = D[k];
			}
		}
		S[k] = 1;
		for (j = 1; j <= G.n; j++)
		{
			if (S[j]==0)
			{
				if (D[j] > D[k] + G.mat[k][j])
				{
					D[j] = D[k] + G.mat[k][j];
					P[j] = k;
				}
			}
		}
	}
	cout << "���·������    ���·��" << endl;
	if (c == 1)
	{
		for (i = 1; i <= G.n; i++)
		{
			if (i != v)
			{
				cout << D[i] << "     " << i;
				k = P[i];
				while (k != 0){
					cout << " <- " << k;
					k = P[k];
				}
				cout << endl;
			}
		}
	}
	else{
		for (i = 1; i <= G.n; i++)
		{
			if (i != v)
			{
				cout << D[i] << "     " << i;
				k = P[i];
				while (k != 0){
					cout << " -> " << k;
					k = P[k];
				}
				cout << endl;
			}
		}
	}
	
}
void Floyd(juzhen G)
{
	int i, j, k;
	for (i = 1; i <= G.n; i++)
	{
		for (j = 1; j <= G.n; j++)
		{
			D1[i][j] = G.mat[i][j];
			P1[i][j] = 0;
		}
	}
	for (k = 1; k <= G.n; k++)
	{
		for (i = 1; i <= G.n; i++)
		{
			for (j = 1; j <= G.n; j++)
			{
				if (D1[i][j] > D1[i][k] + D1[k][j])
				{
					D1[i][j] = D1[i][k] + D1[k][j];
					P1[i][j] = k;
				}
			}
		}
	}
}
int main()
{
	int v,i,j,k,a,c,tep=1;
	juzhen G,g;
	cre1(G);
	while (tep)
	{
		printf("���·���㷨ʵ������ \n");
		printf("1����Dijkstra�㷨���Դ�㵽������������·��\n");
		printf("2����Floyd-Warshall�㷨��������������������·��\n");
		printf("3����Dijkstra�㷨����������㵽Ŀ���յ�����·��\n");
		printf("4����Floyd-Warshall�㷨���ĳ�Զ������·��\n");
		printf("6�����˳�����\n");
		printf("���������ѡ�1-6��:");
		cin >> a;
		switch (a)
		{

		case 1:
			system("cls");
			cout << "������Դ�㣺";
			cin >> v;
			Dijkstra(G, v,1);
			printf("�Ƿ��������1.YES  2��NO  ����");
			cin >> c;
			getchar();
			if (c == 1)tep = 1;
			else
				tep = 0;
			system("cls");
			break;
		case 2:
			system("cls");
			Floyd(G);
			cout << "��̾������" << endl;
			for (i = 1; i <= G.n; i++)
			{
				for (j = 1; j <= G.n; j++)
					cout << D1[i][j] << " ";
				cout << endl;
			}
			cout << "���·������" << endl;
			for (i = 1; i <= G.n; i++)
			{
				for (j = 1; j <= G.n; j++)
					cout << P1[i][j] << " ";
				cout << endl;
			}
			cout << "���·������    ���·��" << endl;
			for (i = 1; i <= G.n; i++)
			{
				for (j = 1; j <= G.n; j++)
				{
					if (D1[i][j] < maxint/2&&i!=j)
					{
						cout << D1[i][j] << "   ";
						k = P1[i][j];
						cout << j << " <- ";
						while (k != 0){
							cout << k << " <- ";
							k = P1[k][j];
						}
						cout << i;
						cout << endl;
					}
				}
			}
			printf("�Ƿ��������1.YES  2��NO ����");
			cin >> c;
			getchar();
			if (c == 1)tep = 1;
			else
				tep = 0;
			system("cls");
			break;
		case 3:
			system("cls");
			cout << "�������յ㣺";
			cin >> v;
			g.e = G.e, g.n = G.n;
			for (i = 1; i <= G.n; i++)
			{
				for (j = 1; j <= G.n; j++)
					g.mat[i][j] = G.mat[j][i];
			}
			Dijkstra(g, v,2);
			printf("\n�Ƿ��������1.YES  2��NO ����");
			cin >> c;
			getchar();
			if (c == 1)tep = 1;
			else
				tep = 0;
			system("cls");
			break;
		case 4:
			system("cls");
			Floyd(G);
			cout << "���������������㣺 ";
			cin >> i >> j;
			cout << "����" << i << " -> " << j << "    ";
			cout << "���·������    ���·��" << endl;
			cout << D1[i][j] << "   ";
			k = P1[i][j];
			cout << j << " <- ";
			while (k != 0){
				cout << k << " <- ";
				k = P1[k][j];
			}
			cout << i;
			cout << endl;
			cout << "����" << j << " -> " << i << "    ";
			cout << "���·������    ���·��" << endl;
			cout << D1[j][i] << "   ";
			k = P1[j][i];
			cout << i << " <- ";
			while (k != 0){
				cout << k << " <- ";
				k = P1[k][i];
			}
			cout << j;
			cout << endl;
			printf("\n�Ƿ��������1.YES  2��NO ����");
			cin >> c;
			getchar();
			if (c == 1)tep = 1;
			else
				tep = 0;
			system("cls");
			break;
		case 5:
			system("cls");
			
			system("cls");
			break;
		case 6:
			printf("ллʹ�ã�");
			tep = 0;
			break;
		default:
			system("cls");
			printf("ѡ�����\n");
		}
	}

	return 0;
}