#pragma once

//  https://leetcode.com/problems/unique-morse-code-words/
/*
* 804. Unique Morse Code Words
* 
* International Morse Code defines a standard encoding where each letter is mapped to
* a series of dots and dashes, as follows:
*    'a' maps to ".-",
*    'b' maps to "-...",
*    'c' maps to "-.-.", and so on.
*
* For convenience, the full table for the 26 letters of the English alphabet is given below:
[".-","-...","-.-.","-..",".","..-.","--.","....","..",".---","-.-",".-..","--","-.","---",".--.","--.-",".-.","...","-","..-","...-",".--","-..-","-.--","--.."]
*
* Given an array of strings words where each word can be written as a concatenation of
* the Morse code of each letter.
*
*    For example, "cab" can be written as "-.-..--...", which is the concatenation
*      of "-.-.", ".-", and "-...". We will call such a concatenation the
*      transformation of a word.
*
* Return the number of different transformations among all words we have.
* 
* Example 1:
* Input: words = ["gin","zen","gig","msg"]
* Output: 2
* Explanation: The transformation of each word is:
* "gin" -> "--...-."
* "zen" -> "--...-."
* "gig" -> "--...--."
* "msg" -> "--...--."
* There are 2 different transformations: "--...-." and "--...--.".
*
* Example 2:
* Input: words = ["a"]
* Output: 1
*
* Constraints:
*   1 <= words.length <= 100
*   1 <= words[i].length <= 12
*   words[i] consists of lowercase English letters.
*/

#include <string>
#include <vector>
#include <set>
#include <gtest/gtest.h>
#include "../util/std_util.h"

namespace UniqueMorseCodeWords {
    const char* morseTable[] = {
        ".-","-...","-.-.","-..",".","..-.","--.","....","..",".---","-.-",".-..","--","-.","---",".--.","--.-",".-.","...","-","..-","...-",".--","-..-","-.--","--.."
    };

    class Solution {
    public:
        int uniqueMorseRepresentations(std::vector<std::string>& words) {
            std::set<std::string> codes;
            for (std::string s : words) {
                codes.insert(morseCodeOf(s));
            }
            return codes.size();
        }

        std::string morseCodeOf(std::string& word) {
            std::string r;
            for (char c : word) {
                r.append(morseTable[c - 'a']);
            }
            return r;
        }
    };

    int testUniqueMorseRepresentations(const char* input) {
        std::vector<std::string> words = StdUtil::generateStringVector(input);
        return Solution().uniqueMorseRepresentations(words);
    }
}

TEST(_804_UniqueMorseCodeWords, SimpleCases) {
    /*
    * Example 1:
    * Input: words = ["gin","zen","gig","msg"]
    * Output: 2
    */
    EXPECT_EQ(UniqueMorseCodeWords::testUniqueMorseRepresentations("[gin,zen,gig,msg]"), 2);
}