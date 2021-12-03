#include <iostream>
#include <string>
#include <vector>
#include <string_view>

class KMP : public std::exception {
public: 
	void SetFailure() {
		failure_.clear();
		failure_.resize(pattern_size_ , 0);
		size_t i = 1;
		size_t j = 0;
		while(i < pattern_size_){
			if (pattern_[i] == pattern_[j]) {
				failure_[i] = j + 1;
				i++;
				j++;
			}
			else if (j > 0)
				j = failure_[j - 1];
			else {
				failure_[i] = 0;
				i++;
			}
		}
	}
	void Matching() const {
		size_t i = 0;
		size_t j = 0;
		std::vector<unsigned int> index;

		if (pattern_size_ == 1) {//brute_force
			while (i < text_size_) {
				if (pattern_[0] == text_[i])
					index.push_back(i + 2 - pattern_size_);
				i++;
			}
			std::cout << index.size() << '\n';
			if (index.empty()) return;
			for (const auto& itr : index)
				std::cout << itr << ' ';
			return;
		}

		while (i < text_size_) {
			if (text_[i] == pattern_[j]) {
				if (j == pattern_size_ - 1) {
					index.push_back(i + 2 - pattern_size_); 
					j = failure_[j - 1];
				}
				else {
					i++;
					j++;
				}
			}
			else {
				if (j > 0) j = failure_[j - 1];
				else i++;
			}
		}
		std::cout << index.size() << '\n';
		if (index.empty()) return;
		for (const auto& itr : index)
			std::cout << itr << ' ';
	}
public:
	void set_text() { 
		text_.reserve(1000003);
		std::getline(std::cin, text_);
		text_size_ = text_.size();
	}
	void set_pattern() { 
		pattern_.reserve(1000003);
		std::getline(std::cin, pattern_);
		pattern_size_ = pattern_.size();
	}
	std::string_view get_text() const { return text_; }
	std::string_view get_pattern() const { return pattern_; }
	void PrintFailure() const {
		if (failure_.empty()) return;
		for (const auto& itr : failure_)
			std::cout << itr << ' ';
		std::cout << std::endl;
	}
public://Constructor, Destructor
	KMP(const std::string& text, const std::string& pattern) :text_(text), pattern_(pattern), text_size_(text_.size()) , pattern_size_(pattern_.size()){};
	KMP() :text_(std::string()), pattern_(std::string()) , text_size_(0) , pattern_size_(0) {};
private:
	std::string text_;
	std::string pattern_;
	size_t text_size_;
	size_t pattern_size_;
	std::vector<unsigned int> failure_;
};

//int main() {
//	KMP kmp;
//	kmp.set_text();
//	kmp.set_pattern();
//	kmp.SetFailure();
//
//	//std::vector<unsigned int> match{ kmp.Matching() };
//	kmp.Matching();
//}