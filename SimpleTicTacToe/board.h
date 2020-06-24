#pragma once

#include "constants.h"
#include "coords.h"
#include <fstream>

class Board {
public:
	Board();
	Board(const Board& board);
	Board(const short xBoard, const short oBoard);

	void setScore(const short score);
	short getScore() const;

	/// Return player board with the given index
	short getBoard(const short boardIdx) const;

	/// Return the status of the board
	unsigned short getStatus() const;

	/// Flag helpers
	bool hasFlag(const unsigned short flag) const;
	void setFlag(const unsigned short flag);
	void unsetFlag(const unsigned short flag);

	/// Fill all possible moves in the given array
	/// @param[in] allMoves the array tp be filled
	/// @param[in] allMovesCount the count to be set for all moves
	void getAllPossibleMoves(Coords(&allMoves)[ALL_SQUARES], int& allMovesCount) const;

	/// Apply the given move on the board, considering which player is to move
	/// @param[in] move the move to apply
	void playMove(const Coords move);

	/// Check if the given board has a winning pattern
	/// @param[in] boardIdxToCheck the borad to check
	void checkForWin(const int boardIdxToCheck);

	/// Check if the board is draw if noone wins
	void checkForDraw();

	friend std::ostream& operator<<(std::ostream& stream, const Board& board);

private:
	short board[SQUARE_TYPES]; ///< Two bit masks showing where each player has played
	short score; ///< The score for the board
	unsigned short flags; ///< Flags identifying the state of the board
};
