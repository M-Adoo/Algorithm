//Sort.h          By Adoo
//I coding the file when I learning the 'Algorithm To Introduction'
//InsertionSort     
//2011/7/17    updated the code     InsertionSort   


#ifndef  SORT_H
#define SORT_H
#include<algorithm>
#include<limits>

/*
//InsertionSort     By Adoo
//2011/7/16         When I learning the <Algorithm To Introduction>

#include"Sort.h"
template  <typename  T>         //Assume the "T" is iterator
T InsertionSort(const T& BeginIter, const T& EndIter)
{
	auto Iter=BeginIter;
	++Iter;
	while(Iter!=EndIter)
	{
		auto Key=*Iter;
		auto Iter2=Iter;
		--Iter2;
	   while(Iter2>=BeginIter && Key<*Iter2)
	    {
			auto Iter3=Iter2;
			++Iter3;
			*Iter3=*Iter2;
			if(Iter2!=BeginIter)
				--Iter2;
			else
				break;
		}
		*(Iter2)=Key;
		++Iter;
	}
	return Iter;
}
*/

template  <typename  T>        
T InsertionSort( const T& BeginIter, const T& EndIter)
{
	auto Iter=BeginIter;
	++Iter;
	while(Iter!=EndIter)
	{
		auto Key=*Iter;
		std::reverse_iterator <T> RIter(Iter);
		std::reverse_iterator <T> RBeginIter(BeginIter);
	   while(RIter!=RBeginIter && Key<*RIter)
	    {
			auto Iter3=RIter;
			*--Iter3=*RIter++;
		}
		*--RIter=Key;
		++Iter;
	}
	return Iter;
}

//MergeSort  
//the merge sort has two version , one combine the result depend on std::inpace_merge
//the other I implement the combin result by myself
//2011/8/16   
template <typename T>
void MergeSort(const T& BegIter,const T& EndIter)
{

	if(BegIter+1<EndIter)
	{
		auto MidIter=BegIter;
		advance(MidIter,distance(BegIter,EndIter)/2 );
		MergeSort(BegIter,MidIter); 
		MergeSort(MidIter,EndIter);
		//CombineResult(BegIter,MidIter,EndIter);
		std::inplace_merge(BegIter,MidIter,EndIter);
	}
}

//my inplace merge for MergeSort
template<typename T>
T CombineResult(const T& BegIter, const T& MidIter,const T& EndIter)
{
	std::vector<T::value_type> Array1(BegIter,MidIter);
	Array1.push_back(std::numeric_limits<T::value_type>::max());
	std::vector<T::value_type>Array2(MidIter,EndIter);
	Array2.push_back(std::numeric_limits<T::value_type>::max());
	auto  Beg1=Array1.begin();
	auto Beg2=Array2.begin();
	T Beg=BegIter;
	while(Beg!=EndIter)
	{
		if(*Beg1<*Beg2)
		{
			*Beg++=*Beg1++;
		}
		else
		{
			*Beg++=*Beg2++;
		}
	}
	return EndIter;

}


#endif
