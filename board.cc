#ifndef SUDOKU_BOARD_CC
#define SUDOKU_BOARD_CC

#include <iostream>
#include "board.hh"

Board::Board()
{
	block_length = 3u;
	board_length = 9u;
	
	sudoku_board = new int*[board_length];
	for(unsigned int i = 0; i < board_length; i++)
	{
		sudoku_board[i] = new int[board_length];
	}
	ClearBoard();
	
	row_name = new char[9] { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I' };
}

Board::~Board()
{
	for(unsigned int i = 0; i < board_length; i++)
	{
		delete[] sudoku_board[i];
	}
	delete[] sudoku_board;
	delete[] row_name;
}

void Board::SetBoard(int **board)
{
	for(unsigned int i = 0; i < board_length; i++)
	{
		for(unsigned int j = 0; j < board_length; j++)
		{
			sudoku_board[i][j] = board[i][j];
		}
	}
}

void Board::SetRow(unsigned int row_num, int row[])
{
	for(unsigned int i = 0; i < board_length; i++)
	{
		sudoku_board[row_num][i] = row[i];
	}
}

void Board::SetColumn(unsigned int column_num, int column[])
{
	for(unsigned int i = 0; i < board_length; i++)
	{
		sudoku_board[i][column_num] = column[i];
	}
}

void Board::ClearBoard()
{
	for(unsigned int i = 0; i < board_length; i++)
	{
		for(unsigned int j = 0; j < board_length; j++)
		{
			sudoku_board[i][j] = 0;
		}
	}
}

bool Board::ValidateBoard(bool display)// = false)
{
	bool valid = true;
	
	for(unsigned int i = 0; i < board_length; i++)
	{
		if(!ValidateRow(i, display)) { valid = false; }
	}
	
	for(unsigned int i = 0; i < board_length; i++)
	{
		if(!ValidateColumn(i, display)) { valid = false; }
	}
	
	for(unsigned int i = 0; i < board_length; i++)
	{
		if(!ValidateBlock(i, display)) { valid = false; }
	}
	
	if(display)
	{
		if(valid) { printf("This is a valid board.\n"); }
		else { printf("This is not a valid board.\n"); }
	}
	return valid;
}

bool Board::ValidateRow(unsigned int row, bool display)// = false)
{
	if(row > 8)
	{
		if(display) { printf("Row %i is not a valid row number.\n", row); }
		return false;
	}
	
	int *validation = new int[board_length + 1];
	for(unsigned int i = 0; i <= board_length; i++) // initialize array
	{
		validation[i] = 0;
	}
	
	// count occurences of numbers
	for(unsigned int i = 0; i < board_length; i++)
	{
		int num = sudoku_board[row][i];
		if(num > 9 || num < 1) { continue; }
		validation[num]++;
	}
	
	// validation phase
	if(validation[0] != 0) // there should be no zeros
	{
		if(display) { printf("Row %c is invalid.\n", row_name[row]); }
		return false;
	}
	for(unsigned int i = 1; i <= board_length; i++)
	{
		if(validation[i] != 1) // there should be no duplicates
		{
			if(display) { printf("Row %c is invalid.\n", row_name[row]); }
			return false;
		}
	}
	
	if(display) { printf("Row %c is valid.\n", row_name[row]); }
	return true;
}

bool Board::ValidateColumn(unsigned int column, bool display)// = false)
{
	if(column > 8)
	{
		if(display) { printf("Column %i is not a valid column number.\n", column + 1); }
		return false;
	}
	
	int *validation = new int[board_length + 1];
	for(unsigned int i = 0; i <= board_length; i++) // initialize array
	{
		validation[i] = 0;
	}
	
	// count occurences of numbers
	for(unsigned int i = 0; i < board_length; i++)
	{
		int num = sudoku_board[i][column];
		if(num > 9 || num < 1) { continue; }
		validation[num]++;
	}
	
	// validation phase
	if(validation[0] != 0) // there should be no zeros
	{
		if(display) { printf("Column %i is invalid.\n", column + 1); }
		return false;
	}
	for(unsigned int i = 1; i <= board_length; i++)
	{
		if(validation[i] != 1) // there should be no duplicates
		{
			if(display) { printf("Column %i is invalid.\n", column + 1); }
			return false;
		}
	}
	
	if(display) { printf("Column %i is valid.\n", column + 1); }
	return true;
}

bool Board::ValidateBlock(unsigned int block, bool display)// = false)
{
	if(block > 8)
	{
		if(display) { printf("Block %i is not a valid block number.\n", block + 1); }
		return false;
	}
	
	int *validation = new int[board_length + 1];
	int row;
	int column;
	int row_shift = (block / 3) * 3;
	int col_shift = (block % 3) * 3;
	
	for(unsigned int i = 0; i <= board_length; i++) // initialize array
	{
		validation[i] = 0;
	}
	
	// count occurences of numbers
	for(unsigned int i = 0; i < board_length; i++) //todo
	{
		column = i % 3 + col_shift;
		if(i < 3) { row = 0 + row_shift; }
		else if(i < 6){ row = 1 + row_shift; }
		else if(i < 9){ row = 2 + row_shift; }
		
		int num = sudoku_board[row][column];
		if(num > 9 || num < 1) { continue; }
		validation[num]++;
	}
	
	// validation phase
	if(validation[0] != 0) // there should be no zeros
	{
		if(display) { printf("Block %i is invalid.\n", block + 1); }
		return false;
	}
	for(unsigned int i = 1; i <= board_length; i++)
	{
		if(validation[i] != 1) // there should be no duplicates
		{
			if(display) { printf("Block %i is invalid.\n", block + 1); }
			return false;
		}
	}
	
	if(display) { printf("Block %i is valid.\n", block + 1); }
	return true;
}

void Board::PrintBoard()
{
	std::cout << "Sudoku Board\n";
	std::cout << "  ";
	for(unsigned int i = 1; i <= board_length; i++)
	{
		std::cout << i << " ";
	}
	std::endl(std::cout);
	
	//char alpha[9] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I' };
	for(unsigned int i = 0; i < board_length; i++)
	{
		std::cout << row_name[i] << " ";
		for(unsigned int j = 0; j < board_length; j++)
		{
			std::cout << sudoku_board[i][j] << " ";
		}
		std::endl(std::cout);
	}
}

#endif
