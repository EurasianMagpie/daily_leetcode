#pragma once

#include <vector>
#include "input_util.h"

class StdUtil {

public:
	/*
	  根据输入构造一个 std::vector
	  @input vector描述数组的字符串描述
	  返回不为空
	*/
	static std::vector<int> generateIntVector(const char* input) {
		auto inputs = InputUtil::parseCommonInputString(input);
		std::vector<int> ret;
		std::size_t sz = inputs.size();
		for (auto ite = inputs.begin(); ite != inputs.end(); ite++) {
			ret.push_back(std::atoi(ite->c_str()));
		}
		return ret;
	}

	static std::vector<std::string> generateStringVector(const char* input) {
		return InputUtil::parseCommonInputString(input);
	}

	template <class _Ty>
	static bool compareEqualVector(std::vector<_Ty>& lhs, std::vector<_Ty>& rhs) {
		if (lhs.size() != rhs.size()) {
			return false;
		}
		auto itel = lhs.begin();
		auto iter = rhs.begin();
		for (; itel != lhs.end() && iter != rhs.end(); itel++, iter++)
		{
			if (*itel != *iter) {
				return false;
			}
		}
		return true;
	}
};