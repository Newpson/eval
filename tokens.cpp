#include <string>
#include <string_view>
#include <vector>

#include "tokens.h"

static
bool is_delimiter(const char c, const std::string &delimiters)
{
    for (const char d : delimiters)
        if (c == d)
            return true;
    return false;
}

std::vector<std::string_view> tokenize(
        const std::string &string,
        const std::string &delimiters)
{
    std::vector<std::string_view> tokens;
    std::string::const_iterator token_begin = string.begin();
    for (auto string_iter = string.begin(); string_iter != string.end(); ++string_iter) {
        if (is_delimiter(*string_iter, delimiters)) {
            std::string::const_iterator token_end = string_iter;
            if (token_end - token_begin > 0)
                tokens.push_back(std::string_view(token_begin.base(), token_end.base()));
            tokens.push_back(std::string_view(string_iter.base(), 1));
            token_begin = token_end + 1;
        }
    }
    return tokens;
}
