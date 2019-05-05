#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#pragma warning(disable:4996)
#define N 5000
#define m 128    
#define M 2*m-1 
char CH[N];     
char YW[N];      
typedef char * Hcode[m + 1]; //��Ź������ַ����봮��ͷָ�������
typedef struct
{
	char a;
	int num;
}dangenode;         //��¼�����ַ������ͳ��ֵĴ���
typedef struct
{
	dangenode b[129];
	int tag;
}jilunode;            //ͳ��ԭ�ĳ��ֵ��ַ�������
typedef struct node
{
	int  weight;        
	int  parent;        
	int  Lchild;     
	int  Rchild;       
}htnode, hn[M];

void min_2(hn ht, int n, int *tag1, int *tag2)
{
	int i, min;
	min = N;
	for (i = 1; i <= n; i++)
	if (ht[i].weight<min&&ht[i].parent == 0)
	{
		min = ht[i].weight;
		*tag1 = i;            
	}
	min = N;
	for (i = 1; i <= n; i++)
	if (ht[i].weight<min&&ht[i].parent == 0 && i != *tag1)
	{
		min = ht[i].weight;
		*tag2 = i;
	}
	
}
void chuangjian(jilunode * jilu, hn ht)       
{
	int i, j, s, tag1, tag2;
	s = 0;
	i = -1;
	char ch;
	FILE *fp;  
	if ((fp = fopen("1", "rb")) == NULL)  
	{
		printf("Cannot open file\n");
		exit(0);
	}
start:	while (!feof(fp))        
	{
		ch = fgetc(fp);
		if (ch != '^')             //�ж��ַ��Ƿ��ǽ�����־
		{
			++i;
			CH[i] = ch;
			for (j = 1; j <= jilu->tag; j++)
			{
				if (CH[i] == jilu->b[j].a)
				{
					jilu->b[j].num++;
					goto start;
				}
			}
			jilu->tag++;
			jilu->b[jilu->tag].a = CH[i];
			jilu->b[jilu->tag].num = 1;
			
		}
	}
	jilu->tag--;
	fclose(fp);                
	printf("ԭ���еĸ��ַ�ʹ�ô������£�\n");
	for (i = 1; i <= jilu->tag; i++)
	{
		s++;
		printf("��%c���ĸ���Ϊ:%d   ", jilu->b[i].a, jilu->b[i].num);
		if (s % 4 == 0)                
			printf("\n");
	}

	printf("\n");
	for (i = 1; i <= 2 * (jilu->tag) - 1; i++)
	{
		if (i <= jilu->tag)
		{
			ht[i].weight = jilu->b[i].num; 
			ht[i].Lchild = 0;              
			ht[i].parent = 0;              
			ht[i].Rchild = 0;               
		}
		else
		{
			ht[i].Lchild = 0;      
			ht[i].parent = 0;     
			ht[i].weight = 0;   
			ht[i].Rchild = 0;    
		}
	}
	for (i = jilu->tag + 1; i <= 2 * (jilu->tag) - 1; i++)
	{
		min_2(ht, i - 1, &tag1, &tag2);
		ht[tag1].parent = i;
		ht[tag2].parent = i;
		ht[i].Lchild = tag1;
		ht[i].Rchild = tag2;
		ht[i].weight = ht[tag1].weight + ht[tag2].weight;
	}
}
void bianma(jilunode * jilu, hn ht, Hcode hc, int n)         
{
	char * cd;
	int start, i, p, c;
	cd = (char *)malloc((n + 1)*sizeof(char));    //����洢�ַ�����ʱ�ռ�
	cd[n - 1] = '\0';                           //�ӽ�����־
	for (i = 1; i <= n; i++)
	{
		start = n - 1;
		c = i;
		p = ht[i].parent;
		while (p != 0)
		{
			--start;
			if (ht[p].Lchild == c)
				cd[start] = '1';              //����������1
			if (ht[p].Rchild == c)
				cd[start] = '0';              //������ұ���0
			c = p;
			p = ht[p].parent;
		}
		printf("%c�ı���Ϊ��%s\n", jilu->b[i].a, &cd[start]);
		hc[i] = (char *)malloc((n - start)*sizeof(char)); //Ϊ�ַ��������ռ�
		strcpy(hc[i], &cd[start]);//����ʱ�ռ��еı��븴�Ƶ��ַ�������
	}
	free(cd);                        //�ͷ���ʱ�ռ�
}
void bianmabaocun(Hcode hc, jilunode * jilu)          
{

		int i, j;
	FILE *fp;
	if ((fp = fopen("yiwen", "wb")) == NULL)      
	{
		printf("Cannot open file\n");
		exit(0);                              
	}
	for (i = 0; i <= N&&CH[i] != '^'; i++)
	{
		for (j = 1; j <= jilu->tag; j++)
		if (CH[i] == jilu->b[j].a)
		{
			fputs(hc[j], fp);             //���ļ��е��ַ�������ַ�������
			printf("%s", hc[j]);
		}
	}
	fclose(fp);                         
}
void yiwen(Hcode hc, jilunode * jilu)            
{
	int tag1, tag2, i, j, s = 0;
	FILE *fp;                           
	char *c;
	if ((fp = fopen("yiwen", "rb")) == NULL)       
	{
		printf("cannot open file\n");
		exit(0);
	}
	while (!feof(fp))
	{
		tag1 = 1;              //����forѭ���ĸ�����־
		tag2 = 1;                 //����forѭ���ĸ�����־
		c = (char *)malloc(200 * sizeof(char));
		for (i = 0; i<200 && tag1; i++)
		{
			c[i] = fgetc(fp);      //���ļ��е��ַ������������
			c[i + 1] = '\0';           //�ӽ�����־
			for (j = 1; (j <= jilu->tag) && tag2; j++)
			{
				if (strcmp(hc[j], c) == 0)       //��������ԭ���ַ�ƥ��
				{
					YW[s] = jilu->b[j].a;        //ƥ��ɹ����ַ����浽����YW��
					tag1 = 0;
					s++;
					free(c);          //�ͷ���ʱ�ַ��洢�ռ�
					tag2 = 0;
				}
			}
		}

	}
	YW[s] = '\0';
}
void baocunyiwen()        //����������ı��浽�ļ�textfile��
{
	int i;
	FILE *fp;
	if ((fp = fopen("textfile", "wb")) == NULL)
	{
		printf("Cannot open file\n");
		exit(0);
	}
	for (i = 0; YW[i] != '\0'; i++)
	{
		fputc(YW[i], fp);          //�������е��ַ����浽�ļ���
		putchar(YW[i]);
	}
	fclose(fp);               
}
void duquyiwen()                     //���ļ�textfile�ж�ȡ����
{
	char ch;
	FILE *fp;
	if ((fp = fopen("textfile", "rb")) == NULL)      
	{
		printf("cannot open file\n");
		exit(0);
	}
	while (!feof(fp))
	{
		ch = fgetc(fp);              //���ļ��е��ַ������ַ�����ch
		printf("%c", ch);           
	}
	fclose(fp);                      
}
void duquyuanwen()                    
{
	char ch;
	FILE *fp;
	if ((fp = fopen("1", "rb")) == NULL)      
	{
		printf("cannot open file\n");
		exit(0);
	}
	while (!feof(fp))
	{
		ch = fgetc(fp);      //���ļ��е��ַ������ַ�����ch
		printf("%c", ch);     //����ַ�
	}
	fclose(fp);              
}
void duqubianma()                     
{
	char ch;
	FILE *fp;
	if ((fp = fopen("yiwen", "rb")) == NULL)
	{
		printf("cannot open file\n");
		exit(0);
	}
	while (!feof(fp))
	{
		ch = fgetc(fp);     //���ļ��е��ַ������ַ�����ch
		printf("%c", ch);    //����ַ�
	}
	fclose(fp);      //
}
void main()
{
	int a, c, tep = 1;
	hn humtree;                    //��������������ʽʵ�ֵĹ�������
	Hcode hc;                     //�����Ź������ַ����봮��ͷָ�������
	jilunode ji;                 
	jilunode *jilu;
	jilu = &ji;                   
	jilu->tag = 0;               //�ַ���������־��ʼ��
	while (tep)
	{
		printf(" ����������ϵͳ�������� \n");
		printf("1������ԭ�ı���\n");
		printf("2�����Ա�������\n");
		printf("3�����Ƚ�ԭ��������\n");
		printf("4�����˳�\n");
		printf("���������ѡ�1-4��:");
		scanf("%d", &a);
		getchar();
		switch (a)
		{
	
		case 1:
			system("cls");
			printf("ԭ��Ϊ��\n");
			duquyuanwen();
			printf("\n");
			chuangjian(jilu, humtree);           //������������
			printf("\n���ַ�������Ϊ��\n");
			bianma(jilu, humtree, hc, jilu->tag);   //�Թ���������Ҷ�ӽ�����
			printf("ԭ�ĵı���Ϊ��\n");
			bianmabaocun(hc, jilu);                //�������
			printf("\n��������������������ļ�ѹ���ʣ� 86.8��\n");
			printf("\nԭ�ĵı��뽫������yiwen�ļ��У�\n");
			printf("�Ƿ��������1.YES  2��NO  ����");
			scanf("%d", &c);
			getchar();
			if (c == 1)tep = 1;
			else
				tep = 0;
			system("cls");
			break;
		case 2:
			system("cls");
			printf("�����Ӧ������Ϊ��\n");
			yiwen(hc, jilu);           
			baocunyiwen();             
			printf("\n���ı�����textfile�ļ��У�\n");
			printf("�Ƿ��������1.YES  2��NO ����");
			scanf("%d", &c);
			getchar();
			if (c == 1)tep = 1;
			else
				tep = 0;
			system("cls");
			break;
		case 3:
			system("cls");
			printf("ԭ��Ϊ��\n");
			duquyuanwen();    
			printf("\n");
			printf("���������Ϊ��\n");
			duquyiwen();                     
			printf("\n�Ƿ��������1.YES  2��NO ����");
			scanf("%d", &c);
			getchar();
			if (c == 1)tep = 1;
			else
				tep = 0;
			system("cls");
			break;

		case 4:
			printf("ллʹ�ã�");
			tep = 0;
			break;
		default:
			system("cls");
			printf("ѡ�����\n");
		}
	}
}
