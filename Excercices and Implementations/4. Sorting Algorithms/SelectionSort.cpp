#include <iostream>

template <typename T>
void selectionSort(T array[], unsigned size)
{
	for(int i = 0; i< size; ++i)
	{
		int min = i;
		for(int j = i; j < size; ++j)
		{
			if(array[min] > array[j])
				min = j;
		}

		std::swap(array[min],array[i]);
	}
}

int main(int argc, char const *argv[])
{
	int arr[10] = {1,2,4,7,8,3,56,7,4,9};
	selectionSort(arr, 10);

	for (int i = 0; i < 10; ++i)
	{
		std::cout << arr[i] << std::endl;
	}
	
	return 0;
}