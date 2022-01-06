#pragma once
#include <iostream>
#include <vector>

class FloydWarshall : public std::exception {
public:
	using Vector = std::vector< unsigned int >;
	using Matrix = std::vector< Vector >;
public://Constructor, Destructor
	FloydWarshall(const size_t& size) : size_(size) {
		matrix_.resize(size_);
		for (auto& itr : matrix_)
			itr.resize(size_, 1000000000);
	}
public:
	void Insert(const unsigned int& from, const unsigned int& to, const unsigned int& cost) {
		matrix_[from - 1][to - 1] = matrix_[from - 1][to - 1] == 0 ? cost : (matrix_[from - 1][to - 1] < cost ? matrix_[from - 1][to - 1] : cost);
	}
	void all_source_shortest_path() const {
		//Matrix table(size_);//Tabel to write shortest path
		//for (auto& itr : table)
		//	itr.resize(size_);

		Matrix table = matrix_;
		for (size_t j = 0; j < size_; j++)
			table[j][j] = 0;

		for (size_t j = 0; j < size_; j++) {

			for (size_t k = 0; k < size_; k++) {

				for (size_t l = 0; l < size_; l++) {

					table[k][l] = table[k][l] > table[k][j] + table[j][l] ? table[k][j] + table[j][l] : table[k][l];

				}
			}

		}

		for (const auto& itr : table) {
			for (const auto& itr_2 : itr) {
				if (itr_2 >= 10000000) std::cout << 0 << ' ';
				else std::cout << itr_2 << ' ';
			}
			std::cout << '\n';
		}

	}
	void Print() const {
		for (const auto& itr : matrix_) {
			for (const auto& itr_2 : itr)
				std::cout << itr_2 << ' ';
			std::cout << '\n';
		}
	}
private:
	size_t size_;
	Matrix matrix_;
};
