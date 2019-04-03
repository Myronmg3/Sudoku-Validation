#ifndef SUDOKU_BOARD_CC
#define SUDOKU_BOARD_CC

#include <iostream>
#include "board.hh"

Board::Board()
{
	block_length = 3u;
	board_length = 9u;
	num_threads = 1u;
	big_board = false;
	
	sudoku_board = new int*[board_length];
	for(unsigned int i = 0; i < board_length; i++)
	{
		sudoku_board[i] = new int[board_length];
	}
	ClearBoard();
	
	row_name = new char[26];
	for(int i = 0, start = 65; i < 26; i++)
	{
		row_name[i] = char(start + i);
	}
}

Board::Board(unsigned int block_length)
{
	this->block_length = block_length;
	board_length = block_length * block_length;
	num_threads = 1u;
	big_board = (block_length > 5u) ? true : false;
	
	sudoku_board = new int*[board_length];
	for(unsigned int i = 0; i < board_length; i++)
	{
		sudoku_board[i] = new int[board_length];
	}
	ClearBoard();
	
	row_name = new char[26];
	for(int i = 0, start = 65; i < 26; i++)
	{
		row_name[i] = char(start + i);
	}
}

Board::Board(unsigned int block_length, unsigned int num_threads)
{
	this->block_length = block_length;
	board_length = block_length * block_length;
	this->num_threads = num_threads;
	big_board = (block_length > 5u) ? true : false;
	
	sudoku_board = new int*[board_length];
	for(unsigned int i = 0; i < board_length; i++)
	{
		sudoku_board[i] = new int[board_length];
	}
	ClearBoard();
	
	row_name = new char[26];
	for(int i = 0, start = 65; i < 26; i++)
	{
		row_name[i] = char(start + i);
	}
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

unsigned int Board::GetBlockLength()
{
	return block_length;
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

void Board::SetNumThreads(unsigned int num)
{
	num_threads = num;
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
	if(row > board_length - 1)
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
		if(num > (int)board_length || num < 0) { continue; }
		validation[num]++;
	}
	
	// validation phase
	if(validation[0] != 0) // there should be no zeros
	{
		if(display)
		{
			if(!big_board) { printf("Row %c is invalid.\n", row_name[row]); }
			else
			{
				unsigned int index = row / 26u;
				char first_char = (index == 0) ? '\0' : row_name[index - 1];
				index = row % 26u;
				printf("Row %c%c is invalid.\n", first_char, row_name[index]);
			}
		}
		return false;
	}
	for(unsigned int i = 1; i <= board_length; i++)
	{
		if(validation[i] != 1) // there should be no duplicates
		{
			if(display)
			{
				if(!big_board) { printf("Row %c is invalid.\n", row_name[row]); }
				else
				{
					unsigned int index = row / 26u;
					char first_char = (index == 0) ? '\0' : row_name[index - 1];
					index = row % 26u;
					printf("Row %c%c is invalid.\n", first_char, row_name[index]);
				}
			}
			return false;
		}
	}
	
	if(display)
	{
		if(!big_board) { printf("Row %c is valid.\n", row_name[row]); }
		else
		{
			unsigned int index = row / 26u;
			char first_char = (index == 0) ? '\0' : row_name[index - 1];
			index = row % 26u;
			printf("Row %c%c is valid.\n", first_char, row_name[index]);
		}
	}
	return true;
}

bool Board::ValidateColumn(unsigned int column, bool display)// = false)
{
	if(column > board_length - 1)
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
		if(num > (int)board_length || num < 0) { continue; }
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
	if(block > board_length - 1)
	{
		if(display) { printf("Block %i is not a valid block number.\n", block + 1); }
		return false;
	}
	
	int *validation = new int[board_length + 1];
	int row;
	int column;
	int row_shift = (block / block_length) * block_length;
	int col_shift = (block % block_length) * block_length;
	
	for(unsigned int i = 0; i <= board_length; i++) // initialize array
	{
		validation[i] = 0;
	}
	
	// count occurences of numbers
	for(unsigned int i = 0, shift = 0; i < board_length; i++)
	{
		column = i % block_length + col_shift;
		shift = i / block_length;
		row = shift + row_shift;
		
		int num = sudoku_board[row][column];
		if(num > (int)board_length || num < 0) { continue; }
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
	unsigned int max_spaces = CalculateSpaces(board_length);
	unsigned int num_of_spaces, rem_spaces;
	
	unsigned int total_spaces;
	total_spaces = board_length * (max_spaces + 1);
	total_spaces += (big_board) ? 3 : 2;
	total_spaces -= (total_spaces >= 12) ? 12 : total_spaces;
	
	// display board
	AddSpaces(total_spaces / 2u);
	std::cout << "SUDOKU BOARD\n";
	(big_board) ? std::cout << "   " : std::cout<<"  ";
	
	for(unsigned int i = 1; i <= board_length; i++)
	{
		num_of_spaces = CalculateSpaces(i);
		rem_spaces = max_spaces - num_of_spaces;
		std::cout << i;
		AddSpaces(rem_spaces + 1);
	}
	std::endl(std::cout);
	
	int num;
	for(unsigned int i = 0; i < board_length; i++)
	{		
		unsigned int index;
		if(big_board)
		{
			index = i / 26u;
			(index == 0) ? std::cout << ' ' : std::cout << row_name[index - 1];
		}
		index = i % 26u;
		std::cout << row_name[index] << ' ';
		
		for(unsigned int j = 0; j < board_length; j++)
		{
			num = sudoku_board[i][j];
			num_of_spaces = CalculateSpaces(num);
			rem_spaces = max_spaces - num_of_spaces;
			std::cout << num;
			AddSpaces(rem_spaces + 1);
		}
		std::endl(std::cout);
	}
}

unsigned int Board::CalculateSpaces(unsigned int num)
{
	unsigned int spaces = 0, remainder = num;
	do
	{
		spaces++;
		remainder /= 10u;
	}while(remainder > 0);
	
	return spaces;
}

void Board::AddSpaces(unsigned int num)
{
	for(unsigned int i = 0; i < num; i++)
	{
		std::cout<<' ';
	}
}

#endif
