#pragma once

#include "constants.h"
#include <fstream>

/// Coordinates for a square of the board
struct Coords {
	Coords() :
		rowIdx{ INVALID_IDX },
		colIdx{ INVALID_IDX }
	{}

	Coords(const int rowIdx, const int colIdx) :
		rowIdx{ rowIdx },
		colIdx{ colIdx }
	{}

	bool isValid() const {
		return INVALID_IDX != rowIdx && INVALID_IDX != colIdx;
	}

	friend std::ostream& operator<<(std::ostream& stream, const Coords& coords) {
		stream << "[" << coords.rowIdx << ", " << coords.colIdx << "]";
		return stream;
	}

	int rowIdx; ///< The row index of the square
	int colIdx; ///< The col index of the square
};
