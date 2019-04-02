#include <omp.h>
#include <iostream>
#include "board.hh"

int main()
{
	Board b(7);
	//int arr[9] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	//int arr2[9] = { 4, 5, 6, 7, 8, 9, 1, 2, 3 };
	//int arr3[9] = { 7, 8, 9, 1, 2, 3, 4, 5, 6 };
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
	b.PrintBoard();
	
	//b.SetRow(0, arr);
	//b.SetRow(2, arr2);
	//b.SetRow(1, arr3);
	//b.PrintBoard();
	//b.SetColumn(5, arr);
	//b.PrintBoard();
	
	//if(b.ValidateColumn(5)) std::cout << "Yahoozie!\n";
	//if(b.ValidateColumn(9, true)) std::cout << "Yahoozie!\n";
	//b.ValidateColumn(5, true);
	
	if(b.ValidateBoard()) std::cout << "Giggity! ;)\n";
	else std::cout << "Aww shucks! :(\n";
	
	b.ValidateBoard(true);
	
	b.ClearBoard();
	b.PrintBoard();
	return 0;
}
