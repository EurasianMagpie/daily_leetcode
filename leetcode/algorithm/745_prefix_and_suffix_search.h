#pragma once

// https://leetcode.com/problems/prefix-and-suffix-search/
/*
* 745. Prefix and Suffix Search
* 
* Design a special dictionary with some words that searchs the words in it by a prefix and a suffix.
*
* Implement the WordFilter class:
*  - WordFilter(string[] words) Initializes the object with the words in the dictionary.
*  - f(string prefix, string suffix) Returns the index of the word in the dictionary,
*    which has the prefix prefix and the suffix suffix. If there is more than one valid index,
*    return the largest of them. If there is no such word in the dictionary, return -1.
* 
* Example 1:
* Input
*  ["WordFilter", "f"]
*  [[["apple"]], ["a", "e"]]
* Output
*  [null, 0]
* Explanation
*  WordFilter wordFilter = new WordFilter(["apple"]);
*  wordFilter.f("a", "e"); // return 0, because the word at index 0 has prefix = "a" and suffix = 'e".
*
* Constraints:
*  - 1 <= words.length <= 15000
*  - 1 <= words[i].length <= 10
*  - 1 <= prefix.length, suffix.length <= 10
*  - words[i], prefix and suffix consist of lower-case English letters only.
*  - At most 15000 calls will be made to the function f.
*/

#include <vector>
#include <string>
#include <list>
#include <set>
#include <algorithm>
#include <gtest/gtest.h>
#include "../util/std_util.h"

namespace PrefixandSuffixSearch {

    /*
    * Still Something Wrong
    */
    class WordFilter {

        static const int WORD_TRIE_WIDTH = 32;

        struct WordInfo {
            int position;
            int size;
        };

        struct WordTrieNode {
            char key;
            WordInfo* wordInfo;
            WordTrieNode* next[WORD_TRIE_WIDTH];

            WordTrieNode(char k) : WordTrieNode(k, nullptr) {}

            WordTrieNode(char k, WordInfo* info) : key(k), wordInfo(info) {
                memset(next, 0, sizeof(WordTrieNode*) * WORD_TRIE_WIDTH);
            }
        };

        WordTrieNode* mPrefixRoot;
        WordTrieNode* mSuffixRoot;
        std::map<uint32_t, std::set<WordInfo*>> mPrefixCache;
        std::map<uint32_t, std::set<WordInfo*>> mSuffixCache;
        std::map<uint64_t, int> mResultCache;

    public:
        WordFilter(std::vector<std::string>& words) : mPrefixRoot(nullptr) {
            initWordTrieNode(words);
        }

        ~WordFilter() {
            releaseWordTrieNode(mPrefixRoot);
            releaseWordTrieNode(mSuffixRoot);
        }

        int f(std::string prefix, std::string suffix) {
            return findWord(prefix, suffix);
        }

    private:
        void releaseWordTrieNode(WordTrieNode* root) {
            if (root) {
                return;
            }
            std::list<WordTrieNode*> nodes;
            nodes.push_back(root);
            while (!nodes.empty()) {
                WordTrieNode* node = nodes.front();
                for (int i = 0; i < WORD_TRIE_WIDTH; i++) {
                    if (node->next[i]) {
                        nodes.push_back(node->next[i]);
                    }
                }
                if (node->wordInfo) {
                    delete node->wordInfo;
                }
                delete node;
                nodes.pop_front();
            }
        }

        void initWordTrieNode(std::vector<std::string>& words) {
            mPrefixRoot = new WordTrieNode('\0');
            mSuffixRoot = new WordTrieNode('\0');
            for (int i = 0; i < words.size(); i++) {
                addWord(mPrefixRoot, mSuffixRoot, words.at(i).c_str(), words.at(i).size(), 0, i);
            }
        }

        void addWord(WordTrieNode* pPrefix, WordTrieNode* pSuffix, const char* word, int sz, int index, int position) {

            char c1 = *(word + index);
            int prefixIndex = indexOf(c1);
            WordTrieNode* prefixNode = pPrefix->next[prefixIndex];
            if (!prefixNode) {
                prefixNode = new WordTrieNode(c1);
                pPrefix->next[prefixIndex] = prefixNode;
            }

            char c2 = *(word + sz - 1 - index);
            int suffixIndex = indexOf(c2);
            WordTrieNode* suffixNode = pSuffix->next[suffixIndex];
            if (!suffixNode) {
                suffixNode = new WordTrieNode(c2);
                pSuffix->next[suffixIndex] = suffixNode;
            }

            if (index == sz - 1) {
                WordInfo* wordInfo = new WordInfo();
                wordInfo->position = position;
                wordInfo->size = sz;
                prefixNode->wordInfo = wordInfo;
                suffixNode->wordInfo = wordInfo;
            }
            else {
                addWord(prefixNode, suffixNode, word, sz, index + 1, position);
            }
        }

        int findWord(std::string& prefix, std::string& suffix) {
            uint64_t h1 = (uint64_t)(hashOf(prefix));
            uint64_t h2 = (uint64_t)(hashOf(suffix));
            uint64_t key = (h1 << 32) | h2;
            auto ite = mResultCache.find(key);
            if (ite != mResultCache.end()) {
                return ite->second;
            }
            std::set<WordInfo*> r1 = findWordByPrefix(prefix);
            std::set<WordInfo*> r2 = findWordBySuffix(suffix);
            int sz = std::min(r1.size(), r2.size());
            if (!sz) {
                return -1;
            }
            std::vector<WordInfo*> r(sz);
            std::set_intersection(r1.begin(), r1.end(), r2.begin(), r2.end(), r.begin());

            int position = -1;
            int size = 0;
            for (auto ite = r.begin(); ite != r.end(); ite++) {
                WordInfo* p = *ite;
                if (!p) {
                    break;
                }
                if (p->size > size) {
                    size = p->size;
                    position = p->position;
                }
                else if (p->size == size && p->position > position) {
                    size = p->size;
                    position = p->position;
                }
            }
            mResultCache[key] = position;
            return position;
        }

        std::set<WordInfo*> findWordByPrefix(std::string& prefix) {
            uint32_t key = hashOf(prefix);
            auto ite = mPrefixCache.find(key);
            if (ite != mPrefixCache.end()) {
                return ite->second;
            }
            std::set<WordInfo*> result;
            WordTrieNode* pNode = mPrefixRoot;
            for (int i = 0; i < prefix.size(); i++) {
                char c = prefix.at(i);
                WordTrieNode* pNextNode = pNode->next[indexOf(c)];
                if (pNextNode) {
                    pNode = pNextNode;
                }
                else {
                    pNode = nullptr;
                    break;
                }
            }

            if (pNode) {
                std::list<WordTrieNode*> possibleNodes;
                possibleNodes.push_back(pNode);
                while (!possibleNodes.empty())
                {
                    WordTrieNode* node = possibleNodes.front();
                    if (node->wordInfo) {
                        result.insert(node->wordInfo);
                    }
                    for (int i = 0; i < WORD_TRIE_WIDTH; i++) {
                        if (node->next[i]) {
                            possibleNodes.push_back(node->next[i]);
                        }
                    }
                    possibleNodes.pop_front();
                }
            }
            mPrefixCache[key] = result;
            return result;
        }

        std::set<WordInfo*> findWordBySuffix(std::string& suffix) {
            uint32_t key = hashOf(suffix);
            auto ite = mSuffixCache.find(key);
            if (ite != mSuffixCache.end()) {
                return ite->second;
            }
            std::set<WordInfo*> result;
            WordTrieNode* pNode = mSuffixRoot;
            for (int i = suffix.size() - 1; i >= 0; i--) {
                char c = suffix.at(i);
                WordTrieNode* pNextNode = pNode->next[indexOf(c)];
                if (pNextNode) {
                    pNode = pNextNode;
                }
                else {
                    pNode = nullptr;
                    break;
                }
            }

            if (pNode) {
                std::list<WordTrieNode*> possibleNodes;
                possibleNodes.push_back(pNode);
                while (!possibleNodes.empty())
                {
                    WordTrieNode* node = possibleNodes.front();
                    if (node->wordInfo) {
                        result.insert(node->wordInfo);
                    }
                    for (int i = 0; i < WORD_TRIE_WIDTH; i++) {
                        if (node->next[i]) {
                            possibleNodes.push_back(node->next[i]);
                        }
                    }
                    possibleNodes.pop_front();
                }
            }
            mSuffixCache[key] = result;
            return result;
        }

        inline int indexOf(char c) {
            return c - 'a';
        }

        inline uint32_t hashOf(std::string str) {
            return std::hash<std::string>{}(str);
        }
    };

    /**
     * Your WordFilter object will be instantiated and called as such:
     * WordFilter* obj = new WordFilter(words);
     * int param_1 = obj->f(prefix,suffix);
     */

}

TEST(_745_PrefixandSuffixSearch, SimpleCases) {
    /*
    * Example 1:
    * Input
    *  ["WordFilter", "f"]
    *  [[["apple"]], ["a", "e"]]
    * Output
    *  [null, 0]
    */
    std::vector<std::string> words1 = StdUtil::generateStringVector("[[aabbccdd,apple]]");
    PrefixandSuffixSearch::WordFilter filter1(words1);

    EXPECT_EQ(filter1.f("a", "e"), 1);
    EXPECT_EQ(filter1.f("aabb", "ccdd"), 0);


    /*
    * Input
    ["WordFilter","f","f","f","f","f","f","f","f","f","f"]
    [[["cabaabaaaa","ccbcababac","bacaabccba","bcbbcbacaa","abcaccbcaa","accabaccaa","cabcbbbcca","ababccabcb","caccbbcbab","bccbacbcba"]],
    ["bccbacbcba","a"],["ab","abcaccbcaa"],["a","aa"],["cabaaba","abaaaa"],["cacc","accbbcbab"],["ccbcab","bac"],["bac","cba"],["ac","accabaccaa"],["bcbb","aa"],["ccbca","cbcababac"]]

    Expected
    [null,9,4,5,0,8,1,2,5,3,1]

    Output
    [null,9,4,4,0,8,1,2,5,3,1]
    */

    std::vector<std::string> words2 = StdUtil::generateStringVector("[[cabaabaaaa,ccbcababac,bacaabccba,bcbbcbacaa,abcaccbcaa,accabaccaa,cabcbbbcca,ababccabcb,caccbbcbab,bccbacbcba]]");
    PrefixandSuffixSearch::WordFilter filter2(words2);

    // 4 - abcaccbcaa
    // 5 - accabaccaa
    EXPECT_EQ(filter2.f("a", "aa"), 5);
    //EXPECT_EQ(filter2.f("aabb", "ccdd"), 0);
}