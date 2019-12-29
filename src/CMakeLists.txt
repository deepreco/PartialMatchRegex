# Copyright 2019 Igor Turovskiy
# Copyright 2019 Sviatoslav Dmitriev
# Distributed under the Boost Software License, Version 1.0.
# See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt

add_library(PartialMatchRegex PartialMatchRegex.h PartialMatchRegex.cpp)
target_link_libraries(PartialMatchRegex pcrecpp)

add_executable(PartialMatchRegexTest PartialMatchRegexTest.cpp PartialMatchRegex.h PartialMatchRegex.cpp)
target_link_libraries(PartialMatchRegexTest pcrecpp)
add_test(PartialMatchRegexTest PartialMatchRegexTest)