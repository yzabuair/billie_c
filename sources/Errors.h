// Copyright 2025, Yasser Zabuair.  See LICENSE for details.
#pragma once
#include <system_error>

namespace billiec {

enum class errc {
    no_error = 0x00,
    file_not_specified,
    output_file_missing,
    unknown_cmdline_option
};

std::error_code make_error_code(errc err);
const std::error_category& get_error_category();
} // namespace billiec
