#include <iostream>

using namespace std;

char letter = 'A';

void rec_boom(char** board, int s_row, int s_col,int e_row, int e_col, int r_blank, int c_blank, int size){
	if(size > 2){
		if(r_blank < s_row+size/2){
			if(c_blank < s_col+size/2){
				rec_boom(board, s_row, 				s_col, 			s_row + size/2 -1, 	s_col + size/2 -1, 	r_blank,			c_blank, 			size/2);
				rec_boom(board, s_row + size/2, 	s_col, 			e_row, 				s_col + size/2 -1, 	s_row + size/2,		s_col + size/2 -1,	size/2);
				rec_boom(board, s_row, 				s_col + size/2, s_row + size/2 -1, 	e_col, 				s_row + size/2 -1,	s_col + size/2,		size/2);
				rec_boom(board, s_row + size/2,		s_col + size/2,	e_row,			 	e_col,			 	s_row + size/2,		s_col + size/2,		size/2);
				board[s_row+size/2][s_col + size/2 -1] = letter;
				board[s_row + size/2 -1][s_col+size/2] = letter;
				board[s_row+size/2][s_col+size/2] = letter;
				letter++;
			} else {
				rec_boom(board, s_row, 			s_col, 			s_row + size/2 -1, 	s_col + size/2 -1, 	s_row + size/2 -1,	s_col + size/2 -1, 	size/2);
				rec_boom(board, s_row + size/2, s_col, 			e_row, 				s_col + size/2 -1, 	s_row + size/2,		s_col + size/2 -1, 	size/2);
				rec_boom(board, s_row, 			s_col + size/2, s_row + size/2 -1, 	e_col, 				r_blank,			c_blank,	 		size/2);
				rec_boom(board, s_row + size/2,	s_col + size/2,	e_row,			 	e_col,	 			s_row + size/2,		s_col + size/2,		size/2);
				board[s_row+size/2][s_col + size/2 -1] = letter;
				board[s_row + size/2 -1][s_col + size/2 -1] = letter;
				board[s_row+size/2][s_col+size/2] = letter;
				letter++;
			}
		} else {
			if(c_blank < s_col+size/2){
				rec_boom(board, s_row, 				s_col, 			s_row + size/2 -1, 	s_col + size/2 -1, 	s_row + size/2 -1,	s_col + size/2 -1, 	size/2);
				rec_boom(board, s_row + size/2, 	s_col, 			e_row, 				s_col + size/2 -1, 	r_blank,			c_blank, 			size/2);
				rec_boom(board, s_row, 				s_col + size/2, s_row + size/2 -1, 	e_col, 				s_row + size/2 -1,	s_col + size/2,		size/2);
				rec_boom(board, s_row + size/2,		s_col + size/2,	e_row,	 			e_col,			 	s_row + size/2,		s_col + size/2,		size/2);	
				board[s_row + size/2 -1][s_col + size/2 -1] = letter;
				board[s_row + size/2 -1][s_col+size/2] = letter;
				board[s_row+size/2][s_col+size/2] = letter;
				letter++;
			} else {
				rec_boom(board, s_row, 				s_col, 			s_row + size/2 -1, 	s_col + size/2 -1, 	s_row + size/2 -1,	s_col + size/2 -1, 	size/2);
				rec_boom(board, s_row/2 + size/2, 	s_col, 			e_row,		 		s_col + size/2 -1, 	s_row + size/2,		s_col + size/2 -1, 	size/2);
				rec_boom(board, s_row, 				s_col + size/2, s_row + size/2 -1, 	e_col, 				s_row + size/2 -1,	s_col + size/2,		size/2);
				rec_boom(board, s_row + size/2,		s_col + size/2,	e_row,	 			e_col,			 	r_blank,			c_blank,			size/2);	
				board[s_row+size/2][s_col + size/2 -1] = letter;
				board[s_row + size/2 -1][s_col+size/2] = letter;
				board[s_row + size/2 -1][s_col + size/2 -1] = letter;
				letter++;
			}
		}
	} else {
		if(s_row != r_blank || s_col != c_blank)
			board[s_row][s_col] = letter;
		if(s_row != r_blank || e_col != c_blank)
			board[s_row][e_col] = letter;
		if(e_row != r_blank || s_col != c_blank)
			board[e_row][s_col] = letter;
		if(e_row != r_blank || e_col != c_blank)
			board[e_row][e_col] = letter;
		letter++;
	}
}
	
int main(int argc, char const *argv[])
{
	int size, r_blank, c_blank;
	char** board;
	cout << "Enter number of rows: ";
	cin >> size;
	cout << "Enter row number between 0 and " << size - 1 << ": ";
	cin >> r_blank;
	cout << "Enter column number between 0 and " << size - 1 << ": ";
	cin >> c_blank;

	board = new char*[size];
	for(int i  = 0; i < size; i++){
		board[i] = new char[size];
	}
	for(int i = 0; i < size; i++){
		for (int j = 0; j < size; ++j)
		{
			board[i][j] = '-';
		}
	}

	rec_boom(board, 0,0,size-1,size-1,r_blank,c_blank,size);
	for(int i = 0; i < size; i++){
		for (int j = 0; j < size; ++j)
		{
			cout << board[i][j] << " ";
		}
		cout << endl;
	}
	return 0;
}