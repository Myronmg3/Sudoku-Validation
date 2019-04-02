#pragma once
#ifndef SUDOKU_BOARD_HH
#define SUDOKU_BOARD_HH

// description: This class represents a Sudoku Board. It will have 9 rows and
//	9 columns. The board can only 
class Board
{
	/******************************Attributes*******************************/
	
	// description: The sudoku board which consists of 9 rows and 9 columns
	private: int **sudoku_board;
	
	// description:
	private: char *row_name;
	
	// description: The length of a block on the sudoku board.
	private: unsigned int block_length;
	
	// description: The total length of the sudoku board.
	private: unsigned int board_length;
	
	// description: The number of threads used for validation.
	private: unsigned int num_threads;
	
	// description: Indicates if boards are longer than 26 units.
	private: bool big_board;
	
	/*******************************Methods*********************************/
	
	// description: Constructor
	public: Board();
	
	// description: Constructor
	// param[in] block_length: Length of a block on the sudoku board.
	public: Board(unsigned int block_length);
	
	// description: Constructor
	// param[in] block_length: Length of a block on the sudoku board.
	// param[in] num_threads: The number of threads used for validation.
	public: Board(unsigned int block_length, unsigned int num_threads);
	
	// description: Destructor
	public: ~Board();
	
	// description: Returns the value of block_length.
	// return: Value of block_length.
	public: unsigned int GetBlockLength();
	
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
	
	// description: Sets the number of threads to be used during validation.
	// param[in] num: The number threads to be used.
	public: void SetNumThreads(unsigned int num);
	
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
	
	// description: Calculates the number of spaces a number occupies.
	// param[in] num: The number to be analyzed.
	// return: The number of spaces the number occupies.
	private: unsigned int CalculateSpaces(unsigned int num);
	
	// description: Adds spaces to display.
	// param[in] num: The number of spaces to be added.
	private: void AddSpaces(unsigned int num);
};
#endif
