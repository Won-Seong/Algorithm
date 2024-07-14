#pragma once
#include <iostream>
#include <vector>
#include <cmath>

class LCA {
	using Vector = std::vector< int >; 
	using Matrix = std::vector< Vector >;
	using PairVector = std::vector< std::pair<size_t , int> >; // Index and value
	using PairMatrix = std::vector < PairVector >;
public: // Main Class Functions
	void Insert(const size_t& left, const size_t& right, const int& value) {
		matrix_[left].push_back(std::make_pair(right, value)); matrix_[right].push_back(std::make_pair(left, value));
	} // Insert the element to the matrix_.
	size_t LeastCommonAncestor(size_t left, size_t right) const; // Search for the LCA of two nodes with left and right indexes.
	void SetDepth(); // You can set the depth_table_ and parent_matrix_ to search for the least common ancestor using LeastCommonAncestor() later.
public:
	LCA(const size_t& size) :size_(size) {
		matrix_.resize(size_);
	}
	const PairMatrix& get_matrix() const { return matrix_; }
	void PrintDepthTable() const;
	void PrintParentMatrix() const;
private:
	void SetDepthUtility(Vector& visit_table, int now, int depth); // This is a crucial utility function for SetDepth().
private:
	Vector depth_table_; // This table records the depth of each node.
	Matrix parent_matrix_; // This matrix records the parents of each node. 
	size_t size_; 
	PairMatrix matrix_; // This matrix is an adjacent list, which has information about which nodes are conneted to which nodes.
};