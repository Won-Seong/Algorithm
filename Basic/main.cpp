#include "TopologicalOrder.h"

int main() {
	size_t N;
	std::cin >> N;
	std::vector<int> time;
	TopologicalOrder topo(N);
	int value{ 0 };
	for (size_t i = 0; i < N; i++)
	{
		std::cin >> value;
		time.push_back(value);
		while (value != -1) {
			std::cin >> value;
			if (value == -1) break;
			topo.Insert(value - 1, i);
		}
	}

	std::vector<size_t> topological{ topo.TopologicalReturn() };
	std::vector< std::vector<int>> temp{ topo.get_in() };

	/*for (const auto& itr : temp) {
		for (const auto& itr_2 : itr)
			std::cout << itr_2 << ' ';
		std::cout << std::endl;
	}*/
	int max{ 0 };
	for (size_t i = 0; i < topological.size(); i++)
	{
		max = 0;
		if (!temp[topological[i]].empty()) {
			for (const auto& itr : temp[topological[i]]) {
				max = max > time[itr] ? max : time[itr];
			}
		}
		time[topological[i]] += max;
	}

	for (const auto& itr : time)
		std::cout << itr << '\n';

}