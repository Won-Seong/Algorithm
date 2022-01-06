#pragma once
#include <iostream>
#include <vector>
#include <set>

class Prim : public std::exception {
public:
	struct Edge {
		size_t from_;
		size_t to_;
		int value_;
	public:
		Edge(const size_t& from, const size_t& to, const int& value) :from_(from), to_(to), value_(value) {};
		bool operator<(const Edge& edge) const {
			return value_ < edge.value_;
		}
		bool operator>(const Edge& edge) const {
			return value_ > edge.value_;
		}
	};
public:
	using Vector = std::vector<int>;
	using Set = std::multiset<Edge>;
	using Matrix = std::vector< Set >;
public:
	void Insert(const size_t& from, const size_t& to, const int& value) {
		matrix_[from - 1].insert(Edge(from - 1, to - 1, value));
		matrix_[to - 1].insert(Edge(to - 1, from - 1, value));
	}
	long long MinimumSpaaningTree() const {
		enum class STATUS {
			UNSEEN, FRINGE, TREE
		};
		std::vector<STATUS> status(size_, STATUS::UNSEEN);
		std::multiset<Edge> edges;

		size_t temp{ 0 };
		long long sum{ 0 };

		status[temp] = STATUS::TREE;

		do
		{
			for (const auto& itr : matrix_[temp])
				edges.insert(itr);

			while (!edges.empty() && status[edges.begin().operator*().from_] == STATUS::TREE &&
				status[edges.begin().operator*().to_] == STATUS::TREE) {
				edges.erase(edges.begin());
			}
			if (edges.empty()) break;

			status[edges.begin().operator*().to_] = STATUS::TREE;
			sum += edges.begin().operator*().value_;
			temp = edges.begin().operator*().to_;
			edges.erase(edges.begin());

		} while (true);

		return sum;
	}
	void Clear() {
		matrix_.clear();
		size_ = 0;
	}
	void Init(const size_t& size) {
		size_ = size;
	}
	void Print() const {
		for (const auto& itr : matrix_) {
			for (const auto& itr_2 : itr)
				std::cout << '(' << itr_2.to_ << ' ' << itr_2.value_ << ')' << ' ';
			std::cout << std::endl;
		}

	}
public:
	Prim(const size_t& size) :size_(size) {
		matrix_.resize(size_);
	}
	Prim() : size_(size_t()) {};
private:
	Matrix matrix_;
	size_t size_;
};