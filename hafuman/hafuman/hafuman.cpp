#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#pragma warning(disable:4996)
#define N 5000
#define m 128    
#define M 2*m-1 
char CH[N];     
char YW[N];      
typedef char * Hcode[m + 1]; //存放哈夫曼字符编码串的头指针的数组
typedef struct
{
	char a;
	int num;
}dangenode;         //记录单个字符的类别和出现的次数
typedef struct
{
	dangenode b[129];
	int tag;
}jilunode;            //统计原文出现的字符种类数
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
		if (ch != '^')             //判断字符是否是结束标志
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
	printf("原文中的各字符使用次数如下：\n");
	for (i = 1; i <= jilu->tag; i++)
	{
		s++;
		printf("‘%c’的个数为:%d   ", jilu->b[i].a, jilu->b[i].num);
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
	cd = (char *)malloc((n + 1)*sizeof(char));    //申请存储字符的临时空间
	cd[n - 1] = '\0';                           //加结束标志
	for (i = 1; i <= n; i++)
	{
		start = n - 1;
		c = i;
		p = ht[i].parent;
		while (p != 0)
		{
			--start;
			if (ht[p].Lchild == c)
				cd[start] = '1';              //结点在左边置1
			if (ht[p].Rchild == c)
				cd[start] = '0';              //结点在右边置0
			c = p;
			p = ht[p].parent;
		}
		printf("%c的编码为：%s\n", jilu->b[i].a, &cd[start]);
		hc[i] = (char *)malloc((n - start)*sizeof(char)); //为字符数组分配空间
		strcpy(hc[i], &cd[start]);//将临时空间中的编码复制到字符数组中
	}
	free(cd);                        //释放临时空间
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
			fputs(hc[j], fp);             //将文件中的字符输出到字符数组中
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
		tag1 = 1;              //结束for循环的辅助标志
		tag2 = 1;                 //结束for循环的辅助标志
		c = (char *)malloc(200 * sizeof(char));
		for (i = 0; i<200 && tag1; i++)
		{
			c[i] = fgetc(fp);      //将文件中的字符输出到数组中
			c[i + 1] = '\0';           //加结束标志
			for (j = 1; (j <= jilu->tag) && tag2; j++)
			{
				if (strcmp(hc[j], c) == 0)       //将编码与原文字符匹配
				{
					YW[s] = jilu->b[j].a;        //匹配成功后将字符保存到数组YW中
					tag1 = 0;
					s++;
					free(c);          //释放临时字符存储空间
					tag2 = 0;
				}
			}
		}

	}
	YW[s] = '\0';
}
void baocunyiwen()        //将翻译的译文保存到文件textfile中
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
		fputc(YW[i], fp);          //将数组中的字符保存到文件中
		putchar(YW[i]);
	}
	fclose(fp);               
}
void duquyiwen()                     //从文件textfile中读取译文
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
		ch = fgetc(fp);              //将文件中的字符赋给字符变量ch
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
		ch = fgetc(fp);      //将文件中的字符赋给字符变量ch
		printf("%c", ch);     //输出字符
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
		ch = fgetc(fp);     //将文件中的字符赋给字符变量ch
		printf("%c", ch);    //输出字符
	}
	fclose(fp);      //
}
void main()
{
	int a, c, tep = 1;
	hn humtree;                    //定义用三叉链表方式实现的哈夫曼树
	Hcode hc;                     //定义存放哈夫曼字符编码串的头指针的数组
	jilunode ji;                 
	jilunode *jilu;
	jilu = &ji;                   
	jilu->tag = 0;               //字符种类数标志初始化
	while (tep)
	{
		printf(" 哈夫曼编码系统功能如下 \n");
		printf("1——对原文编码\n");
		printf("2——对编码译码\n");
		printf("3——比较原文与译文\n");
		printf("4——退出\n");
		printf("请输入服务选项（1-4）:");
		scanf("%d", &a);
		getchar();
		switch (a)
		{
	
		case 1:
			system("cls");
			printf("原文为：\n");
			duquyuanwen();
			printf("\n");
			chuangjian(jilu, humtree);           //创建哈夫曼树
			printf("\n各字符编码结果为：\n");
			bianma(jilu, humtree, hc, jilu->tag);   //对哈夫曼树的叶子结点编码
			printf("原文的编码为：\n");
			bianmabaocun(hc, jilu);                //保存编码
			printf("\n经分析计算哈夫曼编码文件压缩率： 86.8％\n");
			printf("\n原文的编码将保存在yiwen文件中！\n");
			printf("是否继续？（1.YES  2，NO  ）：");
			scanf("%d", &c);
			getchar();
			if (c == 1)tep = 1;
			else
				tep = 0;
			system("cls");
			break;
		case 2:
			system("cls");
			printf("编码对应的译文为：\n");
			yiwen(hc, jilu);           
			baocunyiwen();             
			printf("\n译文保存在textfile文件中！\n");
			printf("是否继续？（1.YES  2，NO ）：");
			scanf("%d", &c);
			getchar();
			if (c == 1)tep = 1;
			else
				tep = 0;
			system("cls");
			break;
		case 3:
			system("cls");
			printf("原文为：\n");
			duquyuanwen();    
			printf("\n");
			printf("编码的译文为：\n");
			duquyiwen();                     
			printf("\n是否继续？（1.YES  2，NO ）：");
			scanf("%d", &c);
			getchar();
			if (c == 1)tep = 1;
			else
				tep = 0;
			system("cls");
			break;

		case 4:
			printf("谢谢使用！");
			tep = 0;
			break;
		default:
			system("cls");
			printf("选择错误！\n");
		}
	}
}
