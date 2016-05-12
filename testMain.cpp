/*
 * copyright (c) 2016 K Sreram
 * This program and any associated files are under MIT license (https://opensource.org/licenses/MIT)
 */

#define TEST_COMPLEXITY true
#include <iostream>
#include "quicksort\QuickSort.hpp"
#include <vector>
#include <stdlib.h>  
#include <time.h>       

int main()
{
	srand(time(NULL));
	std::vector <int> array, array2;
	int arraySize = rand() % 100000 + 1;
	
	std::cout << "array size :" << arraySize << "\n";
	system("pause");
	std::cout << "\n";

	array.resize(arraySize);
	
	for (int i = 0; i < arraySize; ++i)
	{
		array[i] = rand() % 500;
	}

	array2 = array;

	QuickSort<int> sortProcedure(0, &array, HOARE_PARTITION_SCHEME);
	sortProcedure.Randomize = false;
	
	std::cout << "\n----------------- Non randomized -------------------------\n";
	
	std::cout << "\narray before sorting : \n";
	for (int i = 0; i < arraySize; ++i)
	{
		std::cout << array[i] << "\n";
	}
	sortProcedure.Sort();
	std::cout << "\n array after sorting : \n";
	for (int i = 0; i < arraySize; ++i)
	{
		std::cout << array[i] << "\n";
	}

	std::cout << "\n\n count:" << sortProcedure.count << "\n";
	system("pause");

	std::cout << "\n --------------- Randomized -------------------------------\n";

	sortProcedure.reInitialize(0, &array2, HOARE_PARTITION_SCHEME);
	sortProcedure.Randomize = true;
	std::cout << "\narray before sorting : \n";
	for (int i = 0; i < arraySize; ++i)
	{
		std::cout << array2[i] << "\n";
	}
	sortProcedure.Sort();
	std::cout << "\n array after sorting : \n";
	for (int i = 0; i < arraySize; ++i)
	{
		std::cout << array2[i] << "\n";
	}


	std::cout << "\n\n count:" << sortProcedure.count << "\n";
	system("pause");
	return 0;
}
