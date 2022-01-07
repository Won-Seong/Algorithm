#pragma once
#include <iostream>
#include <vector>
#include <cmath>

class PrimeNumber : std::exception {
public:
	using PrimeVector = std::vector<unsigned long>;
	using FactoVector = std::vector < std::pair<unsigned long, int> >;
public:
	bool check_prime(unsigned long K) const;//K가 소수인지 Binary Search해 보자
	void SieveOfEratosthenes();//K보다 작은 소수를 모두 찾아보자
	void PrintPrimeVector() {
		if (vector_.empty()) std::cout << "No number in vector!";
		else
		for (const auto& itr : vector_)
			std::cout << itr << ' ';
		std::cout << std::endl;
	}
	FactoVector Factorization(unsigned long K) const;//K를 소인수 분해해 보자
	unsigned long EulerPiFunc(unsigned long K) const;//오일러 피 함수
public://Const, Dest, getter and setter
	PrimeNumber() :number_(0) {};
	PrimeNumber(const unsigned int& number) :number_(number) {
		SieveOfEratosthenes();
	};
	void Clear() { vector_.clear(); }
	void set_number(const unsigned int& number) { number_ = number; Clear(); vector_.resize(number_); }
	unsigned int get_number() const { return number_; }
private:
	PrimeVector vector_;
	unsigned int number_;//에라토스테네스의 체는 해당 숫자 이하를 탐색한다
};