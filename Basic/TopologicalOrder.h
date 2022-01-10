#pragma once
#include <iostream>
#include <vector>
#include <queue>

//������ ���
class TopologicalOrder : public std::exception {
	using Vector = std::vector<int>;
	using IndexVector = std::vector< size_t >;
	using Matrix = std::vector< Vector >;
public:
	void Insert(const size_t& from, const size_t& to);//���� �Է�
	void TopologicalPrint() const;//Topological�� ����� ���
	IndexVector TopologicalReturn() const;//Topological�� ����� ��ȯ
public:
	TopologicalOrder(const size_t& size) :size_(size) {
		out_matrix_.resize(size_);
		in_matrix_.resize(size_);
		in_degree_vector_.resize(size_, 0);
	}//������ size_��ŭ
	Matrix get_out() const { return out_matrix_; }
	Matrix get_in() const { return in_matrix_; }
private:
	IndexVector TopologicalUtility(const size_t& index) const;//Index�� �����Ͽ��� ���
	IndexVector TopologicalUtility() const;
private:
	Matrix out_matrix_;//������ ������
	Matrix in_matrix_;//������ ������
	Vector in_degree_vector_;//i ������ ������ ������ �� ���� �ִ°�?
	size_t size_;
};