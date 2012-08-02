//FindMaxSubArray.h      By Adoo
//2011.8.27     when  I learning the    Introduction to algorithm
//Across this  understand  how  to   devide and conquer
#ifndef FindMax
#define FindMax
template<typename T>
std::pair<std::pair<T,T>,typename T::value_type>
	FindMaxCrossingArray(const T& BegIter,const T& MidIter, const T& EndIter){

		T::value_type  LeftSum=std::numeric_limits<T::value_type>::min();
		T::value_type  Sum=T::value_type();
		T LeftIter=MidIter;

		for(std::reverse_iterator<T> RIter(MidIter),RBegIter(BegIter) ; RIter!=RBegIter;++RIter){
			Sum+=*RIter;
			if(Sum>LeftSum){
				LeftSum=Sum;
				LeftIter=RIter.base();
			}
		}

		T::value_type RightSum=std::numeric_limits<T::value_type>::min();
		T RightIter=MidIter;
		Sum=T::value_type();
		for(auto Iter=MidIter;Iter!=EndIter;++Iter){
			Sum+=*Iter;
			if(Sum>RightSum){
				RightSum=Sum;
				RightIter=Iter;
			}
		}
		return std::make_pair(make_pair(LeftIter,RightIter),LeftSum+RightSum);
};
     

template<typename T>
std::pair<std::pair<T,T>,typename T::value_type>	
FindMaxSubArray(const T& BegIter,const T& EndIter){
        typedef std::pair<std::pair<T,T>,typename T::value_type> RType;
		if(EndIter-BegIter==1)
			return make_pair(make_pair(BegIter,EndIter),*BegIter);
		T MidIter=BegIter;
	     advance(MidIter, distance(BegIter,EndIter)/2);
		RType R1=FindMaxSubArray(BegIter,MidIter);
		RType R2=FindMaxSubArray(MidIter,EndIter);
		RType R3=FindMaxCrossingArray(BegIter,MidIter,EndIter);
		
		auto R= R1.second>R2.second ? R1:R2 ;
		return  R.second>R3.second ?R:R3;
	
}

#endif