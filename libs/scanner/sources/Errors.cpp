// Copyright 2025, Yasser Zabuair.  See LICENSE for details.
#include <scanner/Errors.h>

namespace billiec::scanner {

/** @brief  The \c std:error_category for the scanner module.. */
struct ErrorCategory: public std::error_category
{
    ErrorCategory(){ }
    ~ErrorCategory(){ }

    virtual const char* name() const noexcept
    {
        return "billiec.scanner.ErrorCategory";
    }

    virtual std::string message(int err) const
    {
        auto ec = static_cast<errc>(err);
        switch(ec)
        {
            case errc::scanner_err_none:
                return "scanner_err_none";
            case errc::scanner_err_invalid_token:
                return "scanner_err_invalid_token";
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

} // namespace billiec::scanner
