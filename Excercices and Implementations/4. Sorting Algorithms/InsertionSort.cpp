#include <iostream>
#include <cstring>

template <typename T>
void insertionSort(T array[], unsigned size)
{
	for(int i = 1; i < size; i++)
	{
		T value = array[i];
		int index = i;
		while(index > 0 && array[index -1] >= value)
		{
			array[index] = array[index - 1];
			--index;
		}
		array[index ] = value;
	}
}

int main(int argc, char const *argv[])
{
	int arr[10] = {1,2,4,7,8,3,56,7,4,9};
	insertionSort(arr, 10);

	for (int i = 0; i < 10; ++i)
	{
		std::cout << arr[i] << std::endl;
	}

	// Lexicografically sort strings
	char str[16] = "asdfghjbch";
	insertionSort(str, strlen(str));

	for (int i = 0; str[i] != '\0'; ++i)
	{
		std::cout << str[i];
	}
	
	return 0;
}