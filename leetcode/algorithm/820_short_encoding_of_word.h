#pragma once

// https://leetcode.com/problems/short-encoding-of-words/
/*
* 820. Short Encoding of Words
* 
* A valid encoding of an array of words is any reference string s and array of indices indices such that:
*  - words.length == indices.length
*  - The reference string s ends with the '#' character.
*  - For each index indices[i], the substring of s starting from indices[i] and up to (but not including)
*    the next '#' character is equal to words[i].
* Given an array of words, return the length of the shortest reference string s possible of any valid encoding 
* of words.
*
*
* Example 1:
* Input: words = ["time", "me", "bell"]
* Output: 10
* Explanation: A valid encoding would be s = "time#bell#" and indices = [0, 2, 5].
* words[0] = "time", the substring of s starting from indices[0] = 0 to the next '#' is underlined in "time#bell#"
* words[1] = "me", the substring of s starting from indices[1] = 2 to the next '#' is underlined in "time#bell#"
* words[2] = "bell", the substring of s starting from indices[2] = 5 to the next '#' is underlined in "time#bell#"
*
* Example 2:
* Input: words = ["t"]
* Output: 2
* Explanation: A valid encoding would be s = "t#" and indices = [0].
*
*
* Constraints:
*  + 1 <= words.length <= 2000
*  + 1 <= words[i].length <= 7
*  + words[i] consists of only lowercase letters.
*/

#include <string>
#include <vector>
#include <list>
#include <gtest/gtest.h>
#include "../util/std_util.h"

namespace ShortEncodingOfWords {

    /*
    * 将所有单词按字母顺序的倒序，存入trie，
    * 最终统计 所有叶子节点的单词长度 + 实际使用的单词个数
    */
    class EncodingTrie {
        static const int TRIE_NODE_NEXT_LENGTH = 27;

        struct TrieNode {
            int depth;
            TrieNode** next;
            TrieNode(int d) : depth(d), next(nullptr) {}
        };

        TrieNode* mRoot;
    public:

        int calcMinimumLengthEncoding(std::vector<std::string>& words) {
            mRoot = createTrieNode(0);
            for (auto ite = words.begin(); ite != words.end(); ite++) {
                std::string& word = *ite;
                TrieNode* node = mRoot;
                int sz = word.size();
                for (int i = sz - 1; i >= 0; i--) {
                    node = addTrieNodeTo(node, indexOf(word.at(i)), sz - i);
                }
            }

            int ans(0);
            std::list<TrieNode*> nodes;
            nodes.push_back(mRoot);
            while (!nodes.empty()) {
                TrieNode* node = nodes.front();
                if (node->next) {
                    for (int i = 0; i < TRIE_NODE_NEXT_LENGTH; i++) {
                        if (node->next[i]) {
                            nodes.push_back(node->next[i]);
                        }
                    }
                }
                else {
                    ans += node->depth + 1;
                }
                nodes.pop_front();
            }
            releaseTrie(mRoot);
            return ans;
        }

    private:
        TrieNode* createTrieNode(int depth) {
            return new TrieNode(depth);
        }

        void releaseTrie(TrieNode* root) {
            if (root) {
                if (root->next) {
                    for (int i = 0; i < TRIE_NODE_NEXT_LENGTH; i++) {
                        if (root->next[i]) {
                            releaseTrie(root->next[i]);
                        }
                    }
                    delete[] root->next;
                }
                delete root;
            }
        }

        TrieNode* addTrieNodeTo(TrieNode* parent, int index, int depth) {
            if (!parent->next) {
                parent->next = new TrieNode * [TRIE_NODE_NEXT_LENGTH];
                memset(parent->next, 0, sizeof(TrieNode*) * TRIE_NODE_NEXT_LENGTH);
            }
            if (!parent->next[index]) {
                parent->next[index] = createTrieNode(depth);
            }
            return parent->next[index];
        }

        inline int indexOf(char c) {
            return c - 'a';
        }
    };
    
    class Solution {
    public:
        int minimumLengthEncoding(std::vector<std::string>& words) {
            return EncodingTrie().calcMinimumLengthEncoding(words);
        }
    };

    int testMinimumLengthEncoding(const char* input) {
        std::vector<std::string> words = StdUtil::generateStringVector(input);
        return Solution().minimumLengthEncoding(words);
    }
}

TEST(_820_ShortEncodingOfWords, SimpleCases) {
    /*
    * Example 1:
    * Input: words = ["time","me","bell"]
    * Output: 10
    */
    EXPECT_EQ(ShortEncodingOfWords::testMinimumLengthEncoding("[time,me,bell]"), 10);

    /*
    * Example 2:
    * Input: words = ["t"]
    * Output: 2
    */
    EXPECT_EQ(ShortEncodingOfWords::testMinimumLengthEncoding("[t]"), 2);
}