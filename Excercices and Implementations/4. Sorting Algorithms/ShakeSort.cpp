#include <iostream>
#include <list>

using std::list;

void sortCocktailStyle(list<int>& dl)
{
	bool swapped = true;

	list<int>::iterator begin = dl.begin();
	list<int>::iterator end = dl.end();

	while (swapped)
	{
		swapped = false;
		for (list<int>::iterator it= begin; it != end; ++it)
		{
			list<int>::iterator next(it);
			++next;
			if (next == end) break;

			if (*it > *next)
			{
				std::swap(*it, *next);
				swapped = true;
			}
		}

		if (!swapped) break;

		swapped = false;

		--end;

		for (list<int>::iterator it = end; it != begin; --it) { 

			list<int>::iterator prev(it);
			--prev;

            if (*prev > *it) { 
                std::swap(*it, *prev);
                swapped = true;
            } 
        } 
   
        ++begin; 

	}
}

int main(int argc, char const *argv[])
{
	list<int> dl;
	dl.push_back(5);
	dl.push_back(1);
	dl.push_back(4);
	dl.push_back(2);
	dl.push_back(8);
	dl.push_back(0);
	dl.push_back(2);

	sortCocktailStyle(dl);

	for (list<int>::iterator it = dl.begin(); it != dl.end(); ++it)
	{
		std::cout << *it << ' ';
	}
	std::cout << std::endl;

	return 0;
}