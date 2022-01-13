#include "SSSP.h"

int main() {
	std::cin.sync_with_stdio(false);
	std::cin.tie(NULL);
	size_t N, M, X;
	std::cin >> N >> M >> X;

	SSSP sssp(N);

	size_t a, b;
	unsigned long c;

	for (size_t i = 0; i < M; i++)
	{
		std::cin >> a >> b >> c;
		sssp.Insert(a - 1, b - 1, c);

	}
	unsigned int count{ 1 };

	for (const auto& itr : sssp.K_Dijkstra(0, X)) {
		if (itr.size() < X) {
			std::cout << -1;
		}
		else {
			std::cout << itr.top();
		}
		std::cout << '\n';
	}
	
}