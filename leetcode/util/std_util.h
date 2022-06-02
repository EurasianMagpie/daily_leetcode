#pragma once

#include <vector>
#include <string>
#include "input_util.h"

class StdUtil {

public:
	struct IntTypeConverter {
		int operator() (std::string& s) {
			return std::atoi(s.c_str());
		}
	};

	struct CharTypeConverter {
		char operator() (std::string& s) {
			return s.at(0);
		}
	};

	struct StringTypeConverter {
		std::string operator() (std::string& s) {
			return s;
		}
	};

public:
	/*
	  根据输入构造一个 std::vector
	  @input vector描述数组的字符串描述
	  返回不为空
	*/
	template <class _Ty, class _TypeConverter>
	static std::vector<_Ty> generateVector(const char* input) {
		auto inputs = InputUtil::parseCommonInputString(input);
		std::vector<_Ty> ret;
		std::size_t sz = inputs.size();
		for (auto ite = inputs.begin(); ite != inputs.end(); ite++) {
			ret.push_back(_TypeConverter{}(*ite));
		}
		return ret;
	}

	static std::vector<int> generateIntVector(const char* input) {
		return generateVector<int, IntTypeConverter>(input);
	}

	static std::vector<char> generateCharVector(const char* input) {
		return generateVector<char, CharTypeConverter>(input);
	}

	static std::vector<std::string> generateStringVector(const char* input) {
		return generateVector<std::string, StringTypeConverter>(input);
	}


	/*
	* 比较两个 std::vector 是否内容相同
	*/
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


public:
	/*
	* 根据输入构造一个 std::vector 嵌套的 matrix
	*/
	template <class _Ty, class _TypeConverter>
	static std::vector<std::vector<_Ty>> generateVectorMatrix(std::initializer_list<const char*>& input) {
		std::vector<std::vector<_Ty>> ret;
		for (auto ite = input.begin(); ite != input.end(); ite++) {
			ret.push_back(generateVector<_Ty, _TypeConverter>(*ite));
		}
		return ret;
	}

	static std::vector<std::vector<int>> generateIntVectorMatrix(std::initializer_list<const char*>& input) {
		return generateVectorMatrix<int, IntTypeConverter>(input);
	}

	static std::vector<std::vector<char>> generateCharVectorMatrix(std::initializer_list<const char*>& input) {
		return generateVectorMatrix<char, CharTypeConverter>(input);
	}

	/*
	* 比较两个 std::vector 嵌套的 matrix 是否内容相同
	*/
	template <class _Ty>
	static bool compareEqualVectorMatrix(
		std::vector<std::vector<_Ty>>& lhs, std::vector<std::vector<_Ty>>& rhs) {
		std::size_t sz1 = lhs.size();
		std::size_t sz2 = rhs.size();
		if (sz1 != sz2) {
			return false;
		}
		for (std::size_t i = 0; i < sz1; i++) {
			if (!compareEqualVector<_Ty>(lhs.at(i), rhs.at(i))) {
				return false;
			}
		}
		return true;
	}
};