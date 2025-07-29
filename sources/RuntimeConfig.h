// Copyright 2025, Yasser Zabuair.
#pragma once

#include <string>

namespace billiec {

enum class RunStage {
    stage_lexer,
    stage_parser,
    stage_code_gen,
    stage_all
};

struct RuntimeConfig {
    RunStage    run_stage = RunStage::stage_all;
    std::string input_file;
    std::string output_file;
};

} // namespace billiec

