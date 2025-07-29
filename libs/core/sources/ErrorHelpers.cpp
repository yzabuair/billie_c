// Copyright 2025, Yasser Zabuair.  See LICENSE for details.
#include <core/ErrorHelpers.h>

namespace billiec {

std::ostream& operator<<(std::ostream& stream, const billiec::ErrorCode& ec) {
    stream << " error_code: "    << ec.ec_.message()    << "\n";
    stream << " message:    ";
    if (!ec.messages_.empty() ) {
        for(const auto& curr_message: ec.messages_) {
            stream << curr_message << " ";
        }
    }
    stream << "\n";
    stream << " file: "  << ec.caller_location_.file_name()   << "\n";
    stream << " line: "  << ec.caller_location_.line()        << "\n";

    return stream;
}

} // namespace billiec
