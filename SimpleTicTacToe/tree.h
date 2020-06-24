#pragma once

#include <vector>
#include <map>
#include "node.h"

using BestMovesMap = std::map<std::pair<short, short>, std::pair<Coords, int>>;

/// Pair of the best move and its score for a given game state
struct BestMoveScore {
	Coords bestMove;
	short score;
};

class Tree {
public:
	Tree();

	Node& getNode(const int nodeIdx);
	const Node& getNode(const int nodeIdx) const;
	const int getNodesCount() const;

	/// Traverse all possible tic tac toe board states using DFS
	/// @param[in] depth the traversal depth
	/// @param[in] currentRootIdx the current root of the tree
	/// @param[in] allMoves the array tp be filled
	/// @param[in] allMovesCount the count to be set for all moves
	void dfsTraverse(
		const int depth,
		const int currentRootIdx,
		Coords(&allMoves)[ALL_SQUARES],
		int& allMovesCount
	);

	/// Backpropagate the result of the given Node to the root
	/// @param[in] nodeIdx the Node from which to start the backpropagation
	/// @param[in] turnsToEnd the how many turns are left until the end state
	/// @param[in] boardScore the board score to backpropagate
	void backtrack(const int nodeIdx, const int turnsToEnd, const short boardScore);

	/// Expand the given Node, creating children with all possible actions
	/// @param[in] nodeIdx the node to expand
	/// @param[in] allMoves the array tp be filled
	/// @param[in] allMovesCount the count to be set for all moves
	void expand(const int nodeIdx, Coords(&allMoves)[ALL_SQUARES], int& allMovesCount);

	/// Add the given node to the tree structure
	/// @param[in] node the node to add
	/// @return the index of the added node
	int addNode(const Node& node);

	/// Back propagate the score of the terminating board, maximizing for X and minimizing for O
	/// @param[in] parentBoard the board state of the parent, for which to decide the best move
	/// @param[in] currentNode the node holding the current move to consider
	/// @param[in] turnsToEnd the turns count for reaching the terminal state
	/// @param[in] boardScore the board score to backpropagate
	void backtrackScore(
		Board& parentBoard,
		const Node& currentNode,
		const int turnsToEnd,
		const short boardScore
	);

	/// Set the information for the best move of the given board
	/// @param[in] parentBoard the board state of the parent, for which to decide the best move
	/// @param[in] currentNode the node holding the current move to consider
	/// @param[in] turnsToEnd the turns count for reaching the terminal state
	void setBestMove(
		Board& parentBoard,
		const Node& currentNode,
		const int turnsToEnd
	);

	/// Gather the best moves for all game states
	void collectBestMoves();

	/// Output the best results to file
	void outputResults() const;

private:
	/// Reserve tree node and create root Node
	void init();

private:
	std::vector<Node> nodes; ///< All nodes in the tree
	BestMovesMap checkedBoards; ///< Check boards to prevent duplication
};
