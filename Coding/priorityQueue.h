//PriorityQueue.h    
//By Adoo   2011/9/19  
//when I learning Introduction To Algorithm
#pragma once
#include"HeapSort.h"
#include<deque>
#include<numeric>

template<typename T>
class PriorityQueue
{
	
	
public:
	PriorityQueue(void){};
	~PriorityQueue(void){};

	void Add(const T& value )
	{
		data.push_back(value);
		auto position=data.end ()-1;
		//mantain the heap property
		while(position>data.begin () && *position>*parent(position))
		{
			swap(*parent(position),*position);
			position=parent(position);
		}
	};

	T Get(void)
	{
		if(data.empty())
		   return std::numeric_limits<int>::min ();
		std::swap(*data.begin(),*(data.end()-1));
		T result=data.back();
		data.pop_back();
		//mantain the heap property
		MaxHeapfy(data.begin (),data.end (),data.begin ());
		return result;
	}
private:
	typename std::deque<T>::iterator parent(typename const std::deque<T>::iterator& last)
	{
    	return  data.begin ()+(last-data.begin ())/2;
	}
	std::deque<T>  data;
};

