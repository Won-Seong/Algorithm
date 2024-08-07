#include "Combination.h"

void Combination::CreatePascalTable()
{
	for (size_t i = 2; i <= size_; i++)
	{
		pascal_table_[i][1] = i;
		pascal_table_[i][i - 1] = i;
	}
	for (size_t i = 2; i < size_ - 1; i++)
	{
		PascalUility(size_, i);
	}
}

void Combination::PrintPascalTable() const
{
	std::cout << "================Print pascal table================" << std::endl;
	for (size_t i = 0; i <= size_; i++)
	{
		for (size_t j = size_ - i; j > 0; j--)
			std::cout << ' ';
		for (size_t j = 0; j < i + 1; j++)
		{
			std::cout << pascal_table_[i][j] << ' ';
		}
		std::cout << '\n';
	}
	std::cout << "==================================================" << std::endl;
}

BigInteger Combination::N_Combination_M(const size_t& n, const size_t& m) const
{
	if (n < m) throw std::invalid_argument("M can't be bigger than N!");
	return pascal_table_[n][m];
}

BigInteger Combination::PascalUility(const size_t& n,const size_t& m)
{
	if (n == m || n == 0 || m == 0) return 1;
	else if (pascal_table_[n][m] > 1) return pascal_table_[n][m];
	else return pascal_table_[n][m] = PascalUility(n-1, m-1) + PascalUility(n - 1, m);
}

void CombinationSimple(const size_t& n, const size_t& m)
{
	int top{ 0 };
	std::vector<int> vector(n);
	CombinationSimpleUtility(n, m, vector, top, 1);
	return;
}

void CombinationSimpleUtility(const size_t& n, const size_t& m,std::vector<int>& vector , int& top, size_t start)
{
	if (top == m)
	{
		for (size_t i = 0; i < m; i++) std::cout << vector[i]<< ' ';
		std::cout << std::endl;
		return;
	}
	for (size_t i = start; i <= n; i++)
	{
		if (n - i + 1 < m - top) break;//����ġ��
		vector[top++] = i;
		CombinationSimpleUtility(n , m , vector, top, i + 1);
		top--;
	}
}
