#include <iostream>
#include <string>
#include <iomanip>
using namespace std;
template <class T, class cmp = std::minus<T>>
class priority_queue
{
public:
	priority_queue();
	~priority_queue();

	void insert(T n);
	void pop();
	T top();
	int size();

private:
	int parent(int i);
	int left(int i);
	int right(int i);
	void exchange(T& a, T& b);
	void max_heapify(int i);

	int heap_size;
	int length;
	cmp minus;
	T* array;
};


template<class T, class cmp>
priority_queue<T, cmp>::priority_queue()
{
	heap_size = 0;
	length = 1;
	array = new T[length];
}

template<class T, class cmp>
priority_queue<T, cmp>::~priority_queue()
{
	delete array;
}

template<class T, class cmp>
int priority_queue<T, cmp>::parent(int i)
{
	return (i - 1) / 2;
}

template<class T, class cmp>
int priority_queue<T, cmp>::left(int i)
{
	return i * 2 + 1;
}

template<class T, class cmp>
int priority_queue<T, cmp>::right(int i)
{
	return i * 2 + 2;
}

template<class T, class cmp>
void priority_queue<T, cmp>::exchange(T& a, T& b)
{
	T c = a;
	a = b;
	b = c;
}

template <class T, class cmp>
int priority_queue<T, cmp>::size()
{
	return heap_size;
}

template<class T, class cmp>
void priority_queue<T, cmp>::max_heapify(int i)
{
	int l = left(i);
	int r = right(i);
	int largest = i;
	if (l < heap_size && minus(array[l], array[i])>0)
		largest = l;
	if (r < heap_size && minus(array[r], array[largest])>0)
		largest = r;
	if (largest != i) {
		exchange(array[i], array[largest]);
		max_heapify(largest);
	}
}

template<class T, class cmp>
void priority_queue<T, cmp>::insert(T n)
{
	if (heap_size == length) {
		T* temp_arr = new T[2 * length];
		memmove(temp_arr, array, sizeof(T)*length);
		length *= 2;
		delete array;
		array = temp_arr;
	}
	array[heap_size++] = n;
	int temp = heap_size - 1;
	while (temp>0 && minus(array[parent(temp)], array[temp])<0) {
		exchange(array[parent(temp)], array[temp]);
		temp = parent(temp);
	}
}
template<class T, class cmp>
void priority_queue<T, cmp>::pop()
{
	if (heap_size == 0)
		return;
	if (heap_size == length >> 2) {
		length >>= 2;
		T* temp_arr = new T[length >> 2];
		memmove(temp_arr, array, sizeof(T)*length);
		delete array;
		array = temp_arr;
	}
	array[0] = array[--heap_size];
	max_heapify(0);
}

template<class T, class cmp>
T priority_queue<T, cmp>::top()
{
	return array[0];
}

struct char_freq {
	char letter;
	double freq;

	char_freq(char x, double y)
		:letter(x), freq(y) {}
};

struct huffman_node
{
	char_freq data;
	huffman_node *left;
	huffman_node *right;

	huffman_node(char_freq x)
		:data(x), left(nullptr), right(nullptr) {}
};

class huffman_tree {
public:
	class cmp {
	public:
		double operator() (huffman_node* x, huffman_node* y);
	};

	huffman_tree(int num = 2);
	~huffman_tree();

public:
	void insert(char_freq x);
	void insert(char letter, double freq);
	void creat_huffman_tree();
	void print_tree();

private:
	int K;
	priority_queue<huffman_node*, cmp> pri_que;
	huffman_node* head;

	void free_memory(huffman_node* head);
	void print_tree_help(huffman_node* head, std::string prefix, std::string code);
};

double huffman_tree::cmp::operator()(huffman_node *x, huffman_node *y)
{
	return y->data.freq - x->data.freq;
}

huffman_tree::huffman_tree(int num)
{
	K = num;
	head = nullptr;
}

huffman_tree::~huffman_tree()
{
	free_memory(head);
}

void huffman_tree::free_memory(huffman_node *head)
{
	if (!head)
		return;
	free_memory(head->left);
	free_memory(head->right);
	delete head;
}

void huffman_tree::insert(char_freq x)
{
	huffman_node* temp = new huffman_node(x);
	pri_que.insert(temp);
}

void huffman_tree::insert(char letter, double freq)
{
	insert(char_freq(letter, freq));
}

void huffman_tree::creat_huffman_tree()
{
	if (head)
		free_memory(head);
	while ((pri_que.size() - 1) % (K - 1))
		insert('#', 0.0);
	while (pri_que.size() > 1) {
		huffman_node* new_node = new huffman_node(char_freq(0, 0));
		double new_freq = 0.0;
		new_node->left = pri_que.top();
		new_freq += pri_que.top()->data.freq;
		pri_que.pop();
		huffman_node* temp = new_node->left;
		for (int i = 0; i<K - 1; i++) {
			temp->right = pri_que.top();
			new_freq += pri_que.top()->data.freq;
			pri_que.pop();
			temp = temp->right;
		}
		new_node->data.freq = new_freq;
		pri_que.insert(new_node);
	}
	head = pri_que.top();
	pri_que.pop();
}

void huffman_tree::print_tree()
{
	if (!head)
		std::cout << "huffman tree is empty!\n";
	else {
		std::cout << "print:\nh\n";
		print_tree_help(head, "", "");
	}
}

void huffman_tree::print_tree_help(huffman_node* h, std::string prefix, std::string code)
{
	std::cout << prefix + (h->right ? "©À©¤©¤©¤" : "©¸©¤©¤©¤");
	if (code.empty())
		std::cout << "©¤©¤©¤©´\n";
	else if (h->left)
		std::cout << "   " << code.back() << "\n";
	else
		std::cout << " " << h->data.letter << " : " << code << "\n";
	huffman_node* temp = h->left;
	int i = 0;
	while (temp) {
		if (temp->data.freq != 0)
			print_tree_help(temp, prefix + (h->right ? "©¦      " : "       "), code + char('0' + i++));
		temp = temp->right;
	}
}


void test_huffman_tree()
{
	std::cout << "k:";
	int k;
	std::cin >> k;
	huffman_tree test(k);
	std::cout << "1.insert\n2.creat tree\n3.print\n4.end\n";
	while (true) {
		char choice;
		std::cin >> choice;
		switch (choice) {
		case '1':
		{
					char letter;
					double freq;
					std::cin >> letter >> freq;
					test.insert(letter, freq);
					break;
		}
		case '2':
		{
					test.creat_huffman_tree();
					break;
		}
		case '3':
		{
					test.print_tree();
					break;
		}
		case '4':
			return;
		default:
			break;
		}
	}
}

int main()
{
	test_huffman_tree();
}

