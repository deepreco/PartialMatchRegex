// Copyright 2019 Igor Turovskiy
// Copyright 2019 Sviatoslav Dmitriev
// Distributed under the Boost Software License, Version 1.0.
// See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt

#include "PartialMatchRegex.h"


const pcrecpp::RE PartialMatchRegex::RE_MATCHER =
        pcrecpp::RE("^((?:(?:[^?+*{}()[\\]\\\\|]+|\\\\.|\\[(?:\\^?\\\\.|\\^[^\\\\]|[^\\\\^])"
                    "(?:[^\\]\\\\]+|\\\\.)*\\]|\\((?:\\?[:=!]|\\?<[=!]|\\?>)?(?1)??\\)|\\(\\?"
                    "(?:R|[+-]?\\d+)\\))(?:(?:[?+*]|\\{\\d+(?:,\\d*)?\\})[?+]?)?|\\|)*)$");



PartialMatchRegex::PartialMatchRegex(const std::string &str)
{
    if (!isValidRegex(str)) {
        throw std::runtime_error(str + " is not valid Regex");
    }
    _basic = std::make_unique<pcrecpp::RE>(str);
    std::string extReStr;
    if (!str.empty()) {
        auto n = str.size();
        extReStr.reserve(((n / 2) + 3) * (n + 1));
        for (size_t i = 0; i < n - 1; i++) {
            pcrecpp::StringPiece sub(str.c_str(), int(i + 1));
            if (RE_MATCHER.FullMatch(sub)) {
                extReStr += "|(";
                extReStr += sub.as_string();
                extReStr += ")";
            }
        }
        extReStr += "|(";
        extReStr += str;
        extReStr += ")";
    }
    _extended = std::make_unique<pcrecpp::RE>(extReStr);
}


PartialMatchRegex::PartialMatchRegex(const PartialMatchRegex &other)
{
    if (other._basic) {
        _basic = std::make_unique<pcrecpp::RE>(*other._basic);
    }
    if (other._extended) {
        _extended = std::make_unique<pcrecpp::RE>(*other._extended);
    }
}
