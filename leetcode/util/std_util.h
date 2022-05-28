#pragma once

#include <vector>
#include "input_util.h"

class StdUtil {

public:
	/*
	  �������빹��һ�� std::vector
	  @input vector����������ַ�������
	  ���ز�Ϊ��
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