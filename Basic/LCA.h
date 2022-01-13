#pragma once
#include <iostream>
#include <vector>
#include <cmath>

class LCA {
	using Vector = std::vector< int >;
	using Matrix = std::vector< Vector >;
	using PairVector = std::vector< std::pair<size_t , int> >;//index, value
	using PairMatrix = std::vector < PairVector >;
public:
	void Insert(const int& left, const int& right, const int& value) {
		matrix_[left].push_back(std::make_pair(right, value)); matrix_[right].push_back(std::make_pair(left, value));
	}
	int LeastCommonAnc(int left, int right) const;
	void SetDepth() ;
	void PrintDepthTable() const;
	void PrintDepthMatrix() const;
public:
	LCA(const size_t& size) :size_(size) {
		matrix_.resize(size_);
	}
	const PairMatrix& get_matrix() const { return matrix_; }
private:
	void SimpleDFS(Vector& visit_table, int now, int depth);
private:
	Vector depth_table;
	Matrix depth_matrix;
	size_t size_;
	PairMatrix matrix_;//adj list
};