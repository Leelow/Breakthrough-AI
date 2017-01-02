#pragma once

#define BOARD_SIZE 8
#define EMPTY_CASE 0
#define BLACK_PAWN 1
#define WHITE_PAWN 2

#include <vector>
#include <iostream>
#include <time.h>
#include <string>

using namespace std;

typedef struct {
	int column;
	int row;
	int color;
} Pawn;

typedef struct {
	int column;
	int row;
} Case;

class Board
{
	vector<vector<int>> cases;

public:
	Board();
	Pawn getPawn(int column, int row);
	vector<Case> getAvailableMoves(Pawn p);
	Pawn getRandomPawn(int color);
	Pawn movePawn(Pawn p, int column, int row);
	string toString();
};