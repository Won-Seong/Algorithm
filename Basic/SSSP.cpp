#include "SSSP.h"

void SSSP::PrintReturnPair(const ReturnPair& pair) const
{
	if (pair.first.empty()) {
		std::cout << "Empty!" << std::endl;
		return;
	}

	std::cout << "Path : ";
	for (const auto& itr : pair.first)
		std::cout << itr.first << ' ';
	std::cout << pair.first.back().second << '\n';
}

SSSP::ReturnPair SSSP::DijkstraWithList(const size_t& source, const size_t& to) const
{
	PairVector pair_vector;//To store detail of path.
	std::vector<STATUS> status(size_, STATUS::UNSEEN);
	Set set;
	Vector memo(size_, 0);//Memo distances to each vertex
	size_t temp_source{ source };

	status[source] = STATUS::TREE;

	do
	{
		for (const auto& itr : adj_list_[temp_source]) {
			switch (status[itr.first])
			{
			case STATUS::UNSEEN:
				set.insert(std::make_tuple(memo[temp_source] + itr.second, temp_source, itr.first));
				status[itr.first] = STATUS::FRINGE;
				break;
			case STATUS::FRINGE:
				set.insert(std::make_tuple(memo[temp_source] + itr.second, temp_source, itr.first));
				break;
			default:
				break;
			}
		}

		while (!set.empty() && status[std::get<2>(set.begin().operator*())] == STATUS::TREE)
			set.erase(set.begin());
		if (set.empty()) break;
		pair_vector.push_back(std::make_pair(std::get<1>(set.begin().operator*()), std::get<2>(set.begin().operator*())));
		temp_source = std::get<2>(set.begin().operator*());
		memo[temp_source] = std::get<0>(set.begin().operator*());
		status[temp_source] = STATUS::TREE;
	} while (temp_source != to && !set.empty());

	//for (int j = 0; j < size_; j++) {
	//	if (j == source) std::cout << 0 << '\n';
	//	else if (memo[j] == 0) std::cout << "INF" << '\n';
	//	else std::cout << memo[j] << '\n';
	//}//Sum of weights

	PairVector pair_vector_two;//To store correct path
	size_t last{ 0 };
	while (!pair_vector.empty()) {
		pair_vector_two.push_back(pair_vector.back());
		last = pair_vector.back().first;
		pair_vector.pop_back();
		while (!pair_vector.empty() && pair_vector.back().second != last)
			pair_vector.pop_back();
	}
	std::reverse(pair_vector_two.begin(), pair_vector_two.end());

	return std::make_pair(pair_vector_two, memo);
}

SSSP::ReturnPair SSSP::DijkstraWithMat(const size_t& source, const size_t& to) const
{
	PairVector pair_vector;//To store detail of path.
	std::vector<STATUS> status(size_, STATUS::UNSEEN);
	Set set;
	Vector memo(size_, 0);//Memo distances to each vertex
	size_t temp_source{ source };

	status[source] = STATUS::TREE;

	do
	{
		for (size_t j = 0; j < size_; j++)
		{
			if (adj_matrix_[temp_source][j] > 0) {
				switch (status[j])
				{
				case STATUS::UNSEEN:
					set.insert(std::make_tuple(memo[temp_source] + adj_matrix_[temp_source][j] , temp_source, j));
					status[j] = STATUS::FRINGE;
					break;
				case STATUS::FRINGE:
					set.insert(std::make_tuple(memo[temp_source] + adj_matrix_[temp_source][j], temp_source, j));
					break;
				default:
					break;
				}
			}
		}

		while (!set.empty() && status[std::get<2>(set.begin().operator*())] == STATUS::TREE)
			set.erase(set.begin());
		if (set.empty()) break;
		pair_vector.push_back(std::make_pair(std::get<1>(set.begin().operator*()), std::get<2>(set.begin().operator*())));
		temp_source = std::get<2>(set.begin().operator*());
		memo[temp_source] = std::get<0>(set.begin().operator*());
		status[temp_source] = STATUS::TREE;
	} while (temp_source != to && !set.empty());

	if (pair_vector.empty() || pair_vector.back().second != to)
		return ReturnPair();

	PairVector pair_vector_two;//To store correct path
	size_t last{ 0 };

	while (!pair_vector.empty()) {
		pair_vector_two.push_back(pair_vector.back());
		last = pair_vector.back().first;
		pair_vector.pop_back();
		while (!pair_vector.empty() && pair_vector.back().second != last)
			pair_vector.pop_back();
	}
	std::reverse(pair_vector_two.begin(), pair_vector_two.end());

	return std::make_pair(pair_vector_two, memo);
}

std::vector<SSSP::PairVector> SSSP::DijkstraAllPath(const size_t& source, const size_t& to) const
{
	PairVector pair_vector;//To store detail of path.
	std::vector<SSSP::PairVector> return_vector;
	std::vector<STATUS> status(size_, STATUS::UNSEEN);
	Set set;
	Vector memo(size_, 0);//Memo distances to each vertex
	size_t temp_source{ source };
	int value{ 1<<18 };

	status[source] = STATUS::TREE;

	do
	{
		for (const auto& itr : adj_list_[temp_source]) {
			switch (status[itr.first])
			{
			case STATUS::UNSEEN:
				set.insert(std::make_tuple(memo[temp_source] + itr.second, temp_source, itr.first));
				status[itr.first] = STATUS::FRINGE;
				break;
			case STATUS::FRINGE:
				set.insert(std::make_tuple(memo[temp_source] + itr.second, temp_source, itr.first));
				break;
			default:
				break;
			}
		}
		while (!set.empty() && status[std::get<2>(set.begin().operator*())] == STATUS::TREE)
			set.erase(set.begin());
		if (set.empty()) break;

		if (std::get<2>(set.begin().operator*()) == to) {
			value = std::get<0>(set.begin().operator*());
			memo[std::get<1>(set.begin().operator*())] = std::get<0>(set.begin().operator*());
			while (!set.empty() && std::get<0>(set.begin().operator*()) <= value && std::get<2>(set.begin().operator*()) == to) {
				pair_vector.push_back(std::make_pair(std::get<1>(set.begin().operator*()), std::get<2>(set.begin().operator*())));
				set.erase(set.begin());
			}
			break;
		}
		pair_vector.push_back(std::make_pair(std::get<1>(set.begin().operator*()), std::get<2>(set.begin().operator*())));
		temp_source = std::get<2>(set.begin().operator*());
		memo[temp_source] = std::get<0>(set.begin().operator*());
		status[temp_source] = STATUS::TREE;
	} while (temp_source != to && !set.empty());

	//for (const auto& itr : pair_vector)
	//	std::cout << itr.first << ' ' << itr.second << '\n';

	while (!pair_vector.empty()) {
		PairVector pair_vector_two;//To store correct path
		size_t last{ 0 };
		while (!pair_vector.empty() && pair_vector.back().second != to)
			pair_vector.pop_back();
		if (pair_vector.empty()) break;

		PairVector::const_reverse_iterator r_iter{ pair_vector.crbegin() };

		while (r_iter != pair_vector.crend()) {
			pair_vector_two.push_back(r_iter.operator*());
			last = pair_vector_two.back().first;
			while (r_iter != pair_vector.crend() && r_iter.operator*().second != last)
				r_iter++;
		}
		std::reverse(pair_vector_two.begin(), pair_vector_two.end());
		return_vector.push_back(pair_vector_two);
		pair_vector.pop_back();
	}
	

	return return_vector;
}

SSSP::ReturnPair SSSP::K_Dijkstra_NoReplace(const size_t& source, const size_t& to, unsigned int K)
{
	Matrix temp_adj_matrix{ adj_matrix_ };

	for (const auto& itr : DijkstraAllPath(source, to)) {
		for (const auto& itr_2 : itr) {
			adj_matrix_[itr_2.first][itr_2.second] = 0;
		}
	}
	
	ReturnPair pair = DijkstraWithMat(source, to);
	adj_matrix_ = temp_adj_matrix;

	return pair;
}

SSSP::Vector SSSP::BellmanFord(const size_t& source) const
{
	PairVector vector;
	std::vector<STATUS> status(size_ , STATUS::UNSEEN);
	Vector memo(size_, 1<<18);
	memo[source] = 0;
	status[source] = STATUS::TREE;

	for (size_t i = 0; i < size_ - 1; i++)
	{
		for (const auto& itr : edge_list_) {
			if (status[std::get<0>(itr)] == STATUS::UNSEEN) continue;
			memo[std::get<1>(itr)] = std::get<2>(itr) + memo[std::get<0>(itr)] < memo[std::get<1>(itr)] ?
				std::get<2>(itr) + memo[std::get<0>(itr)] : memo[std::get<1>(itr)];
			status[std::get<1>(itr)] = STATUS::TREE;
		}
	}//N - 1번 Edge-relaxation

	for (const auto& itr : edge_list_) {
		if (status[std::get<0>(itr)] == STATUS::UNSEEN) continue;
		else if (std::get<2>(itr) + memo[std::get<0>(itr)] < memo[std::get<1>(itr)] && status[std::get<1>(itr)] == STATUS::TREE) return Vector();
	}

	return memo;
}

SSSP::Vector SSSP::BellmanFordUpgrade(const size_t& source) const
{
	PairVector vector;
	std::vector<STATUS> status(size_, STATUS::UNSEEN);
	Vector memo(size_, 1 << 30);
	memo[source] = 0;
	status[source] = STATUS::TREE;

	//음수 사이클이 Source와 연결되어 있는지 확인하는 과정
	std::stack<size_t> stack;
	std::vector<STATUS> status_dfs(size_, STATUS::UNSEEN);
	size_t temp;
	stack.push(source);
	status_dfs[source] = STATUS::TREE;

	while (!stack.empty()) {
		temp = stack.top();
		stack.pop();
		for (const auto& itr : adj_list_[temp])
			if (status_dfs[itr.first] == STATUS::UNSEEN) { stack.push(itr.first), status_dfs[itr.first] = STATUS::TREE; }
	}
	//DFS를 이용하여 status_dfs에 정리. 연결되어 있지 않으면 UNSEEN, 연결되어 있으면 TREE

	for (size_t i = 0; i < size_ - 1; i++)
	{
		for (const auto& itr : edge_list_) {
			if (status[std::get<0>(itr)] == STATUS::UNSEEN) continue;
			memo[std::get<1>(itr)] = std::get<2>(itr) + memo[std::get<0>(itr)] < memo[std::get<1>(itr)] ?
				std::get<2>(itr) + memo[std::get<0>(itr)] : memo[std::get<1>(itr)];
			status[std::get<1>(itr)] = STATUS::TREE;
		}
	}

	for (size_t i = 0; i < size_; i++)
		if (status_dfs[i] == STATUS::UNSEEN)
			memo[i] = -1;
	//연결되어 있지 않은 모든 정점까지의 거리를 -1로.

	for (const auto& itr : edge_list_) {
		if (status[std::get<0>(itr)] == STATUS::UNSEEN) continue;
		else if (std::get<2>(itr) + memo[std::get<0>(itr)] < memo[std::get<1>(itr)] && status_dfs[std::get<1>(itr)] == STATUS::TREE) return Vector();
	}

	return memo;
}
