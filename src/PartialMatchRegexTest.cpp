// Copyright 2019 Igor Turovskiy
// Copyright 2019 Sviatoslav Dmitriev
// Distributed under the Boost Software License, Version 1.0.
// See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt

#define CATCH_CONFIG_MAIN
#include <catch.hpp>

#include "PartialMatchRegex.h"


TEST_CASE("PartialMatchRegex")
{
    const std::string r1("aab*");
    const std::string r2("a|b|c");
    const std::string r3("J.* B.*");
    const std::string r4("\\+?[\\d]+");
    const std::string r5("(\\+|-)?[\\d]+");
    const std::string r6("((\\+|-)?[\\d]+)(\\.(([\\d]+)?))?");
    const std::string r7("((\\+|-)?[\\d]+)(\\.(([\\d]+)?))?((e|E)((\\+|-)?)[\\d]+)?");
    const std::string r8("[^a]{0,3}");
    const std::string r9("a");


    SECTION("Constructor throws")
    {
        REQUIRE(!PartialMatchRegex::isValidRegex("(aza"));
        REQUIRE_THROWS(PartialMatchRegex("(aza"));
        REQUIRE(!PartialMatchRegex::isValidRegex("[a-z."));
        REQUIRE_THROWS(PartialMatchRegex("[a-z."));
    }


    SECTION("Constructor no throws")
    {
        REQUIRE_NOTHROW(PartialMatchRegex(r1));
        REQUIRE_NOTHROW(PartialMatchRegex(r2));
        REQUIRE_NOTHROW(PartialMatchRegex(r3));
        REQUIRE_NOTHROW(PartialMatchRegex(r4));
        REQUIRE_NOTHROW(PartialMatchRegex(r5));
        REQUIRE_NOTHROW(PartialMatchRegex(r6));
        REQUIRE_NOTHROW(PartialMatchRegex(r7));
        REQUIRE_NOTHROW(PartialMatchRegex(r8));
        REQUIRE_NOTHROW(PartialMatchRegex(r9));
        REQUIRE_NOTHROW(PartialMatchRegex(""));
    }


    SECTION("Constructor move")
    {
        PartialMatchRegex re1(r1);
        REQUIRE_NOTHROW(PartialMatchRegex(std::move(re1)));
        PartialMatchRegex re2(r2);
        PartialMatchRegex re4 = std::move(re2);
        REQUIRE_NOTHROW(PartialMatchRegex(re4));
    }


    SECTION("Handy matching")
    {
        PartialMatchRegex re1(r1);
        REQUIRE(re1.fullMatch("aabbbb"));
        REQUIRE(re1.fullMatch("aab"));
        REQUIRE(re1.fullMatch("aa"));
        REQUIRE(re1.subMatch("aabbbb"));
        REQUIRE(re1.subMatch("aab"));
        REQUIRE(re1.subMatch("aa"));
        REQUIRE(re1.subMatch("a"));
        REQUIRE(!re1.subMatch("ac"));
        REQUIRE(!re1.subMatch("c"));

        PartialMatchRegex re2(r2);
        REQUIRE(re2.subMatch("a"));
        REQUIRE(re2.subMatch("b"));
        REQUIRE(re2.subMatch("c"));
        REQUIRE(re2.subMatch("a"));
        REQUIRE(re2.subMatch("b"));
        REQUIRE(re2.subMatch("c"));
        REQUIRE(re2.fullMatch("a"));
        REQUIRE(re2.fullMatch("b"));
        REQUIRE(re2.fullMatch("c"));
        REQUIRE(re2.fullMatch("a"));
        REQUIRE(re2.fullMatch("b"));
        REQUIRE(re2.fullMatch("c"));
        REQUIRE(!re2.subMatch("d"));
        REQUIRE(!re2.fullMatch("d"));

        PartialMatchRegex re3(r3);
        REQUIRE(re3.fullMatch("J B"));
        REQUIRE(re3.fullMatch("John B"));
        REQUIRE(re3.fullMatch("Johny Black"));
        REQUIRE(re3.subMatch("J"));
        REQUIRE(re3.subMatch("Johny"));
        REQUIRE(re3.subMatch("John "));
        REQUIRE(re3.subMatch("J B"));
        REQUIRE(re3.subMatch("John B"));
        REQUIRE(re3.subMatch("Johny Black"));

        PartialMatchRegex re4("");
        REQUIRE(re4.fullMatch(""));

        PartialMatchRegex re5(r5);
        REQUIRE(re5.fullMatch("+123"));
        REQUIRE(re5.fullMatch("123"));
        REQUIRE(re5.fullMatch("-123"));
    }
}
