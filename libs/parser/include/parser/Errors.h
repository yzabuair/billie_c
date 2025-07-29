// Copyright 2025 Yasser Zabuair.  See LICENSE for details.
#include <system_error>

namespace billiec::parser {

enum class errc {
    parser_no_error = 0x00,
    parser_unexpected_token
};

std::error_code make_error_code(errc err);
const std::error_category& get_error_category();

} // namespace billiec::parser
