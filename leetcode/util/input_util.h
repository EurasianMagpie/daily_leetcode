#pragma once

#include <string>
#include <vector>

class InputUtil {

public:
    /*
    * 解析逗号分隔的输入字符串
    * 格式如 [1,2,3,4,5,6,null,8]
    */
    static std::vector<std::string> parseCommonInputString(const char* input) {
        std::vector<std::string> values;
        if (!input || strlen(input) == 0) {
            return values;
        }

        std::string str(input);
        const char* toBeTrim = " \t[]";
        str.erase(str.find_last_not_of(toBeTrim) + 1);
        str.erase(0, str.find_first_not_of(toBeTrim));

        std::string delimiter = ",";
        std::size_t pos = 0;
        std::string token;
        while ((pos = str.find(delimiter)) != std::string::npos) {
            token = str.substr(0, pos);
            values.push_back(token);
            str.erase(0, pos + delimiter.length());
        }
        if (str.length() > 0) {
            values.push_back(str);
        }
        return values;
    }

};