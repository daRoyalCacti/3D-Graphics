#pragma once
#include <iostream>
#include <cstring>

#define refactoring

#define rows 9
#define cols 9
#define size 81

uint8_t board[rows][cols] = //normally hard
{
	{0, 0, 0, 8, 0, 1, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 4, 3},
	{5, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 7, 0, 8, 0, 0},
	{0, 0, 0, 0, 0, 0, 1, 0, 0},
	{0, 2, 0, 0, 3, 0, 0, 0, 0},
	{6, 0, 0, 0, 0, 0, 0, 7, 5},
	{0, 0, 3, 4, 0, 0, 0, 0, 0},
	{0, 0, 0, 2, 0, 0, 6, 0, 0}
};


inline void print_board(uint8_t board[rows][cols]) { //prints the sudoku to console
	for (size_t j = 0; j < cols * 4; j++) std::cout << "-"; std::cout << std::endl; //top line

	for (size_t i = 0; i < rows; i++) {
		for (size_t j = 0; j < cols; j++) {
			if (j % 3 == 0) std::cout << "|  "; // vertical lines
			if (board[i][j] != 0) std::cout << static_cast<unsigned>(board[i][j]) << "  "; //the actual number
			else std::cout << "   "; //dont't print 0's - they are unsolved squares
		}
		std::cout << "|\n";
		if (i + 1 != rows && i % 3 != 2) for (size_t j = 0; j <= rows / 3; j++) std::cout << "|           "; // the vertical lines in linespacing
		std::cout << std::endl;

		if (i % 3 == 2) { for (size_t j = 0; j < cols * 4; j++) std::cout << "-"; std::cout << std::endl; } //the horizontal lines

	}


}

inline bool isValid(uint8_t board[rows][cols], uint8_t posx, uint8_t posy, uint8_t hor_box, uint8_t vert_box) { //checks if the value in a given square is valid
	//col
	for (size_t i = 0; i < posy; i++) { //moving down
		if (board[posx][i] == board[posx][posy]) return false;
	}
	for (size_t i = posy + 1; i < cols; i++) { //moving down
		if (board[posx][i] == board[posx][posy]) return false;
	}

	//row
	for (size_t i = 0; i < posx; i++) { //moving left
		if (board[i][posy] == board[posx][posy]) return false;
	}
	for (size_t i = posx + 1; i < cols; i++) {
		if (board[i][posy] == board[posx][posy]) return false;
	}

	//is bad \/
	for (size_t i = hor_box ; i < hor_box + 3u; i++) {
		for (size_t j = vert_box; j < vert_box + 3u; j++) {
			if (i != posx && j != posy && board[i][j] == board[posx][posy]) return false;
		}
	}

	return true;
}


void toSolve(uint8_t board[rows][cols], uint8_t* solveArrayx, uint8_t* solveArrayy) { //creates an array of given numbers with some extra values for error checking

	//initial values to check if no solution
	solveArrayx[0] = UINT8_MAX - 1;
	solveArrayy[0] = UINT8_MAX - 1;

	uint8_t counter = 0;
	//creating an array of given numbers
	for (uint8_t i = 0; i < rows; i++) {
		for (uint8_t j = 0; j < cols; j++) {
			//zero elements are what are being found
			if (board[i][j] == 0) {
				solveArrayx[++counter] = i; solveArrayy[counter] = j;
			}
		}
	}

	//very large values so the while loop check below will be true

	for (uint8_t i = ++counter; i < rows * cols; i++) {
		solveArrayx[i] = UINT8_MAX;
		solveArrayy[i] = UINT8_MAX;
	}


}


void generateBox(uint8_t* hor_box, uint8_t* vert_box) {
	for (int i = 0; i < rows; i++) {
		hor_box[i] = static_cast<uint8_t>((i) / (float)rows * 3) * 3u;
	}

	for (int i = 0; i < cols; i++) {
		vert_box[i] = static_cast<uint8_t>((i) / (float)cols * 3) * 3u;
	}
}


void solve(uint8_t board[rows][cols]) { //solves the sudoku using backtracking

	uint8_t solveArrayx[size + 1], solveArrayy[size + 1];
	toSolve(board, solveArrayx, solveArrayy);

	uint8_t hor_box[rows], vert_box[cols];
	generateBox(hor_box, vert_box);

	uint8_t* ptrx = &solveArrayx[1], *ptry = &solveArrayy[1];


	while (*ptry <= size + 1) {//|| *ptrx <= size + 1) {

		if (++board[*ptrx][*ptry] == 10) {
			board[*ptrx][*ptry] = 0;
			ptrx--;
			ptry--;

		}
		else 	if (isValid(board, *ptrx, *ptry, hor_box[*ptrx], vert_box[*ptry])) {
			ptrx++;
			ptry++;
		}

	}

	if (*ptry == UINT8_MAX - 1 || *ptrx == UINT8_MAX - 1)
		std::cerr << "no solution found" << std::endl;
}

int boardValid(uint8_t board[rows][cols]){
	uint8_t hor_box[rows], vert_box[cols];
	generateBox(hor_box, vert_box);

	for (int i = 0; i < rows; i++)
		for (int j = 0; j < cols; j++)
			if (board[i][j] != 0)
				if (!isValid(board, i, j, hor_box[i], vert_box[j]))
					return false;

	return true;
}


/* //made redundent
double mean(double* values, unsigned num) {
	double temp = 0;
	for (unsigned i = 0; i < num; i++) {
		temp += values[i];
	}


	return temp / num;
}



double err(double* values, unsigned num) {
	double av = mean(values, num);
	double temp = 0;
	for (unsigned i = 0; i < num; i++) {
		temp += (values[i] - av) * (values[i] - av);
	}

	return sqrt(temp / ((num - 1) * num));
}
*/
