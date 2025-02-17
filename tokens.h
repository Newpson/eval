#pragma once

#include <string>
#include <vector>

std::vector<std::string_view> tokenize(
        const std::string &string,
        const std::string &delimiters);
