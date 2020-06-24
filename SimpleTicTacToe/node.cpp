#include "node.h"

Node::Node() :
	board{},
	move{},
	bestMove{},
	parent{ INVALID_IDX },
	firstChild{ INVALID_IDX },
	childrenCount{ 0 }
{

}

//********************************************************************************************************************
//********************************************************************************************************************

Node::Node(
	Board board,
	Coords move,
	Coords bestMove,
	int parent,
	int firstChild,
	int childrenCount
) :
	board{ board },
	move{ move },
	bestMove{ bestMove },
	parent{ parent },
	firstChild{ firstChild },
	childrenCount{ childrenCount }
{
}

//********************************************************************************************************************
//********************************************************************************************************************

void Node::setBoard(const Board& board) {
	this->board = board;
}

//********************************************************************************************************************
//********************************************************************************************************************

void Node::setBestMove(const Coords bestMove) {
	this->bestMove = bestMove;
}

//********************************************************************************************************************
//********************************************************************************************************************

Board& Node::getBoard() {
	return board;
}

//********************************************************************************************************************
//********************************************************************************************************************

const Board& Node::getBoard() const {
	return board;
}

//********************************************************************************************************************
//********************************************************************************************************************

Coords Node::getMove() const {
	return move;
}

//********************************************************************************************************************
//********************************************************************************************************************

Coords Node::getBestMove() const {
	return bestMove;
}

//********************************************************************************************************************
//********************************************************************************************************************

int Node::getParent() const {
	return parent;
}

int Node::getFirstChild() const {
	return firstChild;
}

//********************************************************************************************************************
//********************************************************************************************************************

int Node::getChildrenCount() const {
	return childrenCount;
}

//********************************************************************************************************************
//********************************************************************************************************************

void Node::addChild(const int childIdxNode) {
	if (0 == childrenCount) {
		firstChild = childIdxNode;
	}

	++childrenCount;
}