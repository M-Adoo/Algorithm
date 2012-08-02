//HeapSort.h
//2011/9/12  by Adoo

#pragma once

template<typename Iter>
void MaxHeapfy(Iter  BegIter, Iter EndIter, Iter Position)
{	//thsi function to keep the heap attribute;

	//get the Left child and Right child;
	Iter LIter(Position);
	Iter RIter(Position);
    std::size_t  Index=std::distance(BegIter,Position)+1;
	//we must check if the iterator will out the range before we call
	if(Index<std::distance(Position,EndIter))
	{
		std::advance (LIter,Index);
		std::advance (RIter,Index+1);
	}
	else
	{
		return ;
	}

	//get the largest element  in Position and his childrens;
	Iter Largest(Position);
	if(LIter!=EndIter&&*LIter>*Largest)
		Largest=LIter;
	if(RIter!=EndIter&&*RIter>*Largest)
		Largest=RIter;
	if(Largest!=Position)
	{
		std::swap (*Position,*Largest);
		MaxHeapfy(BegIter,EndIter,Largest);
	}
}
template <typename Iter>
void BuildMaxHeap(const Iter BegIter,Iter EndIter)
{
	Iter Iter1(BegIter);
	//call MaxHeapfy from the last node of the heap;
	for(std::advance (Iter1,std::distance (BegIter,EndIter)/2); Iter1!=BegIter ;--Iter1)
	{ 
		MaxHeapfy(BegIter,EndIter,Iter1);
	}
	MaxHeapfy(BegIter,EndIter,Iter1);
}

template<typename Iter>
void HeapSort(Iter BegIter, Iter EndIter)
{
	BuildMaxHeap(BegIter,EndIter);
	//we always get the largest element and put it on the end,then shrink the heap, and build heap again;
	for(--EndIter;  EndIter!=BegIter; --EndIter)
	{
		std::swap(*EndIter,*BegIter);
		MaxHeapfy(BegIter,EndIter,BegIter);
	}
}