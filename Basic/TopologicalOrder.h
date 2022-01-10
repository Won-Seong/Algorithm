#pragma once
#include <iostream>
#include <vector>
#include <queue>

class TopologicalOrder : public std::exception {
	using Vector = std::vector<int>;
	using IndexVector = std::vector< size_t >;
	using Matrix = std::vector< Vector >;
public:
	void Insert(const size_t& from, const size_t& to);
	void TopologicalPrint() const;
public:
	TopologicalOrder(const size_t& size) :size_(size) {
		matrix_.resize(size_);
		in_degree_vector_.resize(size_, 0);
	}
private:
	IndexVector TopologicalUtility(const size_t& index) const;
	IndexVector TopologicalUtility() const;
private:
	Matrix matrix_;//adj list
	Vector in_degree_vector_;
	size_t size_;
};