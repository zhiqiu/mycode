#include <algorithm>
#include <iostream>
#include <string>
#include "MinHeap.h"

using namespace std;

class A
{
	string name;
	int id;
public:
	A(string name_, int id_)
	{
		name = name_;
		id = id_;
	}
};

int main()
{
	MinHeap<A*> *heap = new MinHeap<A*>();
	
	heap->init();
	string a = "a";
	A *a1 = new A(a, 1);
	A *a2 = new A(a, 2);
	A *a3 = new A(a, 3);
	A *a4 = new A(a, 4);
	A *a5 = new A(a, 5);
	
	heap->insert(a1, 3);
	heap -> print();	
	heap->insert(a2, 1);
	heap -> print();	
	heap->insert(a3, 5);
	heap -> print();	
	heap->insert(a4, 2);
	heap -> print();	
	heap->insert(a5, 4);
	heap -> print();	
}

