#pragma once

#include <string>
#include <iostream>
#include "../base/base.h"

#include "verify_result.h"
#include "list_util.h"
#include "binary_tree_util.h"


template<class ResultType>
class BaseCase {
public:
	std::string mInput;
	ResultType mExpected;
	ResultType mOutput;
	VerifyResult mVerifyResult;

public:
	BaseCase(const char* caseDescription, ResultType expected)
		: mInput(caseDescription), mExpected(expected), mOutput(0), mVerifyResult(VerifyResult::VERIFY_UNKNOWN)
	{}
};


template<class InputType, class ResultType>
class BaseCaseChecker {
public:
	typedef ResultType(*CaseExecutor)(InputType input);
	typedef VerifyResult(*ResultVerifier)(ResultType expected, ResultType output);

protected:
	BaseCaseChecker<InputType, ResultType>::CaseExecutor mCaseExecutor;
	BaseCaseChecker<InputType, ResultType>::ResultVerifier mResultVerifier;

protected:
	static VerifyResult defaultResultVerifier(ResultType expected, ResultType output) {
		return expected == output ? VerifyResult::VERFIY_OK : VerifyResult::VERFIY_FAILED;
	}

protected:
	BaseCaseChecker(BaseCaseChecker<InputType, ResultType>::CaseExecutor caseExecutor,
		BaseCaseChecker<InputType, ResultType>::ResultVerifier resultVerifier = BaseCaseChecker<InputType, ResultType>::defaultResultVerifier)
		: mCaseExecutor(caseExecutor), mResultVerifier(resultVerifier)
	{}

public:
	/*
	bool verify(const char* input, const char* expected) {
		ResultType expetedResult = createExpectedResultObject(expected);
		BaseCase<ResultType> kase(input, expetedResult);
		bool r = verify(kase);
		releaseExpectedResultObject(expetedResult);
		return r;
	}//*/

	bool verify(const char* input, ResultType expected) {
		BaseCase<ResultType> kase(input, expected);
		return verify(kase);
	}

protected:
	virtual InputType createInputObject(std::string& kase) = 0;
	virtual void releaseInputObject(InputType inputObj) = 0;

protected:
	bool verify(BaseCase<ResultType>& kase) {
		InputType input = createInputObject(kase.mInput);
		kase.mOutput = mCaseExecutor(input);
		kase.mVerifyResult = mResultVerifier(kase.mExpected, kase.mOutput);
		releaseInputObject(input);
		printResult(kase);
		return kase.mVerifyResult == VerifyResult::VERFIY_OK;
	}

	virtual void printResult(BaseCase<ResultType>& kase) {
		std::cout << "-------------------------------------------" << std::endl;
		std::cout << "Input:   \t" << kase.mInput << std::endl;
		std::cout << "Expected:\t" << kase.mExpected << std::endl;
		switch (kase.mVerifyResult)
		{
		case VerifyResult::VERFIY_OK:
			std::cout << "Output:  \t" << kase.mOutput << "\t\033[32mOK\033[0m" << std::endl;
			break;
		case VerifyResult::VERFIY_FAILED:
			std::cout << "Output:  \t" << kase.mOutput << "\t\033[31mWrong\033[0m" << std::endl;
			break;
		case VerifyResult::VERIFY_UNKNOWN:
		default:
			std::cout << "Output:  \tN/A" << "\t\033[31mExecute Failed\033[0m" << std::endl;
			break;
		}
	}
};


template<class ResultType>
class StringCaseChecker : public BaseCaseChecker<std::string, ResultType> {
	typedef BaseCaseChecker<std::string, ResultType> ParentClassType;
public:
	StringCaseChecker(
		ParentClassType::CaseExecutor caseExecutor,
		ParentClassType::ResultVerifier resultVerifier = ParentClassType::defaultResultVerifier)
		: ParentClassType(caseExecutor, resultVerifier)
	{}

protected:
	virtual std::string createInputObject(std::string& input) {
		return input;
	}

	virtual void releaseInputObject(std::string root) {
		//no-op;
	}
};


template<class ResultType>
class LinkedListCaseChecker : public BaseCaseChecker<ListNode*, ResultType> {
	typedef BaseCaseChecker<ListNode*, ResultType> ParentClassType;
public:
	LinkedListCaseChecker(ParentClassType::CaseExecutor caseExecutor,
		ParentClassType::ResultVerifier resultVerifier = ParentClassType::defaultResultVerifier)
		: ParentClassType(caseExecutor, resultVerifier)
	{}

protected:
	virtual ListNode* createInputObject(std::string& input) {
		return ListUtil::generateLinkedList(input);
	}

	virtual void releaseInputObject(ListNode* pList) {
		ListUtil::releaseLinkedList(pList);
	}
};


template<class ResultType>
class BinaryTreeCaseChecker : public BaseCaseChecker<TreeNode*, ResultType> {
	typedef BaseCaseChecker<TreeNode*, ResultType> ParentClassType;
public:
	BinaryTreeCaseChecker(ParentClassType::CaseExecutor caseExecutor,
		ParentClassType::ResultVerifier resultVerifier = ParentClassType::defaultResultVerifier)
		: ParentClassType(caseExecutor, resultVerifier)
	{}

protected:
	virtual TreeNode* createInputObject(std::string& input) {
		return BinaryTreeUtil::generateBinaryTree(input.c_str());
	}

	virtual void releaseInputObject(TreeNode* root) {
		BinaryTreeUtil::releaseBinaryTree(root);
	}
};

