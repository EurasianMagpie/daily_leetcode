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
	static std::vector<int> generateVector(const char* input) {
		auto inputs = InputUtil::parseCommonInputString(input);
		std::vector<int> ret;
		std::size_t sz = inputs.size();
		for (auto ite = inputs.rbegin(); ite != inputs.rend(); ite++) {
			ret.push_back(std::atoi(ite->c_str()));
		}
		return ret;
	}

};