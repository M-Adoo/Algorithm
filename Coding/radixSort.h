//RadixSort.h
//By Adoo
//2011/10/2

#ifndef RADIX_SORT
#define RADIX_SORT
#include<deque>
#include<iterator>

template<typename InIt>
void RadixSort(InIt BegIt,InIt EndIt )
{
	int byte=8*sizeof(*BegIt);
	int count=std::distance (BegIt,EndIt);
	int size=std::log(double(count))/std::log(double(2));
	size=byte<size ? byte : size;
	int from=1;

	do
	{
		RadixCounting(BegIt,EndIt,from,size);
		from+=size;
	}while(from<byte);

	for(auto index=BegIt;index!=EndIt; ++index)
	{
		if(*index<0)
		{
			std::vector< std::iterator_traits<InIt>::value_type > vec(index,EndIt);
			vec.insert(vec.end(),BegIt,index);
			std::copy(vec.begin(),vec.end(),BegIt);
			return;
		}
	}

};

template<typename InIt>
void RadixCounting(InIt BegIt,InIt EndIt ,const int From, const int Size)
{//counting sort the elements form BegIt to EndIt base on the Size bits from From;
	
	//the counter
	int capa=std::pow(double(2),Size);
	std::vector<int> Counter(capa,0);
	
	int clip=capa-1;
	for(auto Index=BegIt;Index!=EndIt;++Index)
		++Counter[((*Index)>>From-1)&clip];

	for(int i=1;i!=capa;++i)
		Counter[i]+=Counter[i-1];
	
	std::vector<int> Result(Counter[capa-1],0);
	for(std::reverse_iterator<InIt> RIter(EndIt),REnd(BegIt); RIter!=REnd ;++RIter)
	{
		int index=((*RIter)>>From-1)&clip;
		Result[ Counter[index]-- -1]=*RIter;
	}
	std::copy(Result.begin(),Result.end(),BegIt);
}


#endif