#include "stdafx.h"
#include "Socket.h"

void Socket::onWhiteMove(Position from, Position to) {
	emit("debug", "[HUMAN] White move from (" + to_string(from.column) + ", " + to_string(from.row) + ") to (" + to_string(to.column) + ", " + to_string(to.row) + ")");
	
	// Update white pawn when the human moves it
	Pawn wP = board.getPawn(from.column, from.row);
	board.movePawn(wP, to.column, to.row);

	// Get a random black pawn
	Pawn bP = board.getRandomPawn(BLACK_PAWN);

	// Move randomly
	Case c = board.getRandomMove(bP);
	board.movePawn(bP, c.column, c.row);
	emit("debug", "lol");
	emitBlackMove(bP.column, bP.row, c.column, c.row);
	emit("board", board.toString());
}

void Socket::onBlackMove(Position from, Position to) {
	emit("debug", "[HUMAN] Black move from (" + to_string(from.column) + ", " + to_string(from.row) + ") to (" + to_string(to.column) + ", " + to_string(to.row) + ")");
}

void Socket::emitWhiteMove(Position from, Position to) {
	emitMove("white", from, to);
	emit("debug", "[AI   ] White move from (" + to_string(from.column) + ", " + to_string(from.row) + ") to (" + to_string(to.column) + ", " + to_string(to.row) + ")");
}

void Socket::emitWhiteMove(int xFrom, int yFrom, int xTo, int yTo) {
	emitWhiteMove({ xFrom, yFrom }, { xTo, yTo });

}

void Socket::emitBlackMove(Position from, Position to) {
	emitMove("black", from, to);
	emit("debug", "[AI   ] Black move from (" + to_string(from.column) + ", " + to_string(from.row) + ") to (" + to_string(to.column) + ", " + to_string(to.row) + ")");
}

void Socket::emitBlackMove(int xFrom, int yFrom, int xTo, int yTo) {
	emitBlackMove({ xFrom, yFrom }, { xTo, yTo });
}

void Socket::on(string input) {
	json j = json::parse(input);

	string eventName = j["eventName"];
	json data = j["data"];
	if (eventName.compare("/move") == 0) {
		Position from = { data["from"]["column"], data["from"]["row"] };
		Position to = { data["to"]["column"], data["to"]["row"] };
		if(data["color"] == "white") onWhiteMove(from, to);
		else onBlackMove(from, to);
	}
}

void Socket::emit(string eventName, json data) {
	json o;
	o["eventName"] = eventName;
	o["data"] = data;
	cout << o.dump() << endl;
}

void Socket::emitMove(string color, Position from, Position to) {
	json move, j_from, j_to;
	j_from["column"] = to_string(from.column);
	j_from["row"] = to_string(from.row);
	j_to["column"] = to_string(to.column);
	j_to["row"] = to_string(to.row);
	move["color"] = color;
	move["from"] = j_from;
	move["to"] = j_to;
	emit("/move", move);
}