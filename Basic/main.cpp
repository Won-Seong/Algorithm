#include "LCA.h"

int main() {
	std::cin.sync_with_stdio(false);
	std::cin.tie(NULL);
	size_t N, M;
	std::cin >> N;
	LCA lca(N);
	int alpha, beta;
	for (size_t i = 0; i < N - 1; i++)
	{
		std::cin >> alpha >> beta;
		lca.Insert(alpha - 1, beta - 1);
	}
	std::cin >> M;

	lca.SetDepth();

	for (size_t i = 0; i < M; i++)
	{
		std::cin >> alpha >> beta;
		std::cout << lca.LeastCommonAnc(alpha - 1, beta - 1) + 1<< '\n';
	}

}