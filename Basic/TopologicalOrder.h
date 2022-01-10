#pragma once
#include <iostream>
#include <vector>
#include <queue>

//유향일 경우
class TopologicalOrder : public std::exception {
	using Vector = std::vector<int>;
	using IndexVector = std::vector< size_t >;
	using Matrix = std::vector< Vector >;
public:
	void Insert(const size_t& from, const size_t& to);//간선 입력
	void TopologicalPrint() const;//Topological의 결과를 출력
	IndexVector TopologicalReturn() const;//Topological의 결과를 반환
public:
	TopologicalOrder(const size_t& size) :size_(size) {
		out_matrix_.resize(size_);
		in_matrix_.resize(size_);
		in_degree_vector_.resize(size_, 0);
	}//정점은 size_만큼
	Matrix get_out() const { return out_matrix_; }
	Matrix get_in() const { return in_matrix_; }
private:
	IndexVector TopologicalUtility(const size_t& index) const;//Index를 지정하였을 경우
	IndexVector TopologicalUtility() const;
private:
	Matrix out_matrix_;//간선이 나가는
	Matrix in_matrix_;//간선이 들어오는
	Vector in_degree_vector_;//i 정점에 들어오는 간선이 몇 개가 있는가?
	size_t size_;
};