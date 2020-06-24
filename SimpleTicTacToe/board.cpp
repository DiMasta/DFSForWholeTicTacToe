#include "board.h"

Board::Board() :
	flags{ 0 },
	score{ INVALID_SCORE }
{
	for (int boardIdx = 0; boardIdx < SQUARE_TYPES; ++boardIdx) {
		board[boardIdx] = EMPTY_TICTACTOE_BOARD;
	}

	setFlag(BOARD_STATUS_IN_PROGRESS);
	setFlag(X_TO_MOVE);
}

//********************************************************************************************************************
//********************************************************************************************************************

Board::Board(const Board& board) {
	for (int boardIdx = 0; boardIdx < SQUARE_TYPES; ++boardIdx) {
		this->board[boardIdx] = board.board[boardIdx];
	}

	this->flags = board.flags;
	this->score = board.score;
}

//********************************************************************************************************************
//********************************************************************************************************************

Board::Board(const short xBoard, const short oBoard) :
	flags{ 0 },
	score{ INVALID_SCORE }
{
	board[0] = xBoard;
	board[1] = oBoard;

	setFlag(BOARD_STATUS_IN_PROGRESS);
	setFlag(X_TO_MOVE);
}

//********************************************************************************************************************
//********************************************************************************************************************

void Board::setScore(const short score) {
	this->score = score;
}

//********************************************************************************************************************
//********************************************************************************************************************

short Board::getScore() const {
	return score;
}

//********************************************************************************************************************
//********************************************************************************************************************

short Board::getBoard(const short boardIdx) const {
	return board[boardIdx];
}

//********************************************************************************************************************
//********************************************************************************************************************

unsigned short Board::getStatus() const {
	unsigned short status = BOARD_STATUS_IN_PROGRESS;

	if (hasFlag(BOARD_STATUS_X_WINS)) {
		status = BOARD_STATUS_X_WINS;
	}
	else if (hasFlag(BOARD_STATUS_O_WINS)) {
		status = BOARD_STATUS_O_WINS;
	}
	else if (hasFlag(BOARD_STATUS_DRAW)) {
		status = BOARD_STATUS_DRAW;
	}

	return status;
}

//********************************************************************************************************************
//********************************************************************************************************************

bool Board::hasFlag(const unsigned short flag) const {
	return flags & flag;
}

//********************************************************************************************************************
//********************************************************************************************************************

void Board::setFlag(const unsigned short flag) {
	flags |= flag;
}

//********************************************************************************************************************
//********************************************************************************************************************

void Board::unsetFlag(const unsigned short flag) {
	flags &= ~flag;
}

//********************************************************************************************************************
//********************************************************************************************************************

void Board::getAllPossibleMoves(Coords(&allMoves)[ALL_SQUARES], int& allMovesCount) const {
	allMovesCount = 0;

	for (int squareIdx = 0; squareIdx < ALL_SQUARES; ++squareIdx) {
		const short squareMask = 1 << squareIdx;

		if (!(board[0] & squareMask) && !(board[1] & squareMask)) {
			allMoves[allMovesCount] = { squareIdx / BOARD_DIM, squareIdx % BOARD_DIM };
			++allMovesCount;
		}
	}
}

//********************************************************************************************************************
//********************************************************************************************************************

void Board::playMove(const Coords move) {
	const int squareIdx = (move.rowIdx * BOARD_DIM) + move.colIdx;

	if (hasFlag(X_TO_MOVE)) {
		board[X_SQUARE] |= 1 << squareIdx;
		checkForWin(X_SQUARE);
		unsetFlag(X_TO_MOVE);
	}
	else {
		board[O_SQUARE] |= 1 << squareIdx;
		checkForWin(O_SQUARE);
		setFlag(X_TO_MOVE);
	}

	checkForDraw();
}

//********************************************************************************************************************
//********************************************************************************************************************

void Board::checkForWin(const int boardIdxToCheck) {
	for (int winMaskIdx = 0; winMaskIdx < WIN_MASKS_COUNT; ++winMaskIdx) {
		if (WIN_MASKS[winMaskIdx] == (board[boardIdxToCheck] & WIN_MASKS[winMaskIdx])) {
			unsetFlag(BOARD_STATUS_IN_PROGRESS);
			if (X_SQUARE == boardIdxToCheck) {
				setFlag(BOARD_STATUS_X_WINS);
				score = X_WINS_SCORE;
			}
			else {
				setFlag(BOARD_STATUS_O_WINS);
				score = O_WINS_SCORE;
			}

			break; // TODO: not sure if this will break gcc automatic vectorization
		}
	}
}

//********************************************************************************************************************
//********************************************************************************************************************

void Board::checkForDraw() {
	if (hasFlag(BOARD_STATUS_IN_PROGRESS) && !hasFlag(BOARD_STATUS_X_WINS) && !hasFlag(BOARD_STATUS_O_WINS)) {
		if (FULL_BOARD_MASK == (board[X_SQUARE] | board[O_SQUARE])) {
			unsetFlag(BOARD_STATUS_IN_PROGRESS);
			setFlag(BOARD_STATUS_DRAW);
			score = DRAW_SCORE;
		}
	}
}

//********************************************************************************************************************
//********************************************************************************************************************

std::ostream& operator<<(std::ostream& stream, const Board& board) {
	for (int rowIdx = 0; rowIdx < BOARD_DIM; ++rowIdx) {
		for (int colIdx = 0; colIdx < BOARD_DIM; ++colIdx) {
			const int squareIdx = (rowIdx * BOARD_DIM) + colIdx;
			const short squareMask = 1 << squareIdx;

			if (board.getBoard(0) & squareMask) {
				stream << "X";
			}
			else if (board.getBoard(1) & squareMask) {
				stream << "O";
			}
			else {
				stream << "_";
			}
		}

		stream << std::endl;
	}

	return stream;
}
