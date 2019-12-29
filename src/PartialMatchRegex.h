// Copyright 2019 Igor Turovskiy
// Copyright 2019 Sviatoslav Dmitriev
// Distributed under the Boost Software License, Version 1.0.
// See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt

#ifndef PARTIALMATCHREGEX_PARTIALMATCHREGEX_H
#define PARTIALMATCHREGEX_PARTIALMATCHREGEX_H

#include <pcrecpp.h>
#include <memory>
#include <string>

/*!
 * @class PartialMatchRegex
 * @brief Wrapper class for pcrecpp::RE that allows to detect prefix of regex
 * @note Perl syntax for regex.
 * @note Does not support symbol classes like '[:digit:]', use '\d' instead
 */
class PartialMatchRegex {
private:
    static const pcrecpp::RE RE_MATCHER;    ///< Regular expression that can match regular expressions

private:
    std::unique_ptr<pcrecpp::RE> _basic    = nullptr;  ///< basic regex
    std::unique_ptr<pcrecpp::RE> _extended = nullptr;  ///< extended regex

public:

    /*! Constructs a PartialMatchRegex from a string str.
     * @param str string used as a source used to initialize the regex.
     * @throws std::runtime_error if the supplied regular expression is not valid.
     */
    explicit PartialMatchRegex(const std::string &str);


    //! Default destructor
    ~PartialMatchRegex() = default;


    //! Copy constructor
    PartialMatchRegex(const PartialMatchRegex &other);


    //! Default move constructor
    PartialMatchRegex(PartialMatchRegex &&) noexcept = default;


    //! Delete copy assignment operator
    PartialMatchRegex & operator= (const PartialMatchRegex &) = delete;


    //! Default move assignment operator
    PartialMatchRegex & operator= (PartialMatchRegex &&) noexcept = default;


    /*! Provides matching str with full regex
     *
     * @param str the target string
     * @return bool
     */
    bool fullMatch(const std::string &str) const
    { return _basic->FullMatch(str); }


    /*! Provides matching str with extended regex
     *
     * @param str the target string
     * @return bool
     */
    bool subMatch(const std::string &str) const
    { return _extended->FullMatch(str); }


    /*! Checks if str is valid regex
     *
     * @param str string
     * @return bool
     */
    static bool isValidRegex(const std::string &str)
    { return RE_MATCHER.FullMatch(str); }

};


#endif // PARTIALMATCHREGEX_PARTIALMATCHREGEX_H
