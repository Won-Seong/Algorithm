#include <iostream>
#include <vector>
#include <map>
#include <set>

class Dijkstra : public std::exception {
public:
	using Vector = std::vector< unsigned int >;
	using Map = std::multimap< unsigned int, unsigned int >;
	using Matrix = std::vector< Map >;
public://Constructor, Destructor
	Dijkstra(const size_t& size) : size_(size) {
		matrix_.resize(size);
	};
	~Dijkstra() {};
public:
	Vector ShortestPath(const unsigned int& source) const {
		enum class STATUS {
			UNSEEN, FRINGE, TREE
		};

		Vector vector;
		std::vector<STATUS> status(size_, STATUS::UNSEEN);
		std::multimap<unsigned int, unsigned int> table;
		Vector memo(size_, 0);//Memo distances to each vertex
		status[source] = STATUS::TREE;

		unsigned int temp{ source };

		do
		{
			for (const auto& itr : matrix_[temp]) {
				//std::cout << itr.second << ' ' << itr.first << '\n';
				if (status[itr.second] == STATUS::UNSEEN) {
					status[itr.second] = STATUS::FRINGE;
					table.insert(std::make_pair(memo[temp] + itr.first, itr.second));
				}
				else if (status[itr.second] == STATUS::FRINGE) {
					table.insert(std::make_pair(memo[temp] + itr.first, itr.second));
				}
			}

			//std::cout << "good " << table.begin().operator*().second << ' ' << table.begin().operator*().first << '\n';

			////for (const auto& itr : status) {
			////	if (itr == STATUS::TREE)
			////		std::cout << 2 << ' ';
			////	else if(itr == STATUS::FRINGE)
			////		std::cout << 1 << ' ';
			////	else
			////		std::cout << 0 << ' ';
			////}
			////std::cout << std::endl;

			//std::cout << "good " << table.begin().operator*().second << ' ' << table.begin().operator*().first << '\n';

			/*for (const auto& itr : table)
				std::cout << itr.second << ' ' << itr.first << '\n';*/

			while (!table.empty() && status[table.begin().operator*().second] == STATUS::TREE)
				table.erase(table.begin());
			if (table.empty()) break;
			/*for (const auto& itr : table)
				std::cout << itr.second << ' ' << itr.first << '\n';*/


			memo[table.begin().operator*().second] = table.begin().operator*().first;
			status[table.begin().operator*().second] = STATUS::TREE;
			temp = table.begin().operator*().second;
		
		} while (!table.empty());
		
		for (unsigned int j = 0; j < size_; j++) {
			if (j == source) std::cout << 0 << '\n';
			else if(memo[j] == 0 ) std::cout << "INF" << '\n';
			else std::cout << memo[j] << '\n';
		}
		return memo;
	}
	void Insert(const size_t& from, const size_t& to, const unsigned int& value) {
		matrix_[from - 1].insert( std::make_pair(value, to - 1) );
	}
private:
	size_t size_;
	Matrix matrix_;
};
//
//int main() {
//	std::cin.sync_with_stdio(false);
//	unsigned int alpha, beta, gamma;
//	std::cin >> alpha>> beta >> gamma;
//
//	Dijkstra dijkstra(alpha);
//
//	unsigned int from, to, value;
//
//	for (unsigned int j = 0; j < beta; j++) {
//		std::cin >> from >> to >> value;
//		dijkstra.Insert(from, to, value);
//	}
//
//	dijkstra.ShortestPath(gamma - 1);
//}