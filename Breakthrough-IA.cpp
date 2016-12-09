#include "stdafx.h"
#include "Socket.h"
#include "Board.h"

using namespace std;

int main()
{
	string input;
	Board board;
	Socket socket(board);

	while(cin >> input && input.compare("exit") != 0) socket.on(input);

    return 0;
}

