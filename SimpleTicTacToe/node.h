#pragma once

#include "board.h"
#include "coords.h"

class Node {
public:
	Node();
	Node(
		Board board,
		Coords move,
		Coords bestMove,
		int parent,
		int firstChild,
		int childrenCount
	);

	void setBoard(const Board& board);
	void setBestMove(const Coords bestMove);

	Board& getBoard();
	const Board& getBoard() const;
	Coords getMove() const;
	Coords getBestMove() const;
	int getParent() const;
	int getFirstChild() const;
	int getChildrenCount() const;

	/// Add new child for this node
	/// @param[in] childIdxNode the index of the child node
	void addChild(const int childIdxNode);

private:
	Board board; ///< The state of Node
	Coords move; ///< The move, which leads to this Node
	Coords bestMove; ///< The chosen best move for the Node
	int parent; ///< The parent index for the node
	int firstChild; ///< The first child for the Node
	int childrenCount; ///< Count of the children, they have ordered indecies
};