#include "LCA.h"

size_t LCA::LeastCommonAncestor(size_t left, size_t right) const
{
	// First, we need to match the depth of the two nodes.
	while (depth_table_[left] != depth_table_[right]) { // The two nodes have the same depth? If not-
		if (depth_table_[left] > depth_table_[right]) // If the left node is deeper than the right,
			left = parent_matrix_[left][static_cast<size_t>(std::floor(std::log2(depth_table_[left] - depth_table_[right])))]; // The left goes upstream.
		else 
			right = parent_matrix_[right][static_cast<size_t>(std::floor(std::log2(depth_table_[right] - depth_table_[left])))];
	}

	if (left == right) return left; // The left and right nodes are the same? Then, it's the LCA.

	// Second, we need to search for the LCA by moving the two nodes by 2^i.
	for (int i = static_cast<size_t>(std::floor(std::log2(depth_table_[left]))); i >= 0; i--){
		if (parent_matrix_[left][i] != parent_matrix_[right][i]) { // If the 2^i parents are not the same,
			//The left and right go upstream to be the 2^i parents.
			left = parent_matrix_[left][i]; 
			right = parent_matrix_[right][i];
		}
	}

	return parent_matrix_[left][0];
}

void LCA::SetDepth() 
{
	Vector visit_table(size_, 0);
	depth_table_.clear(); parent_matrix_.clear();
	depth_table_.resize(size_);
	parent_matrix_.resize(size_);
	for (auto& itr : parent_matrix_)
		itr.resize(static_cast<size_t>(std::log2(size_)) + 1, size_ + 2 );
	visit_table[0] = 1;
	parent_matrix_[0][0] = 0;
	SetDepthUtility(visit_table, 0, 0);
}

void LCA::SetDepthUtility(Vector& visit_table ,int now, int depth) 
{
	depth_table_[now] = depth;
	size_t temp_parent{ size_t() };

	// Recording parents
	for (size_t i = 0; i < parent_matrix_[now].size() - 1; i++){
		temp_parent = parent_matrix_[now][i]; // My 2^i_th parent
		if (parent_matrix_[temp_parent][i] == size_ + 2) break; // No more parents?
		else parent_matrix_[now][i + 1] = parent_matrix_[temp_parent][i]; // My 2^(i+1)_th parent is the parent of my 2^i_th parent.
	}

	// Recall this function for my children.
	for (const auto& itr : matrix_[now]) {
		if (visit_table[itr.first] == 0) { // Is it my child?
			visit_table[itr.first] = 1; 
			parent_matrix_[itr.first][0] = now; // I'm the 2^0_th parent of my child.
			SetDepthUtility(visit_table, itr.first, depth + 1); // Recurrence.
		}
	}
}

void LCA::PrintDepthTable() const
{
	if (depth_table_.empty()) std::cout << "Call this after SetDepth!" << std::endl;
	else
		for (const auto& itr : depth_table_) std::cout << itr << ' ';
	std::cout << std::endl;
}

void LCA::PrintParentMatrix() const
{
	if (depth_table_.empty()) std::cout << "Call this after SetDepth!" << std::endl;
	else {
		for (const auto& itr : parent_matrix_)
			for (const auto& itr_2 : itr)
				std::cout << itr_2 << ' ';
		std::cout << std::endl;
	}
}
