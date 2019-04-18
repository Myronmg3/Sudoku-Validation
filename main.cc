#include <iostream>
#include "board.hh"

// Description: At most three arguments should be passed in from user.
//		1. The length of a block on the sudoku board. Typical sudoku board
//			has a block length of 3.
//		2. The number of threads to run the validator with.
//		3. A flag to indicate to display sudoku board. 0 represents false,
//			1 (or any other number) represents true.  
int main(int argc, char **argv)
{
	unsigned int length = 3;
	unsigned int threads = 1;
	bool show_board = false;
	if(argc == 2) { length = (unsigned int)atoi(argv[1]); }
	else if(argc == 3) 
	{
		length = (unsigned int)atoi(argv[1]);
		threads = (unsigned int)atoi(argv[2]);
	}
	else if(argc == 4)
	{
		length = (unsigned int)atoi(argv[1]);
		threads = (unsigned int)atoi(argv[2]);
		show_board = (atoi(argv[3]) == 0) ? false : true;
	}
	
	Board b(length, threads);
	unsigned int block_length = b.GetBlockLength();
	unsigned int board_length = block_length * block_length;
	int **board = new int*[board_length];
	int num;
	for(unsigned int i = 0, shift = 0; i < board_length; i++, shift += block_length)
	{
		if(i != 0 && i % block_length == 0) { shift++; }
		board[i] = new int[board_length];
		for(unsigned int j = 0; j < board_length; j++)
		{
			num = (j + shift) % board_length + 1;
			board[i][j] = num;
		}
	}
	b.SetBoard(board);
	
	if(b.ValidateBoard()) std::cout << "Giggity! ;)\n";
	else std::cout << "Aww shucks! :(\n";
	b.ValidateBoardSingle();
	if(show_board) { b.PrintBoard(); }
	return 0;
}
