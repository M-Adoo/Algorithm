//QuickSort.h
//by Adoo 2011/9/25
//when I learning Introduction to algorithm
#ifndef QUICKSORT
#define QUICKSORT
#include<ctime>
#include<Windows.h>


template<typename Iter>
void QuickSort(Iter BegIter, Iter EndIter)
{
	if(std::distance(BegIter,EndIter)>1)
	{//if betwen BegIter and EndIter not only one element;
		Iter Apart=Partition(BegIter,EndIter);
		QuickSort(BegIter,Apart);
		std::advance(Apart,1);
		QuickSort(Apart,EndIter);
	}
}

template<typename Iter> 
Iter  Partition(Iter BegIter, Iter EndIter)
{
	//let the EndIter point to the pivot Iterator;
	--EndIter;
	//Apart the elements;
	Iter Apart=BegIter;
	while(BegIter!=EndIter)
	{
		if(*BegIter<*EndIter)
		{
			std::swap (*BegIter,*Apart);
			++Apart;
		}
		++BegIter;
	}
	std::swap(*Apart,*EndIter);
	return Apart;
}

template<typename Iter>
void RadomQuickSort(Iter BegIter, Iter EndIter)
{
	if(std::distance(BegIter,EndIter)>1)
	{//if betwen BegIter and EndIter not only one element;
		Iter Apart=RadomPartition(BegIter,EndIter);
		QuickSort(BegIter,Apart);
		std::advance(Apart,1);
		QuickSort(Apart,EndIter);
	}
}

template<typename Iter> 
Iter  RadomPartition(Iter BegIter, Iter EndIter)
{
	//let the EndIter point to the pivot Iterator;
	srand(std::time(0));
	Iter Pivot=BegIter+rand()%(EndIter-BegIter-1)+1;
	
	//Apart the elements;
	Iter Apart=BegIter;
	while(BegIter!=EndIter)
	{
		if(*BegIter<*Pivot)
		{
			std::swap (*BegIter,*Apart);
			++Apart;
		}
		++BegIter;
	}
	std::swap(*Apart,*Pivot);
	return Apart;
}


#endif
