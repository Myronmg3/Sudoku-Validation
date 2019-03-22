#pragma once
#ifndef SUDOKU_BOARD_HH
#define SUDOKU_BOARD_HH

#define NUM_OF_COLUMNS 9
#define NUM_OF_ROWS 9
#define NUM_OF_BLOCKS 9

// description: This class represents a Sudoku Board. It will have 9 rows and
//	9 columns. The board can only 
class Board
{
	/******************************Attributes*******************************/
	
	// description: The sudoku board which consists of 9 rows and 9 columns
	private: int **sudoku_board;
	private: char *row_name;
	
	/*******************************Methods*********************************/
	
	// description: Constructor
	public: Board();
	
	// description: Destructor
	public: ~Board();
	
	// description: Sets sudoku board to given
	// param[in] board: Two dimensional array to copy values to sudoku_board.
	public: void SetBoard(int **board);
	
	// description: Sets a specified row to values given.
	// param[in] row_num: The row of sudoku_board to be changed/set.
	// param[in] row: The array to copy its values to a row in sudoku_board.
	public: void SetRow(unsigned int row_num, int row[]);
	
	// description: Sets a specified column to values given.
	// param[in] column_num: The column of sudoku_board to be changed/set.
	// param[in] column: The array to copy its values to a column in sudoku_board.
	public: void SetColumn(unsigned int column_num, int column[]);
	
	// description: Empties the contents of the sudoku board.
	public: void ClearBoard();
	
	// description: Checks the validity of the sudoku board.
	// param[in] (optional)display: Indicates to print message of results.
	// return: True if sudoku board is valid.
	public: bool ValidateBoard(bool display = false);
	
	// description: Checks validity of a row.
	// param[in] row: The row number [0-8] to check.
	// param[in] (optional)display: Indicates to print message of results.
	// return: True if row is valid.
	public: bool ValidateRow(unsigned int row, bool display = false);
	
	// description: Checks validity of a column.
	// param[in] column: The column number [0-8] to check.
	// param[in] (optional)display: Indicates to print message of results.
	// return: True if column is valid.
	public: bool ValidateColumn(unsigned int column, bool display = false);
	
	// description: Checks correctness of a block.
	// param[in] block: The block number [0-8] to check.
	// param[in] (optional)display: Indicates to print message of results.
	// return: True if block is valid.
	public: bool ValidateBlock(unsigned int block, bool display = false);
	
	// description: Displays Sudoku board.
	public: void PrintBoard();
};
#endif
