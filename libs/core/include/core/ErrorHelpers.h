// Copyright 2025, Yasser Zabuair.  See LICENSE for details.
#pragma once


#include <ostream>
#include <sstream>
#include <string>
#include <source_location>
#include <system_error>
#include <vector>

namespace billiec {


/** @brief  More detailed error code that tells us where error occurred. */
struct ErrorCode {
    std::error_code             ec_;
    std::source_location        caller_location_;
    std::vector<std::string>    messages_;

    ErrorCode() {
        
    }
    
    ErrorCode(std::error_code ec,
              const std::string& details,
              std::source_location location = std::source_location::current()):
        ec_{std::move(ec)},
        caller_location_{std::move(location)} {
            messages_.push_back(details);
    }

    operator bool() const {
        return ec_.operator bool();
    }

    // Let's you put more details into the message.
    template <typename T>
    ErrorCode& operator<<(T&& parm) {
        std::stringstream stream;

        stream << std::forward<T>(parm);

        messages_.push_back(stream.str());

        return *this;
    }
              
};

std::ostream& operator<<(std::ostream& stream, const billiec::ErrorCode& ec);
} // namespace billiec
