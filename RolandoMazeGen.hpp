// RolandoMazeGen.hpp

#ifndef ROLANDOMAZEGEN_HPP
#define ROLANDOMAZEGEN_HPP

#include "MazeGenerator.hpp"
#include "Maze.hpp"
#include <random>
#include <vector>


class RolandoMazeGen : public MazeGenerator
{
public:
    // make the maze 
	void generateMaze(Maze& maze) override;

    // Recursion!
	void recursiveCall(Maze& maze, std::vector<std::vector<int>>& matrix, 
		unsigned int currentRow, unsigned int currentCol);

	// 0 means unvisited but 1 means visited
	std::vector<std::vector<int>> createMatrix(unsigned int row, unsigned int col);

	// return a bool True if valid to remove wall up and cell up is empty
	bool checkValidUp(unsigned int currentRow, unsigned int currentCol, std::vector<std::vector<int>>& matrix);

	// return a bool True if valid to remove wall down AND cell down is empty
	bool checkValidDown(unsigned int currentRow, unsigned int currentCol, std::vector<std::vector<int>>& matrix);


	// return a bool True if valid to remove wall left and cell is empty
	bool checkValidLeft(unsigned int currentRow, unsigned int currentCol, std::vector<std::vector<int>>& matrix);

	// return a bool True if valid to remove wall right and cell is empty
	bool checkValidRight(unsigned int currentRow, unsigned int currentCol, std::vector<std::vector<int>>& matrix);
};

#endif