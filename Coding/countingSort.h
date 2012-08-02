//CountingSort.h
//by Adoo
//2011/9/29

#ifndef COUNTING_SORT
#define COUNTING_SORT
#include<vector>
template <typename InputIter,typename OutIter>
void CountingSort(InputIter BegIter,InputIter EndIter,OutIter OutputIter, const int Boundary)
{
	//the counter
	std::vector<int> Counter(Boundary,0);
	
	for(auto Index=BegIter;Index!=EndIter;++Index)
		++Counter[*Index];
	// Counter[] holds the number of input element equal to *index;

	for(int i=1;i!=Boundary;++i)
		Counter[i]+=Counter[i-1];
	//Now Counter[] contains the number of elements less than or eaual to i

	std::vector<int> Result(Counter[Boundary-1],0);
	for(std::reverse_iterator<InputIter> RIter(EndIter),REnd(BegIter); RIter!=REnd ;++RIter)
	{
		Result[Counter[*RIter]-1]=*RIter;
		--Counter[*RIter];
	}
	std::copy(Result.begin (),Result.end (),OutputIter);
}
#endif