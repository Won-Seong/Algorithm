#include "TopologicalOrder.h"

void TopologicalOrder::Insert(const size_t& from, const size_t& to)
{
	out_matrix_[from].push_back(to);
	in_matrix_[to].push_back(from);
	in_degree_vector_[to]++;
}

void TopologicalOrder::TopologicalPrint() const
{
	for (const auto& itr : TopologicalUtility())
		std::cout << itr + 1 << ' ';
	std::cout << std::endl;
}

TopologicalOrder::IndexVector TopologicalOrder::TopologicalReturn() const
{
	return TopologicalUtility();
}

TopologicalOrder::IndexVector TopologicalOrder::TopologicalUtility(const size_t& index) const
{
	Vector temp_vector{ in_degree_vector_};
	IndexVector index_vector;
	std::queue<size_t> queue;
	index_vector.push_back(index);
	queue.push(index);
	
	while (index_vector.size() < size_) {
		while (!queue.empty()) {
			for (const auto& itr : out_matrix_[queue.front()])
				if (temp_vector[itr] > 1) temp_vector[itr]--;
				else if (temp_vector[itr] == 1) { temp_vector[itr]--; queue.push(itr); index_vector.push_back(itr); }
			queue.pop();
		}
	}
	return index_vector;
}

TopologicalOrder::IndexVector TopologicalOrder::TopologicalUtility() const
{
	Vector temp_vector{ in_degree_vector_ };
	IndexVector index_vector;
	std::queue<size_t> queue;

	for (size_t i = 0; i < temp_vector.size(); i++)
	{
		if (temp_vector[i] == 0) queue.push(i);//������ ������ ���� ������ �ʱ⿡ ��� Push
	}

	while (index_vector.size() < size_) {//��� ������ �� �� ������
		while (!queue.empty()) {
			index_vector.push_back(queue.front());
			for (const auto& itr : out_matrix_[queue.front()])
				if (temp_vector[itr] > 1) temp_vector[itr]--;//������ ������ In degree�� 1��ŭ ���Ѵ�.
				else if (temp_vector[itr] == 1) { temp_vector[itr]--; queue.push(itr);  }//�� ��, In degree�� 0�� �Ǵ� ������ ��� Push
			queue.pop();
		}

	}
	return index_vector;
}
