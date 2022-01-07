#pragma once
#include "BigInteger.h"
#include <iostream>
#include <vector>

class Combination : std::exception {
private:
	using Vector = std::vector< BigInteger >;
	using Matrix = std::vector< Vector >;
public:
	void CreatePascalTable();//파스칼 테이블 제작
	void PrintPascalTable() const;//
	BigInteger N_Combination_M(const size_t& n,const size_t& m) const;//nCm
public://Const, Dest, getter and setter
	Combination(const size_t& size) :size_(size) {
		set_size(size_);
	};
	Combination() :size_(size_t()) {}
	void Clear() { pascal_table_.clear(); }
	void set_size(const size_t& size) { 
		size_ = size; Clear(); 
		pascal_table_.resize(size_ + 1);
		for (auto& itr : pascal_table_) itr.resize(size_ + 1, 1);
	}
	size_t get_size() const { return size_; }
	
private:
	BigInteger PascalUility(const size_t& n, const size_t& m);
private:
	Matrix pascal_table_;
	size_t size_;//nCm에서 n
};