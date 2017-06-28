#include <algorithm>
#define MAX_SIZE 5
using namespace std;
template <class T>
class MinHeap
{
	typedef double weight_type;
	class Node;
	public:
		MinHeap(int MaxSize_ = MAX_SIZE);
		~MinHeap();

		bool empty() const;
		int adjust(int index);
		int insert(T item, weight_type weight);
		int lookup(T item);
		void update(T item, weight_type newWeight);
		weight_type getWeight(T item);
		void init();
		void print();
	private:
		Node *data;
		int MaxSize;
};


template <class T>
class MinHeap<T>::Node
{
	public:
		T key;
		weight_type weight;
	public:
		Node();
		Node(const Node &node);
		Node& operator=(const Node &node);
		Node(T key_, weight_type weight_);
		~Node();
};


template <class T>
MinHeap<T>::Node::Node()
{
}

template <class T>
MinHeap<T>::Node::Node(const MinHeap<T>::Node &node)
{
	key = node.key;
	weight = node.weight;
}

template <class T>
typename MinHeap<T>::Node& MinHeap<T>::Node::operator=(const MinHeap<T>::Node &node)
{
	key = node.key;
	weight = node.weight;
	return *this;
}

template <class T>
MinHeap<T>::Node::Node(T key_, weight_type weight_)
{
	key = key_;
	weight = weight_;
}


template <class T>
MinHeap<T>::Node::~Node()
{
	//
}

template <class T>
MinHeap<T>::MinHeap(int MaxSize_)
{
	MaxSize = MaxSize_;
	data = new Node[MaxSize];
}


template <class T>
MinHeap<T>::~MinHeap()
{
	delete data;
}


template <class T>
void MinHeap<T>::init()
{
	//data = new Node[MaxSize];
	for(int i = 0; i < MaxSize; i ++)
	{
		data[i].weight = -1;
	}
}

template <class T>
void MinHeap<T>::print()
{
	for(int i = 0; i < MaxSize; i ++){
		cout << data[i].weight << " ";
	}
	cout << endl;
}

template <class T>
int MinHeap<T>::adjust(int index)
{
	int min = index;
	int left = index * 2 + 1, right = (index + 1) * 2; 
	if(left < MaxSize && data[left].weight < data[min].weight)
	{
		min = left;
	}
	if(right < MaxSize && data[right].weight < data[min].weight){
		min = right;
	}
	if(min != index){
		swap(data[index], data[min]);
		return adjust(min);
	}
	else{
		return min;
	}
}


template <class T>
int MinHeap<T>::insert(T item, weight_type weight)
{
	Node *node = new Node(item, weight);
	if(weight > data[0].weight)
	{
		swap(data[0], *node);
		return adjust(0);
	}
}
	
template <class T>
int MinHeap<T>::lookup(T item)
{
	;	
}

template <class T>
void MinHeap<T>::update(T item, weight_type newWeight)
{
	;
}

