// RolandoMazeSolver.hpp

#ifndef ROLANDOMAZESOLVER_HPP
#define ROLANDOMAZESOLVER_HPP

#include "MazeSolver.hpp"
#include "MazeSolution.hpp"
#include "Maze.hpp"
#include <vector>

class RolandoMazeSolver : public MazeSolver
{
public:
    // Solve using a red dash/line tracker in the generated maze
	void solveMaze(const Maze& maze, MazeSolution& mazeSolution) override;

	// makes a vector of int vectors to keep track of where we have been
	std::vector<std::vector<int>> makeMatrixx(unsigned int row, unsigned int col);

	// the recursion functions that keeps going and backing up until it finds a single path
	void recursion(const Maze& maze, MazeSolution& mazeSolution, std::vector<std::vector<int>> matrix,
		unsigned int currentRow, unsigned int currentCol);

	// return a bool True if valid to remove wall up and cell up is empty
	bool checkValidLeft(unsigned int currentRow, unsigned int currentCol, std::vector<std::vector<int>>& matrix, const Maze& maze);

	// return a bool True if valid to remove wall down AND cell down is empty
	bool checkValidRight(unsigned int currentRow, unsigned int currentCol, std::vector<std::vector<int>>& matrix, const Maze& maze);

	// return a bool True if valid to remove wall left and cell is empty
	bool checkValidUp(unsigned int currentRow, unsigned int currentCol, std::vector<std::vector<int>>& matrix, const Maze& maze);

	// return a bool True if valid to remove wall right and cell is empty
	bool checkValidDown(unsigned int currentRow, unsigned int currentCol, std::vector<std::vector<int>>& matrix, const Maze& maze);

private:
	bool solutionFound;

};

#endif