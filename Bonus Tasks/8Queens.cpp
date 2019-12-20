// In how many ways can we place N queens on an NxN chessboard
// without havin 2 queens threaten each other?
// Example solution with size = 8
#include <iostream>
#include <set>

using std::set;

// size of the board, also equal to the number of queens
#define size 8

bool board[size][size];

set<int> attackedColumns;
set<int> attackedLeftDiagonals;
set<int> attackedRightDiagonals;

// counter that displays how many different variations we found
unsigned variations = 0;

bool canPlaceQueen(int row, int col)
{
	bool positionTaken =
			attackedColumns.count(col) ||				// Check if column is attacked
			attackedLeftDiagonals.count(col - row) ||	// All squares in the same left diagonal have the same col - row
			attackedRightDiagonals.count(row + col);	// All squares in the same right diagonal have the same row + col

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

// Recursively finds a solution for the given row
void solve(int row)
{
	// we have placed a queen on every row, so a solution is found
	if (row == size) 
	{
		variations++;
		printSolution();
		return;
	}

	// We iterate over every column of that row, trying to place a 
	for (int col = 0; col < size; ++col)
	{
		if (canPlaceQueen(row, col))
		{	// we mark and unmark so we can explore different variations later on
			markAttackedFields(row, col);
			// we dive into 1 current variation
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