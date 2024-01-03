#include <iostream>
#include <algorithm>
#include <vector>
#include <array>

using std::cout;
using std::endl;

#define DIM 9
#define BLANK 0
#define SPACE " "
#define LINE "|"
#define NEW_ROW "-------------------------------------"
#define GRID_FULL std::make_pair(9, 9)

void print_grid(int grid[DIM][DIM])
{
	for (int i = 0; i < DIM; i++)
	{
		cout << SPACE << SPACE << SPACE << SPACE << endl;
		cout << NEW_ROW << endl;
		for (int j = 0; j < DIM; j++)
		{
			cout << SPACE;
			if (BLANK == grid[i][j])
			{
				cout << SPACE;
			}
			else
			{
				cout << grid[i][j];
			}
			cout << SPACE;
			cout << LINE;
		}
	}
	cout << endl << NEW_ROW << endl << endl;;
}

// Returns a boolean which represents row matches the given number (any assigned entry)
bool used_in_row(int grid[DIM][DIM], int row, int num)
{
	for (int col = 0; col < DIM; col++)
		if (grid[row][col] == num)
		{
			return true;
		}
	return false;
}

// Returns a boolean which represents column matches the given number (any assigned entry)
bool used_in_col(int grid[DIM][DIM], int col, int num)
{
	for (int row = 0; row < DIM; row++)
		if (grid[row][col] == num)
		{
			return true;
		}
	return false;
}

bool used_in_box(int grid[DIM][DIM], int box_start_rpw, int box_start_col, int num)
{
	for (int row = 0; row < 3; row++)
		for (int col = 0; col < 3; col++)
			if (grid[row + box_start_rpw][col + box_start_col] == num) 
			{
				return true;
			}
	return false;
}

bool is_safe(int grid[DIM][DIM], int row, int col, int num)
{
	// Check if 'num' is not already placed in row,column &box 
	return !used_in_row(grid, row, num) &&
		!used_in_col(grid, col, num) &&
		!used_in_box(grid, row - row % 3, col - col % 3, num);
}

// Searches the grid to find an entry that is unassigned. If found, the reference parameters row, col will be set to the location
// that is unassigned, and true is returned. If no unassigned entries: false is returned. 
std::pair<int, int> get_unassigned_location(int grid[DIM][DIM])
{
	for (int row = 0; row < DIM; row++)
		for (int col = 0; col < DIM; col++)
			if (grid[row][col] == BLANK)
			{
				return std::make_pair(row, col);
			}
	return GRID_FULL;
}

bool solve_soduko(int grid[DIM][DIM])
{
	if (GRID_FULL == get_unassigned_location(grid))
	{
		return true; 
	}

	std::pair<int, int> row_and_col = get_unassigned_location(grid);
	int row = row_and_col.first;
	int col = row_and_col.second;

	for (int num = 1; num <= 9; num++)
	{
		if (is_safe(grid, row, col, num))
		{
			grid[row][col] = num;
			// Doing recursion. If return true, then all of our number placements on the Soduko grid are valid & solved. YO!
			if (solve_soduko(grid))
			{
				return true;
			}
			grid[row][col] = BLANK;
		}
	}
	return false; 
}

int main()
{
	cout << "\n\n\tSudoku Solver\n\n" << endl << endl;

	int grid[DIM][DIM] = { { 0, 9, 0, 0, 0, 0, 8, 5, 3 },
						   { 0, 0, 0, 8, 0, 0, 0, 0, 4 },
						   { 0, 0, 8, 2, 0, 3, 0, 6, 9 },
						   { 5, 7, 4, 0, 0, 2, 0, 0, 0 },
						   { 0, 0, 0, 0, 0, 0, 0, 0, 0 },
						   { 0, 0, 0, 9, 0, 0, 6, 3, 7 },
						   { 9, 4, 0, 1, 0, 8, 5, 0, 0 },
						   { 7, 0, 0, 0, 0, 6, 0, 0, 0 },
						   { 6, 8, 2, 0, 0, 0, 0, 9, 0 } };

	print_grid(grid);

	if (true == solve_soduko(grid))
	{
		print_grid(grid);
	}
	else
	{
		cout << "No solution.... Sudoku Sucks" << endl << endl;
	}

	return 0;
}