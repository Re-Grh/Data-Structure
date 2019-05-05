#include<iostream>
#include<string>
#include<fstream>
#include<iomanip>
#include<queue>
using namespace std;
const int CHARACTERNUMBER = 26;
const int CODELENGTH = 5;

struct childNode 
{
	int key; 
	childNode*next;
};

struct HuffmanNode
{
	double weight; 
	int parent;
	int order; 
	childNode* child;
};

struct HuffmanCode
{
	char ch;
	char bits[CHARACTERNUMBER + 1];
};

struct node
{
	int key;
	double weight;
	node() :key(0), weight(0){}; 
	node(int _key, double _weight) :key(_key), weight(_weight){}; 
	friend bool operator< (node a, node b){ return b.weight < a.weight; }; 
};

class Huffman 
{
public:
	Huffman();
	~Huffman();
	void readFile(string filename);
	void buildtree(int knumber);
	void encode(int number);
	void output(string filename, string encode_file);
	void decode(string encode_filename, string decode_filename);
private:
	HuffmanNode HuffmanTree[2 * CHARACTERNUMBER - 1]; 
	HuffmanCode HuffmanCodeGroup[CHARACTERNUMBER];
	int root; 
	int k; 
};

Huffman::Huffman()
{
	for (int i = 0; i < 2 * CHARACTERNUMBER - 1; i++)
	{
		(HuffmanTree + i)->child = NULL;
		(HuffmanTree + i)->order = -1;
		(HuffmanTree + i)->parent = -1;
		(HuffmanTree + i)->weight = 0;
	}
}

Huffman::~Huffman()
{}

void Huffman::readFile(string filename)
{
	int characternum[CHARACTERNUMBER] = { 0 }; 
	char c;
	int count = 0; 
	fstream fin(filename);
	while (fin >> c&&!fin.eof()) 
	{
		characternum[c - 97]++;
		count++;
	}
	for (int i = 0; i < CHARACTERNUMBER; i++) 
	{
		(HuffmanTree + i)->weight = (double)characternum[i] / count;
	}
	fin.close();
}

void Huffman::buildtree(int knumber)
{
	priority_queue<node> q;
	node record;
	childNode* ch;
	k = knumber;
	int n = CHARACTERNUMBER;
	while ((n - 1) % (k - 1) != 0) 
	{
		q.push(node(-1, 0));
		n++;
	}
	for (int i = 0; i < CHARACTERNUMBER; i++) 
	{
		q.push(node(i, (HuffmanTree + i)->weight));
	}
	int j = CHARACTERNUMBER;
	while (q.size() > 1)
	{
		for (int n = 0; n < k; n++) 
		{
			record = q.top();
			q.pop();
			(HuffmanTree + record.key)->parent = j;
			(HuffmanTree + record.key)->order = n;
			ch = (HuffmanTree + j)->child;
			if (ch == NULL) (HuffmanTree + j)->child = new childNode{ record.key, NULL }; 
			else
			{
				while (ch->next != NULL)
				{
					ch = ch->next;
				}
				ch->next = new childNode{ record.key, NULL };
			}
			(HuffmanTree + j)->weight += record.weight;
		}
		q.push(node(j, (HuffmanTree + j)->weight)); 
		j++;
	}
	root = j - 1;
}

void Huffman::encode(int knumber)
{
	int children, father, start;
	childNode* pchild = NULL;
	char cd[CHARACTERNUMBER + 1]; 
	cd[CHARACTERNUMBER] = '\0'; 
	buildtree(knumber);
	for (int i = 0; i < CHARACTERNUMBER; i++)
	{
		HuffmanCodeGroup[i].ch = 97 + i;
		start = CHARACTERNUMBER;
		children = i;
		while (HuffmanTree[children].parent != root) 
		{
			father = HuffmanTree[children].parent;
			cd[--start] = HuffmanTree[children].order + 48;
			children = father;
		}
		cd[--start] = HuffmanTree[children].order + 48;
		strcpy_s(HuffmanCodeGroup[i].bits, &cd[start]);
	}
	cout << "The code table is... " << endl;
	cout << setw(8) << "character" << setw(8) << "code" << endl;
	for (int j = 0; j < CHARACTERNUMBER; j++)
	{
		cout << setw(8) << HuffmanCodeGroup[j].ch << setw(10) << HuffmanCodeGroup[j].bits << endl;
	}
}

void Huffman::output(string filename, string encode_file)
{
	char c;
	int count = 0;
	int codesize = 0;
	double efficiency = 0;
	ifstream fin(filename);
	ofstream fout(encode_file);
	while (fin >> c)
	{
		count++;
		codesize += strlen(HuffmanCodeGroup[c - 97].bits);
		fout << HuffmanCodeGroup[c - 97].bits;
	}
	fin.close();
	fout.close();
	efficiency = (double)codesize / (count*CODELENGTH);
	cout << "the pression rate is " << efficiency<<endl;
}

void Huffman::decode(string encode_filename, string decode_filename)
{
	char c, decoded_c;
	childNode *p;
	fstream encode_read(encode_filename);
	fstream decode_output(decode_filename);
	while (encode_read.peek() != EOF)
	{
		int i = root;
		while (HuffmanTree[i].child != NULL)
		{
			p = HuffmanTree[i].child;
			encode_read >> c;
			int code = atoi(&c);
			for (int j = 0; j < code; j++) 
			{
				p = p->next;
			}
			i = p->key;
		}
		decoded_c = HuffmanCodeGroup[i].ch;
		decode_output << decoded_c;
	}
	encode_read.close();
	decode_output.close();
}
void usage()
{
	cout << "Enter 1 to encode the file with K-huffman tree... " << endl;
	cout << "Enter 2 to decode the file..." << endl;
	cout << "Enter 0 for exit the program..." << endl;
}

int main()
{
	char op = ' ';
	int knumber;
	Huffman huff;
	Huffman B_huff;
	Huffman K_huff;
	while (true)
	{
		usage();
		op = getchar();
		getchar();

		switch (op)
		{
		case '1':
			cout << "Reading the file and building the huffman tree..." << endl;
			huff.readFile("file.txt");
			cout << "Input k: " << endl;
			cin >> knumber;
			getchar();
			huff.encode(knumber);
			cout << "Encoding the file..." << endl;
			huff.output("file.txt", "code.txt");
			cout << "the encoded file is stored in " << "code.txt" << endl;
			break;
		case '2':
			cout << "Decoding the file..." << endl;
			huff.decode("code.txt", "newfile.txt");
			cout << "the decoded file is stored in " << "newfile.txt" << endl;
			break;
		case '0':
			exit(0);
		default:
			break;
		}
	}
	return 0;
}