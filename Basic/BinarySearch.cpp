#include <iostream>
#include <vector>

template<typename T>
size_t binary_search(const std::vector<T>& vec, const T& elem) {

	size_t lo{ 0 };
	size_t hi{ vec.size() };
	size_t m{ (hi + lo) / 2 };

	while (hi - lo > 1) {

		m = (hi + lo) / 2;
		if (vec[m] == elem) {
			lo = m;
			break;
		}
		else if (vec[m] < elem) lo = m;
		else hi = m;

	}

	return lo;

} // This function returns the index of the exact element, or the lower bound.

template<typename T>
size_t binary_search_upper_bound(const std::vector<T>& vec, const T& elem) {

	size_t lo{ 0 };
	size_t hi{ vec.size() };
	size_t m{ (hi + lo) / 2 };

	while (hi - lo > 1) {

		m = (hi + lo) / 2;
		if (vec[m] == elem) {
			lo = m;
			break;
		}
		if (vec[m] <= elem) lo = m + 1;
		else hi = m;

	}

	return lo;

} // This function returns the index of the exact element, or the upper bound.

/*
int main() {

	std::vector<int> vec;

	vec.push_back(1);
	vec.push_back(5);
	vec.push_back(7);
	vec.push_back(9);
	vec.push_back(11);

	std::cout << binary_search(vec, 0) << std::endl;
	std::cout << binary_search(vec, 1) << std::endl;
	std::cout << binary_search(vec, 5) << std::endl;
	std::cout << binary_search(vec, 6) << std::endl;
	std::cout << binary_search(vec, 11) << std::endl;
	std::cout << binary_search(vec, 12) << std::endl;

	std::cout << std::endl;

	std::cout << binary_search_upper_bound(vec, 0) << std::endl;
	std::cout << binary_search_upper_bound(vec, 1) << std::endl;
	std::cout << binary_search_upper_bound(vec, 5) << std::endl;
	std::cout << binary_search_upper_bound(vec, 6) << std::endl;
	std::cout << binary_search_upper_bound(vec, 11) << std::endl;
	std::cout << binary_search_upper_bound(vec, 12) << std::endl;

}
*/