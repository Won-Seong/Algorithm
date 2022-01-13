#pragma once
#include <iostream>
#include <vector>
#include <map>
#include <functional>
#include <algorithm>
#include <cmath>
#include <tuple>
#include <stack>
#include <set>
#include <queue>

class SSSP : public std::exception {
private:
	using Vector = std::vector< long >;
	using Tuple = std::tuple<long, size_t, size_t >;
	using PairVector = std::vector< std::pair< size_t , long> >;//<index, value>
	using Map = std::multimap< long, long >;//<value, to>
	using Set = std::multiset< std::tuple<long, size_t, size_t > >;
	using PairMatrix = std::vector< PairVector >;
	using Matrix = std::vector< Vector >;
	enum class STATUS {
		UNSEEN, FRINGE, TREE
	};
public:
	using ReturnPair = std::pair<PairVector, Vector>;
public:
	static void PrintReturnPair(const ReturnPair& pair);
	ReturnPair DijkstraWithList(const size_t& source) const;//Return shortest path and sum of weight of shortest path.
	ReturnPair DijkstraTo(const size_t& source);//Shortest path goal to source.
	ReturnPair DijkstraWithMat(const size_t& source) const;//Return shortest path and sum of weight of shortest path.
	std::vector<std::priority_queue<long, std::vector<long>, std::less<long>>> K_Dijkstra(const size_t& source, unsigned int K = 2);
	//Return K-th shortest path and sum of weight of shortest path. 
	Vector BellmanFord(const size_t& source = 0) const;//일반적인 Bellman ford 알고리즘
	Vector BellmanFordUpgrade(const size_t& source = 0) const;// Negative cycle이 Source와 연결되어 있지 않은 경우 무시하고 진행
	void Insert(const size_t& from, const size_t& to, const long& value) {
		adj_list_[from].push_back(std::make_pair(to, value));
		adj_matrix_[from][to] = value;
		edge_list_.push_back(std::make_tuple(from, to, value));
	}
public://Constructor, Destructor, setter and getter
	SSSP(const size_t& size) : size_(size) {
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
	std::vector< std::tuple<size_t, size_t, long> > edge_list_;
};