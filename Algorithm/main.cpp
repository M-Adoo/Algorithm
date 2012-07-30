#include "fibonacciHeap.hpp"
#include<iostream>
#include<list>
using namespace std;
int main(){
	FibonacciHeap<int> fib;
	FibonacciHeap<int> fib2;
	FibonacciHeap<int>::node *p = NULL, *p2 = NULL;
	for(int i = 1; i!= 10;  ++i)
	{
		fib.insert(i);
		p=fib2.insert(10*i);
	}
	
	fib.merge(fib2);
	fib.extract_min();
	p2 = p->right;
	fib.decrease_key(p,0);
	fib.decrease_key(p2,1);
	std::cout<<"the size of list<fibonacciHeap>  is :"<<sizeof(list<FibonacciHeap<int> >)<<endl;
	cout<<"the size of list<int> is:"<<sizeof(int)<<endl;
	cin.get();
}