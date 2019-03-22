#include <omp.h>
#include <iostream>
#include "board.hh"

int main()
{
	Board b;
	int arr[9] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	int arr2[9] = { 4, 5, 6, 7, 8, 9, 1, 2, 3 };
	int arr3[9] = { 7, 8, 9, 1, 2, 3, 4, 5, 6 };
	
	//b.PrintBoard();
	b.SetRow(0, arr);
	b.SetRow(2, arr2);
	b.SetRow(1, arr3);
	//b.PrintBoard();
	b.SetColumn(5, arr);
	b.PrintBoard();
	
	if(b.ValidateColumn(5)) std::cout << "Yahoozie!\n";
	if(b.ValidateColumn(9, true)) std::cout << "Yahoozie!\n";
	b.ValidateColumn(5, true);
	
	if(b.ValidateBoard()) std::cout << "Giggity! ;)\n";
	else std::cout << "Aww shucks! :(\n";
	
	b.ValidateBoard(true);
	
	b.ClearBoard();
	b.PrintBoard();
	return 0;
}
