//RadomizedSelect
//by Adoo  2011/10/17

#ifndef RADOMIZEDSELECT
#define RADOMIZEDSELECT
#include"QuickSort.h"

template<typename Iter>
Iter RadomizedSelect(Iter IBeg,Iter IEnd,int index)
{
	if(std::distance(IBeg,IEnd)<2)
		return IBeg;
	auto apart=RadomPartition(IBeg,IEnd);
	// Don't forget add 1;
	int i=std::distance(IBeg,apart)+1;
	if(index==i)
		return apart;
	else
		return index<i ? RadomizedSelect(IBeg,apart,index):RadomizedSelect(++apart,IEnd,index-i);   
}
#endif