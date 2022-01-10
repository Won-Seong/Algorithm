#pragma once
#include <iostream>
#include <set>
#include <vector>

class KrusKal : public std::exception {
public:
	struct Edge;
	using Set = std::multiset<Edge>;
	using IndexVector = std::vector< size_t >;
	using Bucket = std::vector< std::set<size_t> >;
	using Vector = std::vector<size_t>;
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
	int MinimumSpanningTree_() {
		IndexVector vector(size_);
		Set temp_set{ set_ };
		Set result;
		for (size_t i = 0; i < size_; i++)
			vector[i] = i;

		while (!temp_set.empty() && result.size() < size_ - 1) {
			/*std::cout << temp_set.begin().operator*().from_ << ' ' << temp_set.begin().operator*().to_ << '\n';
			std::cout << vector[temp_set.begin().operator*().from_] << ' ' << vector[temp_set.begin().operator*().to_] << '\n';*/

			if (Find(vector, temp_set.begin().operator*().from_) != Find(vector, temp_set.begin().operator*().to_)) 	
			{
				result.insert(temp_set.begin().operator*());
				Union(vector,
					temp_set.begin().operator*().from_, 
					temp_set.begin().operator*().to_);
			}
			temp_set.erase(temp_set.begin());
		}

		int value{ 0 };

		for (const auto& itr : result) {
			//std::cout << itr.from_ + 1 << ' ' << itr.to_ + 1 << ' ' << itr.value_ << '\n';
			value += itr.value_;
		}
		return value;
	}
	void MinimumSpanningTree() const {
		Vector vector(size_);
		Set temp{ set_ };
		Bucket bucket(size_);
		Set result;
		size_t temp_index;
		for (size_t j = 0; j < size_; j++)
		{
			vector[j] = j;
		}
		for (size_t i = 0; i < size_; i++)
		{
			bucket[i].insert(i);
		}

		for (size_t i = 0; !temp.empty() && i < size_; i++)
		{
			//std::cout << temp.begin().operator*().from_ << ' ' << temp.begin().operator*().to_ << ' ' << temp.begin().operator*().value_ << "\n\n";

			while (!temp.empty() && vector[temp.begin().operator*().from_] == vector[temp.begin().operator*().to_])
				temp.erase(temp.begin());

			if (temp.empty()) break; ;

			//std::cout << temp.begin().operator*().from_ << ' ' << temp.begin().operator*().to_ << ' ' << temp.begin().operator*().value_ << "\n\n";

			if (bucket[vector[temp.begin().operator*().from_]].size() < bucket[vector[temp.begin().operator*().to_]].size()) {
				temp_index = vector[temp.begin().operator*().from_];
				for (auto& itr : bucket[vector[temp.begin().operator*().from_]]) {
					bucket[vector[temp.begin().operator*().to_]].insert(itr);
					vector[itr] = vector[temp.begin().operator*().to_];
				}
			}
			else {
				temp_index = vector[temp.begin().operator*().to_];
				for (auto& itr : bucket[vector[temp.begin().operator*().to_]]) {
					bucket[vector[temp.begin().operator*().from_]].insert(itr);
					vector[itr] = vector[temp.begin().operator*().from_];
				}
			}

			bucket[temp_index].clear();
			result.insert(temp.begin().operator*());
			temp.erase(temp.begin());
		}

		Set::iterator iter{ result.end() };
		iter--;
		result.erase(iter);

		unsigned int sum{ 0 };

		for (const auto& itr : result)
			sum += itr.value_;

		std::cout << sum;
	}
	void Insert(const size_t& from, const size_t& to, const int& value) {
		set_.insert(Edge(from - 1, to - 1, value));
	}
private://UnionFind
	size_t Union(IndexVector& vector, size_t left, size_t right) {
		vector[Find(vector, left)] = Find(vector, right);
		return vector[left];
	}
	size_t Find(IndexVector& vector,size_t index) {
		if (index == vector[index]) return index;
		else return vector[index] = Find(vector ,vector[index]);
	}
public:
	KrusKal(const size_t& size) :size_(size) {}
private:
	Set set_;
	size_t size_;
};
