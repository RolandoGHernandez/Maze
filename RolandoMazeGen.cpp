// RolandoMazeGen.cpp

#include <ics46/factory/DynamicFactory.hpp>
#include "RolandoMazeGen.hpp"

ICS46_DYNAMIC_FACTORY_REGISTER(MazeGenerator, RolandoMazeGen, "Rolando's Generator (Required)");


// Random entropy here
std::random_device device;
std::default_random_engine engine{device()};
std::uniform_int_distribution<int> distribution{0,3};

// It doesn't say to NOT use global variables so let's make 3 here, matrix being the game board.
std::vector<std::vector<int>> matrix;
unsigned int maxRows=0;
unsigned int maxCols=0;

void RolandoMazeGen::generateMaze(Maze& maze)
{
	// first add all walls
	maze.addAllWalls();


	// make a vector of int vectors whose size is the same as the maze
	// all of the int sub vectors are filled with 0's to denote they are "unvisited" (empty) cells
	// int sub vectors will be filled with 1's later to mean "visited" cells
	matrix = RolandoMazeGen::createMatrix(maze.getHeight(), maze.getWidth());


	// recursion!  starts with 0 and 0 for row and col

	RolandoMazeGen::recursiveCall(maze, matrix, 0, 0);
}

void RolandoMazeGen::recursiveCall(Maze& maze, std::vector<std::vector<int>>& matrix, 
	unsigned int currentRow, unsigned int currentCol)
{
	// marks current cell as visited
	matrix[currentRow][currentCol] = 1;

	// look for adjacents
	bool upVal = RolandoMazeGen::checkValidUp(currentRow, currentCol, matrix);
	bool downVal = RolandoMazeGen::checkValidDown(currentRow, currentCol, matrix);
	bool leftVal = RolandoMazeGen::checkValidLeft(currentRow, currentCol, matrix);
	bool rightVal = RolandoMazeGen::checkValidRight(currentRow, currentCol, matrix);

	// need all to be false meaning no more valid adjacents
	while (upVal==true || downVal==true || leftVal == true || rightVal==true)
	{
		upVal = RolandoMazeGen::checkValidUp(currentRow, currentCol, matrix);
		downVal = RolandoMazeGen::checkValidDown(currentRow, currentCol, matrix);
		leftVal = RolandoMazeGen::checkValidLeft(currentRow, currentCol, matrix);
		rightVal = RolandoMazeGen::checkValidRight(currentRow, currentCol, matrix);

		// randomness
		int randomNum = distribution(engine);

		// enter up cell
		if (randomNum == 0 && upVal == true)
		{
			maze.removeWall( currentCol, currentRow, Direction::up);
			RolandoMazeGen::recursiveCall(maze, matrix, currentRow-1, currentCol);
			upVal = false;
		}

		// enter down cell
		else if (randomNum == 1 && downVal == true)
		{
			maze.removeWall(currentCol,currentRow,  Direction::down);
			RolandoMazeGen::recursiveCall(maze, matrix, currentRow+1, currentCol);
			downVal = true;
		}
		// enter left cell
		else if (randomNum == 2 && leftVal == true)
		{
			maze.removeWall(currentCol,currentRow, Direction::left);
			RolandoMazeGen::recursiveCall(maze, matrix, currentRow, currentCol-1);
			leftVal = false;
		}
		// enter right cell
		else if (randomNum == 3 && rightVal == true)
		{
			maze.removeWall(currentCol,currentRow, Direction::right);
			RolandoMazeGen::recursiveCall(maze, matrix, currentRow, currentCol+1);
			rightVal = false;
		}
	}
}


std::vector<std::vector<int>> RolandoMazeGen::createMatrix(unsigned int row, unsigned int col)
{
	maxRows = row;
	maxCols = col;

	std::vector<std::vector<int>> matrix(maxRows, std::vector<int>(maxCols));

	for (int i = 0; i < maxRows; i++)
	{
		for (int j = 0; j < maxCols; j++)
		{
			matrix[i][j] = 0;
		}
	}
	return matrix;
}

// return a bool True if valid to remove wall up and cell up is empty
bool RolandoMazeGen::checkValidUp(unsigned int currentRow, unsigned int currentCol, std::vector<std::vector<int>>& matrix)
{
	if (currentRow == 0 || matrix[currentRow-1][currentCol] == 1){return false;}
	else {return true;}
}

// return a bool True if valid to remove wall down AND cell down is empty
bool RolandoMazeGen::checkValidDown(unsigned int currentRow, unsigned int currentCol, std::vector<std::vector<int>>& matrix)
{
	if (currentRow == maxRows-1 || matrix[currentRow+1][currentCol] == 1){return false;}
	else {return true;}
}


// return a bool True if valid to remove wall left and cell is empty
bool RolandoMazeGen::checkValidLeft(unsigned int currentRow, unsigned int currentCol, std::vector<std::vector<int>>& matrix)
{
	if (currentCol == 0 || matrix[currentRow][currentCol-1] == 1){return false;}
	else {return true;}
}

// return a bool True if valid to remove wall right and cell is empty
bool RolandoMazeGen::checkValidRight(unsigned int currentRow, unsigned int currentCol, std::vector<std::vector<int>>& matrix)
{
	if (currentCol == maxCols-1 || matrix[currentRow][currentCol+1] == 1){return false;}
	else {return true;}
}