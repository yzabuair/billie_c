// Copyright 2025, Yasser Zabuair.  See LICENSE for detials.

#include "RuntimeConfig.h"

#include "Errors.h"
#include "RuntimeError.h"

#include <codegen/AssemblyGenerator.h>
#include <codegen/AstPrinter.h>
#include <core/ErrorHelpers.h>
#include <scanner/TokenScanner.h>
#include <parser/LanguageParser.h>

#include <cstring>
#include <expected>
#include <fstream>
#include <iostream>
#include <string>

void print_banner() {
    std::cout << "Copyright 2025 Yasser Zabuair.  See LICENSE for details.\n";
    std::cout << "billie-c, an incomplete c compiler.\n\n";
}

void print_help() {
    std::cout << "billie <options> file_name\n";
    std::cout << "--help   This screen\n";
    std::cout << "--lex  Run lexer phase.\n";
    std::cout << "--parse  Run parse phase.\n";
    std::cout << "--codegen  Run codegen phase.\n";
}

std::string read_file(const std::string filename) {
    std::fstream file_stream{filename};
    std::string source_file;
    std::string line;
    while(std::getline(file_stream, line, '\0')) {
        source_file += line;
    }
    
    return source_file;
}

void run_lexer(const billiec::RuntimeConfig& cfg) {
    auto file_source = read_file(cfg.input_file);
    billiec::scanner::TokenScanner scanner{file_source};
    
    auto tokens = scanner.get_tokens();
    
    for(const auto& curr_token: tokens) {
        std::cout << curr_token;
    }
}

void run_parser(const billiec::RuntimeConfig& cfg) {
    auto file_source = read_file(cfg.input_file);
    
    billiec::scanner::TokenScanner scanner{file_source};
    auto tokens = scanner.get_tokens();
    
    billiec::parser::LanguageParser parser{tokens};
    auto program_node = parser.parse_program();
    billiec::codegen::AstPrinter ast_printer{std::move(program_node)};
    ast_printer.print_ast();
}

void run_codegen(const billiec::RuntimeConfig& cfg) {
    auto file_source = read_file(cfg.input_file);
    
    billiec::scanner::TokenScanner scanner{file_source};
    auto tokens = scanner.get_tokens();
    
    billiec::parser::LanguageParser parser{tokens};
    auto program_node = parser.parse_program();
    
    auto assembly_generator = billiec::codegen::AssemblyGenerator{std::move(program_node)};
    auto program_assembler_node = assembly_generator.generate_assembler();
    
    if (!cfg.output_file.empty()) {
        std::ofstream stream{cfg.output_file};
        program_assembler_node->generate(stream);
        
        stream.flush();
        stream.close();
    } else {
        program_assembler_node->generate(std::cout);
    }
}

billiec::RuntimeConfig process_command_line(int argc, char* argv[]) {
    billiec::RuntimeConfig config;
    
    for(int i = 1; i < argc; ++i) {
        if (std::strcmp(argv[i], "--help") == 0) {
            print_help();
        } else if (std::strcmp(argv[i], "--lex") == 0) {
            config.run_stage = billiec::RunStage::stage_lexer;
        } else if (std::strcmp(argv[i], "--parse") == 0) {
            config.run_stage = billiec::RunStage::stage_parser;
        } else if (std::strcmp(argv[i], "--codegen") == 0) {
            config.run_stage = billiec::RunStage::stage_code_gen;
        } else if (std::strcmp(argv[i], "--output") == 0) {
            if (i+1 >= argc) {
                auto ec =  billiec::ErrorCode{billiec::make_error_code(billiec::errc::output_file_missing),
                                              "You specified --output but no file was given."};
                throw billiec::RuntimeError(std::move(ec));
            }
            config.output_file = argv[i+1];
        } else if (std::strncmp(argv[i], "--", 2) == 0) {
            billiec::ErrorCode ec{billiec::make_error_code(billiec::errc::unknown_cmdline_option),
                                  "Unknown option: "};
            ec << argv[i];
            
            throw billiec::RuntimeError(std::move(ec)); 
        } else {
            config.input_file = argv[i];
        }
    }
    
    return config;
}

void validate_config(const billiec::RuntimeConfig& cfg) {
    if (cfg.input_file.empty()) {
        throw billiec::RuntimeError{billiec::ErrorCode{billiec::make_error_code(billiec::errc::file_not_specified),
                                    "No file was specified."}};
    }
    
    return billiec::ErrorCode{};
}


int main(int argc, char* argv[]) {
    print_banner();
    
    try {
        auto cfg = process_command_line(argc, argv);
        validate_config(cfg);
        
        if (cfg.run_stage == billiec::RunStage::stage_lexer) {
            run_lexer(cfg);
        } else if (cfg.run_stage == billiec::RunStage::stage_parser) {
            run_parser(cfg);
        } else if (cfg.run_stage == billiec::RunStage::stage_code_gen) {
            run_codegen(cfg);
        }
    } catch (const std::exception& exc) {
        std::cout << "Caught: " << exc.what() << "\n";
        return 44;
    }
    
    return 0;
}
