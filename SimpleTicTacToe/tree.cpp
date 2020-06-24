#include "tree.h"
#include <fstream>

Tree::Tree() {
	init();
}

//********************************************************************************************************************
//********************************************************************************************************************

Node& Tree::getNode(const int nodeIdx) {
	return nodes[nodeIdx];
}

//********************************************************************************************************************
//********************************************************************************************************************

const Node& Tree::getNode(const int nodeIdx) const {
	return nodes[nodeIdx];
}

//********************************************************************************************************************
//********************************************************************************************************************

const int Tree::getNodesCount() const {
	return static_cast<int>(nodes.size());
}

//********************************************************************************************************************
//********************************************************************************************************************

void Tree::dfsTraverse(const int depth, const int currentRootIdx, Coords(&allMoves)[ALL_SQUARES], int& allMovesCount) {
	Node& currentRoot = getNode(currentRootIdx);
	Board& currentBoard = currentRoot.getBoard();
	if (!currentBoard.hasFlag(BOARD_STATUS_IN_PROGRESS)) {
		return;
	}

	expand(currentRootIdx, allMoves, allMovesCount);

	const int rootFirstChildIdx = currentRoot.getFirstChild();
	for (int childIdx = 0; childIdx < currentRoot.getChildrenCount(); ++childIdx) {
		dfsTraverse(depth + 1, rootFirstChildIdx + childIdx, allMoves, allMovesCount);
		const Node& childNode = getNode(rootFirstChildIdx + childIdx);

		const bool invalidBestMove = !currentRoot.getBestMove().isValid();
		bool betterMaxMove = false;
		bool betterMinMove = false;

		if (!invalidBestMove) {
			betterMaxMove = 0 == (depth % 2) && (childNode.getBoard().getScore() > currentBoard.getScore());
			betterMinMove = 1 == (depth % 2) && (childNode.getBoard().getScore() < currentBoard.getScore());
		}

		if (invalidBestMove || betterMaxMove || betterMinMove) {
			currentRoot.setBestMove(childNode.getMove());
			currentBoard.setScore(childNode.getBoard().getScore());
		}
	}
}

//********************************************************************************************************************
//********************************************************************************************************************

void Tree::backtrack(const int nodeIdx, const int turnsToEnd, const short boardScore) {
	const Node& currentNode = getNode(nodeIdx);
	const int parentIdx = currentNode.getParent();

	if (INVALID_IDX == parentIdx) {
		return;
	}

	Node& parentNode = getNode(parentIdx);
	Board& parentBoard = parentNode.getBoard();

	backtrackScore(parentBoard, currentNode, turnsToEnd, boardScore);

	backtrack(parentIdx, turnsToEnd + 1, parentBoard.getScore());
}

//********************************************************************************************************************
//********************************************************************************************************************

void Tree::expand(const int nodeIdx, Coords(&allMoves)[ALL_SQUARES], int& allMovesCount) {
	Node& node = getNode(nodeIdx);
	Board& board = node.getBoard();

	board.getAllPossibleMoves(allMoves, allMovesCount);

	for (int moveIdx = 0; moveIdx < allMovesCount; ++moveIdx) {
		Board childBoard{ board };
		childBoard.playMove(allMoves[moveIdx]);

		Coords bestMove;
		if (!childBoard.hasFlag(BOARD_STATUS_IN_PROGRESS)) {
			bestMove = allMoves[moveIdx];
		}

		Node childNode{ childBoard, allMoves[moveIdx], bestMove, nodeIdx, INVALID_IDX, 0 };
		const int childIdx = addNode(childNode);
		node.addChild(childIdx);
	}
}

//********************************************************************************************************************
//********************************************************************************************************************

int Tree::addNode(const Node& node) {
	const int newNodeIdx = getNodesCount();
	nodes.push_back(node);

	return newNodeIdx;
}

//********************************************************************************************************************
//********************************************************************************************************************

void Tree::init() {
	nodes.reserve(MAX_GAME_STATES * 2);

	Node rootNode;

	//Board initilaBoard{ 0b0000000'000'101'110, 0b0000000'011'010'001 };
	//Board initilaBoard{ 0b0000000'000'101'100, 0b0000000'001'010'001 };
	//rootNode.setBoard(initilaBoard);

	nodes.push_back(rootNode);
}

//********************************************************************************************************************
//********************************************************************************************************************

void Tree::backtrackScore(
	Board& parentBoard,
	const Node& currentNode,
	const int turnsToEnd,
	const short boardScore
) {
	if (INVALID_SCORE == parentBoard.getScore()) {
		parentBoard.setScore(boardScore);
		setBestMove(parentBoard, currentNode, turnsToEnd);
	}
	else if (parentBoard.hasFlag(X_TO_MOVE)) {
		// Maximize for X
		if (parentBoard.getScore() <= boardScore) {
			parentBoard.setScore(boardScore);
			setBestMove(parentBoard, currentNode, turnsToEnd);
		}
	}
	else if (!parentBoard.hasFlag(X_TO_MOVE)) {
		// Minimize for O
		if (parentBoard.getScore() >= boardScore) {
			parentBoard.setScore(boardScore);
			setBestMove(parentBoard, currentNode, turnsToEnd);
		}
	}
}

//********************************************************************************************************************
//********************************************************************************************************************

void Tree::setBestMove(Board& parentBoard, const Node& currentNode, const int turnsToEnd) {
	const std::pair<short, short> parentBoardsPair{ parentBoard.getBoard(0), parentBoard.getBoard(1) };

	//if (checkedBoards.end() == checkedBoards.find(parentBoardsPair)) {
	//	checkedBoards[parentBoardsPair] = { currentNode.getMove(), turnsToEnd };
	//}
	//else {
	//	if (checkedBoards[parentBoardsPair].second >= turnsToEnd) {
	//		checkedBoards[parentBoardsPair] = { currentNode.getMove(), turnsToEnd };
	//	}
	//}

	checkedBoards[parentBoardsPair] = { currentNode.getMove(), turnsToEnd };
}

//********************************************************************************************************************
//********************************************************************************************************************

void Tree::collectBestMoves() {
	for (size_t nodeIdx = 0; nodeIdx < nodes.size(); ++nodeIdx) {
		const Node& node = nodes[nodeIdx];
		const Board& board = node.getBoard();

		if (!board.hasFlag(BOARD_STATUS_IN_PROGRESS)) {
			continue;
		}

		const std::pair<short, short> boardsPair{ board.getBoard(0), board.getBoard(1) };
		checkedBoards[boardsPair] = { node.getBestMove(), 0 };
	}
}

//********************************************************************************************************************
//********************************************************************************************************************

void Tree::outputResults() const {
	std::ofstream outputFile;
	outputFile.open("best_moves.txt");

	outputFile << "static const std::map<std::pair<short, short>, Coords> BEST_MOVES = {" << std::endl;

	for (BestMovesMap::const_iterator it = checkedBoards.begin(); it != checkedBoards.end(); ++it) {
		outputFile << "\t{ { ";
		outputFile << it->first.first << ", " << it->first.second;
		outputFile << " }, { ";
		outputFile << it->second.first.rowIdx << ", " << it->second.first.colIdx;
		outputFile << " } }," << std::endl;
	}

	outputFile << "};" << std::endl;

	outputFile.close();
}
