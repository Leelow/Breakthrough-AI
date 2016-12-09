#pragma once

#include "stdafx.h"
#include <iostream>
#include <sstream>
#include <string>
#include "json.hpp"

#include "Board.h"

using namespace std;
using json = nlohmann::json;

typedef string Color;
typedef struct {
	int column;
	int row;
} Position;

#define WHITE Color("white");
#define BLACK Color("black");

class Socket
{

	Board board;

public:
	Socket(Board board) { board: board; };
	void on(string input);
	void emit(string eventName, json data);
	void emitMove(string color, Position from, Position to);
	void onWhiteMove(Position from, Position to);
	void onBlackMove(Position from, Position to);
	void emitWhiteMove(Position from, Position to);
	void emitWhiteMove(int xFrom, int yFrom, int xTo, int yTo);
	void emitBlackMove(Position from, Position to);
	void emitBlackMove(int xFrom, int yFrom, int xTo, int yTo);
};