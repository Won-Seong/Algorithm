#pragma once
#include <iostream>
#include <string_view>

class BigInteger : std::exception {

public:


public:
	BigInteger() : number_( std::string() ) {};
	BigInteger(std::string_view number) : number_(number) {};
	BigInteger(std::string&& number) : number_(number) { number = std::string(); } ;
	void set_number(std::string_view number) { number_ = number; }
	std::string get_number() const { return number_; }
private:
	std::string number_;
};