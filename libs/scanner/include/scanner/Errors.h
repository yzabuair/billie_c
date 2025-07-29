// Copyright 2025 Yasser Zabuair.  See LICENSE for details.
#pragma once
#include <system_error>

namespace billiec::scanner {

enum class errc {
    scanner_err_none = 0x00,
    scanner_err_invalid_token
};

std::error_code make_error_code(errc err);
const std::error_category& get_error_category();
} // namespace billiec::scanner
