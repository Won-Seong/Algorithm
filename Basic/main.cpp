#include "Combination.h"
#include "BigInteger.h"

int main() {
	Combination comb;
	size_t N, M, K;
	std::cin >> N >> M >> K;
	comb.set_size(N + M);
	comb.CreatePascalTable();

	size_t L{ N };
	std::vector<char> result;
	while (N > 0 && M > 0 &&K > 0) {
		/*for (const auto& itr : result)
			std::cout << itr;
		std::cout << '\n';
		std::cout << N << ' ' << M << ' ' << K << '\n';*/

		if (K >= comb.N_Combination_M(N + M - 1, M)) {
			K -= comb.N_Combination_M(N + M - 1, M);
			result.push_back('z');
			M -= 1;
		}
		else {
			result.push_back('a');
			N -= 1;
		}
	}
	if (N == L && K > 1) {
		std::cout << -1;
		return 0;
	}

	while (N > 0)
		result.push_back('a'), N--;
	while (M > 0)
		result.push_back('z'), M--;
	for (const auto& itr : result)
		std::cout << itr;
}