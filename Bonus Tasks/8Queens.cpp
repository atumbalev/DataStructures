#include <iostream>
#include <set>

using std::set;

#define size 8

bool board[size][size];

set<int> attackedColumns;
set<int> attackedLeftDiagonals;
set<int> attackedRightDiagonals;

unsigned variations = 0;

bool canPlaceQueen(int row, int col)
{
	bool positionTaken =
			attackedColumns.count(col) ||
			attackedLeftDiagonals.count(col - row) ||
			attackedRightDiagonals.count(row + col);

	return !positionTaken;
}

void markAttackedFields(int row, int col)
{
	attackedColumns.insert(col);
	attackedLeftDiagonals.insert(col-row);
	attackedRightDiagonals.insert(row+col);
	board[row][col] = true;
}

void unmarkFields(int row, int col)
{
	attackedColumns.erase(col);
	attackedLeftDiagonals.erase(col - row);
	attackedRightDiagonals.erase(row + col);
	board[row][col] = false;
}

void printSolution()
{
	variations++;
	for (int row = 0; row < size; row++)
	{
		for (int col = 0; col < size; col++)
		{
			if (board[row][col] == 1) std::cout << "Q ";
			else std::cout << "- ";
		}
		std::cout << '\n';
	}
	std::cout << '\n';
}

void solve(int row)
{
	if (row == size) 
	{
		printSolution();
		return;
	}

	for (int col = 0; col < size; ++col)
	{
		if (canPlaceQueen(row, col))
		{
			markAttackedFields(row, col);
			solve(row +1);
			unmarkFields(row,col);
		}
	}
}

int main()
{	
	solve(0);
	std::cout << "Total variations: " << variations << "\n";
	return 0;
}