#include "stdafx.h"
#include "Board.h"

Board::Board() {
	cases = vector<vector<int>>();

	srand(time(NULL));

	for (int i = 0; i < BOARD_SIZE; ++i) {
		cases.push_back(vector<int>());
		for (int j = 0; j < BOARD_SIZE; ++j) {
			int value = EMPTY_CASE;
			if (i == 0 || i == 1) value = BLACK_PAWN;
			else if (i == 6 || i == 7) value = WHITE_PAWN;
			cases[i].push_back(value);
		}
	}
}

Pawn Board::getPawn(int column, int row) {
	return{ column, row, cases[row][column] };
}

vector<Case> Board::getAvailableMoves(Pawn p) {
	vector<Case> moves = vector<Case>();

	if (p.color == BLACK_PAWN) {
		if (p.column > 0 && cases[p.row + 1][p.column - 1] != BLACK_PAWN) moves.push_back({ p.column - 1, p.row + 1 });
		if (cases[p.row + 1][p.column] == EMPTY_CASE) moves.push_back({ p.column, p.row + 1 });
		if (p.column < BOARD_SIZE - 1 && cases[p.row + 1][p.column + 1] != BLACK_PAWN) moves.push_back({ p.column + 1, p.row + 1 });
	}
	else {
		if (p.column > 0 && cases[p.row - 1][p.column - 1] != WHITE_PAWN) moves.push_back({ p.column - 1, p.row - 1 });
		if (cases[p.row - 1][p.column] == EMPTY_CASE) moves.push_back({ p.column, p.row - 1 });
		if (p.column < BOARD_SIZE - 1 && cases[p.row - 1][p.column + 1] != WHITE_PAWN) moves.push_back({ p.column + 1, p.row - 1 });
	}

	return moves;
}

Case Board::getRandomMove(Pawn p) {
	vector<Case> moves = getAvailableMoves(p);
	return moves[rand() % moves.size()];
}

Pawn Board::getRandomPawn(int color) {
	Pawn p;
	bool found = false;
	while (!found) {
		p.column = rand() % BOARD_SIZE;
		p.row = rand() % BOARD_SIZE;
		if (cases[p.row][p.column] == color) found = true;
	}
	p.color = color;
	return p;
}

Pawn Board::movePawn(Pawn p, int column, int row) {
	int pawnColor = cases[p.row][p.column];
	cases[row][column] = pawnColor,
	cases[p.row][p.column] = EMPTY_CASE;
	p.column = column;
	p.row = row;
	return p;
}

string Board::toString() {
	string str = "";
	for (int i = 0; i < BOARD_SIZE; ++i) {
		for (int j = 0; j < BOARD_SIZE; ++j) {
			str += to_string(cases[i][j]) + " ";
		}
		str += "\n";
	}
	return str;
}
