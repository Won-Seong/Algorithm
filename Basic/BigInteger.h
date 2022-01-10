#pragma once
#include <iostream>
#include <string>

class BigInteger : std::exception {
public:
	BigInteger operator+(const BigInteger& integer) const;//�� BigInt�� ���Ѵ�.
	void operator+=(const BigInteger& integer);//BigInt�� �ڽſ��� ���Ѵ�.
	BigInteger operator/(const BigInteger& integer) const;//���� �ϼ� ��
	bool operator>(const unsigned int& integer) const;
	bool operator>(const BigInteger& integer) const;
	bool operator<(const unsigned int& integer) const;
	bool operator<(const BigInteger& integer) const;
	bool operator>=(const unsigned int& integer) const;
	bool operator>=(const BigInteger& integer) const;
	bool operator<=(const unsigned int& integer) const;
	bool operator<=(const BigInteger& integer) const;
public:
	long ToLong() const { return std::stol(number_); }//���� long long���� ��ȯ ������ ���
	size_t Length() const { return number_.size(); };
	void Append(std::string str) { number_ += str; }//�ڿ� String�� ���δ�.
	void Append(char ch) { number_ += ch; }//�ڿ� Char�� ���δ�.
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