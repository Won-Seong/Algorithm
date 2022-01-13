#include "LCA.h"

int LCA::LeastCommonAnc(int left, int right) const
{
	while (depth_table[left] != depth_table[right]) {
		if (depth_table[left] > depth_table[right])
			left = depth_matrix[left][static_cast<int>(std::floor(std::log2(depth_table[left] - depth_table[right])))];
		else
			right = depth_matrix[right][static_cast<int>(std::floor(std::log2(depth_table[right] - depth_table[left])))];
	}

	if (left == right) return left;

	for (int i = static_cast<int>(std::floor(std::log2(depth_table[left]))); i >= 0; i--)
	{
		if (depth_matrix[left][i] != depth_matrix[right][i]) {
			left = depth_matrix[left][i];
			right = depth_matrix[right][i];
		}
	}

	return depth_matrix[left][0];
}

void LCA::SetDepth() 
{
	Vector visit_table(size_, 0);
	depth_table.clear(); depth_matrix.clear();
	depth_table.resize(size_);
	depth_matrix.resize(size_);
	for (auto& itr : depth_matrix)
		itr.resize(static_cast<int>(std::log2(size_)) + 1, -1);
	visit_table[0] = 1;
	depth_matrix[0][0] = 0;
	SimpleDFS(visit_table, 0, 0);
	depth_matrix[0][0] = -1;
}

void LCA::SimpleDFS(Vector& visit_table ,int now, int depth) 
{
	depth_table[now] = depth;
	int temp{ 0 };
	for (size_t i = 0; i < depth_matrix[now].size() - 1; i++)
	{
		temp = depth_matrix[now][i];
		if (depth_matrix[temp][i] == -1) break;
		else depth_matrix[now][i + 1] = depth_matrix[temp][i];
	}
	for (const auto& itr : matrix_[now]) {
		if (visit_table[itr.first] == 0) {
			visit_table[itr.first] = 1;
			depth_matrix[itr.first][0] = now;
			SimpleDFS(visit_table, itr.first, depth + 1);
		}
	}
}

void LCA::PrintDepthTable() const
{
	if (depth_table.empty()) std::cout << "Call this after SetDepth!" << std::endl;
	else
		for (const auto& itr : depth_table) std::cout << itr << ' ';
	std::cout << std::endl;
}

void LCA::PrintDepthMatrix() const
{
	if (depth_table.empty()) std::cout << "Call this after SetDepth!" << std::endl;
	else {
		for (const auto& itr : depth_matrix)
			for (const auto& itr_2 : itr)
				std::cout << itr_2 << ' ';
		std::cout << std::endl;
	}
}
