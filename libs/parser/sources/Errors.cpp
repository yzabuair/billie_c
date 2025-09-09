// Copyright 2025 Yasser Zabuair.  See LICENSE for details.
#include <parser/Errors.h>

namespace billiec::parser {

/** @brief  The \c std:error_category for the parser module. */
struct ErrorCategory: public std::error_category
{
    ErrorCategory(){ }
    ~ErrorCategory(){ }

    virtual const char* name() const noexcept
    {
        return "billiec.parser.ErrorCategory";
    }

    virtual std::string message(int err) const
    {
        auto ec = static_cast<errc>(err);
        switch(ec)
        {
            case errc::parser_no_error:
                return "parser_no_error";
            case errc::parser_unexpected_token:
                return "parser_unexpected_token";
            case errc::parser_invalid_expression:
                return "parser_invalid_expression";
            default:
                return "Unknown Error";
        }
    }
};

static const ErrorCategory  g_Category;  ///< Global category, only one per module.

std::error_code make_error_code(errc err) {
    return std::error_code{static_cast<int>(err), g_Category};
}

const std::error_category& get_error_category() {
    return g_Category;
}

} // namespace billiec::parser
