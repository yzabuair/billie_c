// Copyright 2025, Yasser Zabuair.  See LICENSE for details.
#include "Errors.h"

namespace billiec {

/** @brief  The \c std:error_category for the main executable. */
struct ErrorCategory: public std::error_category
{
    ErrorCategory(){ }
    ~ErrorCategory(){ }

    virtual const char* name() const noexcept
    {
        return "billiec.ErrorCategory";
    }

    virtual std::string message(int err) const
    {
        auto ec = static_cast<errc>(err);
        switch(ec)
        {
            case errc::no_error:
                return "no_error";
            case errc::file_not_specified:
                return "file_not_specified";
            case errc::output_file_missing:
                return "output_file_missing";
            case errc::unknown_cmdline_option:
                return "unknown_cmdline_option";
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


} // namespace billiec
