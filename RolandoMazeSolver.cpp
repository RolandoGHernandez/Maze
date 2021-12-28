// RolandoMazeSolver.cpp

#include <ics46/factory/DynamicFactory.hpp>
#include "RolandoMazeSolver.hpp"

ICS46_DYNAMIC_FACTORY_REGISTER(MazeSolver, RolandoMazeSolver, "Rolando's Solver (Required)");

// It doesn't say to NOT use global variables so let's make 3 here, matrix being the game board.
std::vector<std::vector<int>> matrixx;
unsigned int maxRowz=0;
unsigned int maxColz=0;

// main functions that does the solving and calls the recursive call
void RolandoMazeSolver::solveMaze(const Maze& maze, MazeSolution& mazeSolution)
{
	mazeSolution.restart();

	solutionFound = false;

	std::pair<int, int> start = mazeSolution.getStartingCell();

	matrixx = RolandoMazeSolver::makeMatrixx(maze.getHeight(), maze.getWidth());

	RolandoMazeSolver::recursion(maze, mazeSolution, matrixx, start.second, start.first);

}

// makes a vector of int vectors to keep track of where we have been
std::vector<std::vector<int>> RolandoMazeSolver::makeMatrixx(unsigned int row, unsigned int col)
{
	maxRowz = row;
	maxColz = col;

	std::vector<std::vector<int>> matrixx(maxRowz, std::vector<int>(maxColz));

	for (int i = 0; i < maxRowz; i++)
	{
		for (int j = 0; j < maxColz; j++)
		{
			matrixx[i][j] = 0;
		}
	}
	return matrixx;
}

// the recursion functions that keeps going and backing up until it finds a single path
void RolandoMazeSolver::recursion(const Maze& maze, MazeSolution& mazeSolution, std::vector<std::vector<int>> matrixx,
	unsigned int currentRow, unsigned int currentCol)
{
	std::pair<int, int> end = mazeSolution.getEndingCell();
	if (currentCol == end.first && currentRow == end.second)
	{
		solutionFound = true;
		return;
	}

	matrixx[currentRow][currentCol] = 1;


	// look for adjacents
	bool upVal = RolandoMazeSolver::checkValidUp(currentRow, currentCol, matrixx, maze);
	bool downVal = RolandoMazeSolver::checkValidDown(currentRow, currentCol, matrixx, maze);
	bool leftVal = RolandoMazeSolver::checkValidLeft(currentRow, currentCol, matrixx, maze);
	bool rightVal = RolandoMazeSolver::checkValidRight(currentRow, currentCol, matrixx, maze);


	while (upVal == true || downVal == true || rightVal == true || leftVal == true)
	{

		if (upVal == true)
		{
			mazeSolution.extend(Direction::up);
			RolandoMazeSolver::recursion(maze, mazeSolution, matrixx, currentRow-1, currentCol);
			upVal = false;
			if (solutionFound == true)
			{
				return;
			}
		}

		else if (downVal == true)
		{
			mazeSolution.extend(Direction::down);
			RolandoMazeSolver::recursion(maze, mazeSolution, matrixx, currentRow+1, currentCol);
			downVal = false;
			if (solutionFound == true)
			{
				return;
			}
		}

		else if (leftVal == true)
		{
			mazeSolution.extend(Direction::left);
			RolandoMazeSolver::recursion(maze, mazeSolution, matrixx, currentRow, currentCol-1);
			leftVal = false;

			if (solutionFound == true)
			{
				return;
			}

		}

		else if (rightVal == true)
		{
			mazeSolution.extend(Direction::right);
			RolandoMazeSolver::recursion(maze, mazeSolution, matrixx, currentRow, currentCol+1);
			rightVal = false;

			if (solutionFound == true)
			{
				return;
			}
		}
	}

	mazeSolution.backUp();

	if (solutionFound == true)
	{
		return;
	}

}

// return a bool True if valid to remove wall up and cell up is empty
bool RolandoMazeSolver::checkValidUp(unsigned int currentRow, unsigned int currentCol, std::vector<std::vector<int>>& matrixx, const Maze& maze)
{
	if (currentRow == 0 || matrixx[currentRow-1][currentCol] == 1 || maze.wallExists(currentCol,currentRow,  Direction::up) == true){return false;}
	else {return true;}
}

// return a bool True if valid to remove wall down AND cell down is empty
bool RolandoMazeSolver::checkValidDown(unsigned int currentRow, unsigned int currentCol, std::vector<std::vector<int>>& matrixx, const Maze& maze)
{
	if (currentRow == maxRowz-1 || matrixx[currentRow+1][currentCol] == 1 || maze.wallExists(currentCol,currentRow, Direction::down) == true){return false;}
	else {return true;}
}


// return a bool True if valid to remove wall left and cell is empty
bool RolandoMazeSolver::checkValidLeft(unsigned int currentRow, unsigned int currentCol, std::vector<std::vector<int>>& matrixx, const Maze& maze)
{
	if (currentCol == 0 || matrixx[currentRow][currentCol-1] == 1 || maze.wallExists(currentCol,currentRow, Direction::left) == true){return false;}
	else {return true;}
}

// return a bool True if valid to remove wall right and cell is empty
bool RolandoMazeSolver::checkValidRight(unsigned int currentRow, unsigned int currentCol, std::vector<std::vector<int>>& matrixx, const Maze& maze)
{
	if (currentCol == maxColz-1 || matrixx[currentRow][currentCol+1] == 1 || maze.wallExists(currentCol,currentRow, Direction::right) == true){return false;}
	else {return true;}
}
