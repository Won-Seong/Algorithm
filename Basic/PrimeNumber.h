#pragma once
#include <iostream>
#include <vector>
#include <cmath>

class PrimeNumber : std::exception {
public:
	using PrimeVector = std::vector<unsigned long>;
	using FactoVector = std::vector < std::pair<unsigned long, int> >;
public:
	bool check_prime(unsigned long K) const;//K�� �Ҽ����� Binary Search�� ����
	void SieveOfEratosthenes();//K���� ���� �Ҽ��� ��� ã�ƺ���
	void PrintPrimeVector() {
		if (vector_.empty()) std::cout << "No number in vector!";
		else
		for (const auto& itr : vector_)
			std::cout << itr << ' ';
		std::cout << std::endl;
	}
	FactoVector Factorization(unsigned long K) const;//K�� ���μ� ������ ����
	unsigned long EulerPiFunc(unsigned long K) const;//���Ϸ� �� �Լ�
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
	unsigned int number_;//�����佺�׳׽��� ü�� �ش� ���� ���ϸ� Ž���Ѵ�
};