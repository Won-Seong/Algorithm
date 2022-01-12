#pragma once
#include <iostream>
#include <vector>
#include <cmath>

class LCA {
	using Vector = std::vector<int>;
	using Matrix = std::vector< Vector >;
public:
	void Insert(const int& left, const int& right) {
		matrix_[left].push_back(right); matrix_[right].push_back(left);
	}
	int LeastCommonAnc(int left, int right) const;
	void SetDepth() ;
	void PrintDepthTable() const;
	void PrintDepthMatrix() const;
public:
	LCA(const size_t& size) :size_(size) {
		matrix_.resize(size_);
	}
private:
	void SimpleDFS(Vector& visit_table, int now, int depth);
private:
	Vector depth_table;
	Matrix depth_matrix;
	size_t size_;
	Matrix matrix_;//adj list
};