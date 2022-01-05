#include <iostream>
#include <set>
#include <vector>

class KrusKal : public std::exception {
public:
	struct Edge;
	using Set = std::multiset<Edge>;
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

			bucket[ temp_index ].clear();
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
public:
	KrusKal(const size_t& size):size_(size){}
private:
	Set set_;
	size_t size_;
};

int main() {
	std::cin.tie(NULL);
	std::cin.sync_with_stdio(false);
	size_t size, count;
	std::cin >> size >> count;
	KrusKal kruskal(size);

	size_t alpha, beta;
	int gamma;
	for (size_t i = 0; i < count; i++)
	{
		std::cin >> alpha >> beta >> gamma;
		kruskal.Insert(alpha, beta, gamma);
	}
		
	kruskal.MinimumSpanningTree();
}