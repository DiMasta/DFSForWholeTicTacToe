#pragma once

#include <vector>
#include <map>
#include "node.h"

using BestMovesMap = std::map<std::pair<short, short>, char>;

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

	/// Expand the given Node, creating children with all possible actions
	/// @param[in] nodeIdx the node to expand
	/// @param[in] allMoves the array tp be filled
	/// @param[in] allMovesCount the count to be set for all moves
	void expand(const int nodeIdx, Coords(&allMoves)[ALL_SQUARES], int& allMovesCount);

	/// Add the given node to the tree structure
	/// @param[in] node the node to add
	/// @return the index of the added node
	int addNode(const Node& node);

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
