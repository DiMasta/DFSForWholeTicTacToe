#pragma once

static constexpr int INVALID_IDX = -1;

static constexpr int ALL_SQUARES = 9;
static constexpr int BOARD_DIM = 3;
static constexpr int MAX_GAME_STATES = 362880; // 9 * 8 * 7 * 6 * 5 * 4 * 3 * 2
static constexpr int X_SQUARE = 0;
static constexpr int O_SQUARE = 1;
static constexpr int SQUARE_TYPES = 2; // 'X'; 'O'
static constexpr short EMPTY_TICTACTOE_BOARD = 0; // 9 empty squares
static constexpr short INVALID_SCORE = -200;
static constexpr short X_WINS_SCORE = 10;
static constexpr short O_WINS_SCORE = -10;
static constexpr short DRAW_SCORE = 0;

static constexpr short FULL_BOARD_MASK = 0b0000'000'111'111'111;
static constexpr int WIN_MASKS_COUNT = 8;
static constexpr short WIN_MASKS[WIN_MASKS_COUNT] = {
	0b0000'000'000'000'111, // Top row win
	0b0000'000'000'111'000, // Middle row win
	0b0000'000'111'000'000, // Bottom row win

	0b0000'000'001'001'001, // Left column win
	0b0000'000'010'010'010, // Middle column win
	0b0000'000'100'100'100, // Right column win

	0b0000'000'100'010'001, // Main diagonal win
	0b0000'000'001'010'100, // Second diagonal win
};

static constexpr unsigned short BOARD_STATUS_IN_PROGRESS	= 0b0000'0000'0000'0001;
static constexpr unsigned short BOARD_STATUS_DRAW			= 0b0000'0000'0000'0010;
static constexpr unsigned short BOARD_STATUS_X_WINS			= 0b0000'0000'0000'0100;
static constexpr unsigned short BOARD_STATUS_O_WINS			= 0b0000'0000'0000'1000;
static constexpr unsigned short X_TO_MOVE					= 0b0000'0000'0001'0000;
