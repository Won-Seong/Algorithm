#pragma once
#include <iostream>
#include <string>

class BigInteger : std::exception {
public:
	BigInteger operator+(const BigInteger& integer) const;//두 BigInt를 더한다.
	void operator+=(const BigInteger& integer);//BigInt를 자신에게 더한다.
	BigInteger operator/(const BigInteger& integer) const;//아직 완성 전
	bool operator>(const unsigned int& integer) const;
	bool operator>(const BigInteger& integer) const;
	bool operator<(const unsigned int& integer) const;
	bool operator<(const BigInteger& integer) const;
	bool operator>=(const unsigned int& integer) const;
	bool operator>=(const BigInteger& integer) const;
	bool operator<=(const unsigned int& integer) const;
	bool operator<=(const BigInteger& integer) const;
public:
	long ToLong() const { return std::stol(number_); }//만약 long long으로 변환 가능할 경우
	size_t Length() const { return number_.size(); };
	void Append(std::string str) { number_ += str; }//뒤에 String을 붙인다.
	void Append(char ch) { number_ += ch; }//뒤에 Char를 붙인다.
public://Const, Dest, setter and getter
	BigInteger() : number_( std::string() ) {};
	BigInteger(std::string number) : number_(number) {};
	BigInteger(const unsigned int& integer) : number_(std::to_string(integer)) {};
	void set_number(std::string number) { number_ = number; }
	std::string get_number() const { return number_; }
private:
	std::string number_;
};

inline std::ostream& operator<<(std::ostream& os,const BigInteger& number) {
	os << number.get_number();
	return os;
}