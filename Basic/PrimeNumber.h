#pragma once
#include <iostream>
#include <vector>
#include <cmath>

class PrimeNumber : std::exception {
	using PrimeVector = std::vector<unsigned long>;
public:
	bool check_prime() {
		size_t low{ 0 }, high{ vector_.size() };
		size_t mid{ (low + high) / 2 };
		while (low < high - 1) {
			if (number_ == vector_[mid]) return true;
			else if (number_ < vector_[mid]) high = mid - 1;
			else low = mid + 1;
		}
		return false;
	}//K�� �Ҽ����� Binary Search�� ����
	void SieveOfEratosthenes() {
		vector_.clear();
		vector_.push_back(2);//�Ҽ��� 2���� ����
		bool flag{ false };
		for (size_t i = 3; i < number_; i++) {
			flag = false;
			for (const auto& itr : vector_) {
				if (itr > std::sqrt(i)) break;
				else if ((i % itr) == 0) { flag = true; break; }
			}
			if (flag == false) vector_.push_back(i);
		}

	}//K���� ���� �Ҽ��� ��� ã�ƺ���
	void PrintPrimeVector() {
		for (const auto& itr : vector_)
			std::cout << itr << ' ';
		std::cout << std::endl;
	}
public://Const, Dest, getter and setter
	PrimeNumber() :number_(0) {};
	PrimeNumber(const unsigned int& number) :number_(number) {
		SieveOfEratosthenes();
	};
	void set_number(const unsigned int& number) { number_ = number; }
	unsigned int get_number() const { return number_; }
private:
	PrimeVector vector_;
	unsigned int number_;
};