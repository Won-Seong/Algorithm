#pragma once
#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <cmath>
#include <tuple>
#include <stack>
#include <set>

class SSSP : public std::exception {
private:
	using Vector = std::vector< int >;
	using PairVector = std::vector< std::pair< size_t , int> >;//<index, value>
	using Map = std::multimap< int, int >;//<value, to>
	using Set = std::multiset< std::tuple<int, size_t, size_t > >;
	using PairMatrix = std::vector< PairVector >;
	using Matrix = std::vector< Vector >;
	using ReturnPair = std::pair<PairVector, Vector>;
	enum class STATUS {
		UNSEEN, FRINGE, TREE
	};
public:
	void PrintReturnPair(const ReturnPair& pair) const;
	ReturnPair DijkstraWithList(const size_t& source, const size_t& to) const;//Return shortest path and sum of weight of shortest path.
	ReturnPair DijkstraWithMat(const size_t& source, const size_t& to) const;//Return shortest path and sum of weight of shortest path.
	std::vector< PairVector > DijkstraAllPath(const size_t& source, const size_t& to) const;//Return all shortest path
	ReturnPair K_Dijkstra_NoReplace(const size_t& source, const size_t& to, unsigned int K = 2) ;
	//Return K-th shortest path and sum of weight of shortest path. The K-th shortest path doesn't share edges with 1 ... K - 1 shortest path.
	//https://www.acmicpc.net/problem/5719
	Vector BellmanFord(const size_t& source = 0) const;//일반적인 Bellman ford 알고리즘
	Vector BellmanFordUpgrade(const size_t& source = 0) const;// Negative cycle이 Source와 연결되어 있지 않은 경우 무시하고 진행
	void Insert(const size_t& from, const size_t& to, const int& value) {
		adj_list_[from].push_back(std::make_pair(to, value));
		adj_matrix_[from][to] = value;
		edge_list_.push_back(std::make_tuple(from, to, value));
	}
public://Constructor, Destructor, setter and getter
	SSSP(const int& size) : size_(size) {
		adj_list_.resize(size_);
		adj_matrix_.resize(size_);
		for (auto& itr : adj_matrix_)
			itr.resize(size_);
	};
	~SSSP() {};
	size_t get_size() const { return size_; }
private:
	size_t size_;
	PairMatrix adj_list_;
	Matrix adj_matrix_;
	std::vector< std::tuple<size_t, size_t, int> > edge_list_;
};