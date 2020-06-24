#include "game.h"
#include <iostream>

Game::Game() :
	gameTree{}
{
}

//********************************************************************************************************************
//********************************************************************************************************************

void Game::generateBestMoves() {
	Coords allMoves[ALL_SQUARES];
	int allMovesCount{ 0 };

	gameTree.dfsTraverse(0, 0, allMoves, allMovesCount);
	gameTree.collectBestMoves();
	gameTree.outputResults();
}

//********************************************************************************************************************
//********************************************************************************************************************

void Game::playGameWithGeneratedMoves() const {
	Board gameBoard;

	while (gameBoard.hasFlag(BOARD_STATUS_IN_PROGRESS)) {
		const Coords aiMove = BEST_MOVES.at({ gameBoard.getBoard(0), gameBoard.getBoard(1) });
		gameBoard.playMove(aiMove);
		std::cout << gameBoard << std::endl;
		std::cout << "AI Moved: " << aiMove << std::endl << std::endl;

		if (gameBoard.hasFlag(BOARD_STATUS_IN_PROGRESS)) {
			Coords yourMove;
			std::cout << "Make move: ";
			std::cin >> yourMove.rowIdx;
			std::cin >> yourMove.colIdx;

			gameBoard.playMove(yourMove);
			std::cout << gameBoard << std::endl;
		}
	}

	if (gameBoard.hasFlag(BOARD_STATUS_X_WINS)) {
		std::cout << "AI WINS!" << std::endl;
	}
	else if (gameBoard.hasFlag(BOARD_STATUS_O_WINS)) {
		std::cout << "YOU WIN!" << std::endl;
	}
	else {
		std::cout << "DRAW!" << std::endl;
	}
}
