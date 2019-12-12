#include <iostream>


// Merges two subarrays of arr[]. 
// First subarray is arr[l..m] 
// Second subarray is arr[m+1..r] 
template <typename T>
void merge(T arr[], unsigned beg, unsigned mid, unsigned end) 
{
	unsigned leftArrSize = mid - beg + 1;
	unsigned rightArrSize = end - mid;

	/* Init subarrays*/
	T left[leftArrSize];
	T right[rightArrSize];
	/* Copy elements from original arr into subarrays */
	for (int i = 0; i < leftArrSize; ++i)
	{
		left[i] = arr[beg + i];
	}

	for (int i = 0; i < rightArrSize; ++i)
	{
		right[i] = arr[mid + i + 1];
	}


	unsigned i = 0; // @left iteration index
	unsigned j = 0; // @right iteration index
	unsigned k = beg; // @arr iteration index

	while ( i < leftArrSize && j < rightArrSize)
	{
		if (left[i] <= right[j])
		{
			arr[k] = left[i];
			++i;
		}
		else
		{
			arr[k] = right[j];
			++j;
		}
		++k;
	}

	/* Dump remaining elements of remaining array */
	while (i < leftArrSize)
	{
		arr[k] = left[i];
		++i;
		++k;
	}

	while (j < rightArrSize)
	{
		arr[k] = right[j];
		++j;
		++k;
	}
} 

/* l is for left index and r is right index of the 
sub-array of arr to be sorted */
template <typename T>
void mergeSort(T arr[], int l, int r) 
{
	if (l < r) 
	{
		int m = (r + l) / 2; 

		// Sort first and second halves 
		mergeSort(arr, l, m); 
		mergeSort(arr, m+1, r); 

		merge(arr, l, m, r); 
	} 
} 

/* UTILITY FUNCTIONS */
/* Function to print an array */
template <typename T>
void printArray(T A[], int size) 
{ 
	for (int i = 0; i < size; i++) 
	{
		std::cout << A[i] << ' ';
	}

	std::cout << std::endl;
} 

int main() 
{ 
	int arr[] = {12, 11, 13, 5, 6, 7}; 
	int arr_size = sizeof(arr)/sizeof(arr[0]); 

	printf("Given array is \n"); 
	printArray(arr, arr_size); 

	mergeSort(arr, 0, arr_size - 1); 

	printf("\nSorted array is \n"); 
	printArray(arr, arr_size); 
	return 0; 
} 
