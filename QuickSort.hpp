#ifndef _QUICK_SORT_
#define _QUICK_SORT_

#include <vector>
#include <stdlib.h>  
#include <time.h>     

enum Flags{ LOMUTO_PARTITION_SCHEME = 1, HOARE_PARTITION_SCHEME = 2 };


template <class T>
void swap(T& a, T& b)
{
	T temp;
	temp = a;
	a = b;
	b = temp;
}


template < class DataType >
class QuickSort
{

	std::vector < DataType >* dataList;
	Flags algorithmChoice;
	float relativePositionOfPivot;

public:
	bool Randomize;
	size_t count;
	void obtainDataList(std::vector < DataType >* data)
	{
		dataList = data;
	}
	QuickSort()
	{
		// the defalut algorithm used
		algorithmChoice = HOARE_PARTITION_SCHEME;
		count = 0;
		Randomize = false;
		srand(time(NULL));
	}

	QuickSort(float p, std::vector < DataType >* data, const Flags& flag)
	{
		setPositonOfPivot(p);
		setSortAlgorithm(flag);
		obtainDataList(data);
		Randomize = false;
		srand(time(NULL));
		count = 0;
	}

	void reInitialize(float p, std::vector < DataType >* data, const Flags& flag)
	{
		setPositonOfPivot(p);
		setSortAlgorithm(flag);
		obtainDataList(data);
		Randomize = false;
		srand(time(NULL));
		count = 0;
	}

	void setSortAlgorithm(const Flags& flag)
	{
		algorithmChoice = flag;
	}

	void setPositonOfPivot(float p)
	{
		relativePositionOfPivot = p;
	}

	void Sort()
	{
		sortPorcedure(dataList, 0, dataList->size() - 1, algorithmChoice, relativePositionOfPivot);
	}

	std::vector < DataType >* returnArray()
	{
		return dataList;
	}

	
			///**************************************************************************************************
			///               The following contains the main modules for the sort procedure
			///**************************************************************************************************
	/*
	* This partition scheme is the most used among the two possiblities. This has two pointers, 
	* starting from the highest possible position and the lowest possible position respectively. 
	* Then as the iteration proceeds, both the pointers start approching each other. 
	* 
	* A partition scheme is used to determine how the array is partitioned after positioning the pivot. 
	*/
	int hoarePartitionScheme(std::vector < DataType >* array, int lowPos, int highPos, int pivotPos)
	{
		int i = lowPos;
		int j = highPos; 
		
		///sets the pivot based on the location 
		DataType pivot = (*array)[pivotPos];

		/// this is an infnite loop which gets terminated when the pointers (i and j) cross each other. 
		while (true)
		{
			for (; 
				(i <= highPos) && ((*array)[i] <= pivot); 
				++i
	
#ifdef TEST_COMPLEXITY
							,count++
					
#endif // TEST_COMPLEXITY
																);

			for (;
				(j >= lowPos) && ((*array)[j] >= pivot); 
				--j
						
#ifdef TEST_COMPLEXITY
								, count++

#endif // TEST_COMPLEXITY

								);

			if (i > j || i > highPos || j < lowPos) break;
			swap((*array)[i], (*array)[j]);

		}
		
		// initial pivotPos is before the partition: need to be brought to 'j' 
		if (pivotPos < j)
		{
			swap((*array)[j], (*array)[pivotPos]);
			return j;
		}
		// initial pivotPos is after the partition: need to be brought in place, i.e., 'i'
		else if (pivotPos > i)
		{
			swap((*array)[i], (*array)[pivotPos]);
			return i;
		}
		else
		{
			// swapping is not needed if the element is already preasent in the location it have to be in.
			return pivotPos;
		}
	}

	int lomutoPartitionScheme(std::vector < DataType >* array, int lowPos, int highPos, int pivotPos)
	{
		int i;
		int j;
		DataType pivot = (*array)[pivotPos];
		for (i = j = lowPos; j <= highPos; ++j)
		{
			
			
#ifdef TEST_COMPLEXITY
					count++;

#endif // TEST_COMPLEXITY
			
			if ((*array)[j] < pivot )
			{
				swap((*array)[i], (*array)[j]);
				++i;
			}
			if (i == pivotPos)
				++i;
		}
		if (pivotPos > i)
		{
			swap((*array)[i], (*array)[pivotPos]);
			return i;
		}
		else if (pivotPos < i)
		{
			swap((*array)[i - 1], (*array)[pivotPos]);
			return i - 1;
		}
		return i;
	}


	void sortPorcedure(std::vector < DataType > * array, int lowPos, int highPos, const Flags& flag,  float relativePositionOfPivot)
	{
		int pos;
		if (Randomize)
			relativePositionOfPivot = (float)(rand() % (*array).size()) / ((float)(*array).size());
		int pivotPos = lowPos + (highPos - lowPos)*relativePositionOfPivot;
		if (lowPos >= highPos) return;

			switch (flag)
			{
			case HOARE_PARTITION_SCHEME:
				pos = hoarePartitionScheme(array, lowPos, highPos, pivotPos );
				break;
			case LOMUTO_PARTITION_SCHEME:
				pos = lomutoPartitionScheme(array, lowPos, highPos, pivotPos );
				break;
			default:
				break;
			}
			
			/// This should be designed in such a way that the placed pivot isn't included in the sorting process 
			/// again after it gets sorted
			sortPorcedure(array, lowPos, pos-1, flag, relativePositionOfPivot);
			sortPorcedure(array, pos+1, highPos, flag, relativePositionOfPivot);

	}


};
#endif