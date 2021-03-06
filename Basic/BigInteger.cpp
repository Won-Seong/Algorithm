#include "BigInteger.h"

BigInteger BigInteger::operator+(const BigInteger& integer) const
{
	std::string result;
	std::string::const_reverse_iterator r_iter_one{ number_.crbegin() };
	std::string::const_reverse_iterator r_iter_two{ integer.number_.crbegin() };

	int one_num{ 0 }, two_num{ 0 };
	bool flag{ false };

	while (r_iter_one != number_.crend() && r_iter_two != integer.number_.crend()) {
		one_num = r_iter_one.operator*() - '0';
		two_num = r_iter_two.operator*() - '0';
		one_num = one_num + two_num + flag;
		if (one_num < 10)
			result = std::to_string(one_num) + result, flag = false;
		else {
			one_num -= 10;
			result = std::to_string(one_num) + result;
			flag = true;
		}
		r_iter_one++, r_iter_two++;
	}//각자 뒤에서부터 시작하여 더해 나가다가

	if (r_iter_one != number_.crend()) {
		while (flag && r_iter_one != number_.crend()) {
			one_num = r_iter_one.operator*() - '0';
			one_num += flag;
			if(one_num < 10) result = std::to_string(one_num) + result, flag = false;
			else {
				one_num -= 10;
				result = std::to_string(one_num) + result;
				flag = true;
			}
			r_iter_one++;
		}
		while (r_iter_one != number_.crend())
			result = r_iter_one.operator*() + result, r_iter_one++;
	}
	else if (r_iter_two != integer.number_.crend()) {
		while (flag && r_iter_two != integer.number_.crend()) {
			one_num = r_iter_two.operator*() - '0';
			one_num += flag;
			if (one_num < 10) result = std::to_string(one_num) + result, flag = false;
			else {
				one_num -= 10;
				result = std::to_string(one_num) + result;
				flag = true;
			}
			r_iter_two++;
		}
		while (r_iter_two != integer.number_.crend())
			result = r_iter_two.operator*() + result, r_iter_two++;
	}//더 긴 쪽을 전의 결과에다 붙인다. 이 때, 올림이 있을 수 있으니 이를 검사.

	if (flag) result = "1" + result;//결국 맨 처음 자릿수까지 올림이 발생했을 경우
	return BigInteger(result);
}

void BigInteger::operator+=(const BigInteger& integer)
{
	*this = *this + integer;
}

BigInteger BigInteger::operator/(const BigInteger& integer) const
{
	std::string result{ "" };
	BigInteger str{ "" };
	long temp_num{ 0 };

	for (const auto& itr : number_) {

		str.Append(itr);
		//if(str >= integer)

	}
	return str;
}

bool BigInteger::operator>(const unsigned int& integer) const
{
	BigInteger big_int{ integer };
	return operator>(big_int);
}

bool BigInteger::operator>(const BigInteger& integer) const
{
	if (Length() != integer.Length())
		return Length() > integer.Length();
	else {
		for (size_t i = 0; i < Length(); i++)
		{
			if (number_[i] != integer.number_[i]) return number_[i] > integer.number_[i];
		}
	}
	return false;
}

bool BigInteger::operator>=(const unsigned int& integer) const
{
	BigInteger big_int{ integer };
	return operator>=(big_int);
}

bool BigInteger::operator>=(const BigInteger& integer) const
{
	if (Length() != integer.Length())
		return Length() > integer.Length();
	else {
		for (size_t i = 0; i < Length(); i++)
		{
			if (number_[i] != integer.number_[i]) return number_[i] > integer.number_[i];
		}
	}
	return true;
}

bool BigInteger::operator<(const unsigned int& integer) const
{
	BigInteger big_int{ integer };
	return operator<(big_int);
}

bool BigInteger::operator<(const BigInteger& integer) const
{
	if (Length() != integer.Length())
		return Length() < integer.Length();
	else {
		for (size_t i = 0; i < Length(); i++)
		{
			if (number_[i] != integer.number_[i]) return number_[i] < integer.number_[i];
		}
	}
	return false;
}

bool BigInteger::operator<=(const unsigned int& integer) const
{
	BigInteger big_int{ integer };
	return operator<=(big_int);
}

bool BigInteger::operator<=(const BigInteger& integer) const
{
	if (Length() != integer.Length())
		return Length() < integer.Length();
	else {
		for (size_t i = 0; i < Length(); i++)
		{
			if (number_[i] != integer.number_[i]) return number_[i] < integer.number_[i];
		}
	}
	return true;
}