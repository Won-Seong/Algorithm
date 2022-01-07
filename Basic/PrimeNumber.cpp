#include "PrimeNumber.h"

bool PrimeNumber::check_prime(unsigned long K) const
{
	size_t low{ 0 }, high{ vector_.size() - 1 };
	if (vector_[low] > K || vector_[high] < K) throw std::invalid_argument("Is K lower than 2 or higher than Max number?");//현재 소수 배열 내에는 해당 수가 존재하지 않는다.
	size_t mid{ low + (high - low) / 2 };
	while (low <= high) {
		if (K == vector_[mid]) return true;
		else if (K < vector_[mid]) high = mid - 1;
		else low = mid + 1;
	}
	return false;
}

void PrimeNumber::SieveOfEratosthenes()
{
	if (number_ < 2) throw std::exception("The Number is lower than 2!");
	vector_.clear();
	vector_.push_back(2);//소수는 2부터 시작
	bool flag{ false };
	for (size_t i = 3; i < number_; i++) {
		flag = false;
		for (const auto& itr : vector_) {
			if (itr > std::sqrt(i)) break;
			else if ((i % itr) == 0) { flag = true; break; }
		}
		if (flag == false) vector_.push_back(i);
	}
}

PrimeNumber::FactoVector PrimeNumber::Factorization(unsigned long K) const
{
	if (K < 2) throw std::invalid_argument("K is lower than 2!");
	FactoVector vector;
	PrimeVector::const_iterator iter{ vector_.cbegin() };
	while (K > 1 && iter != vector_.cend()) {
			if ((K % iter.operator*()) == 0) {
				vector.push_back(std::make_pair(iter.operator*(), 0));
				while ((K % iter.operator*()) == 0)
					K /= iter.operator*(), vector.back().second++;
			}
			iter++;
	}
	if (K > 1 && iter == vector_.cend()) throw std::exception("The number is composed prime number higher than the Number!");
	return vector;
}

unsigned long PrimeNumber::EulerPiFunc(unsigned long K) const
{
	FactoVector vector{ std::move(Factorization(K)) };
	for (const auto& itr : vector)
		K = K - K / itr.first;
	return K;
}
