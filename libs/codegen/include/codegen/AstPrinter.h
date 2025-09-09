// Copyright 2025 Yasser Zabuair.  See LICENSE for details.
#pragma once

#include <parser/Ast.h>

#include <memory>
#include <string>
namespace billiec::codegen {

/** @brief  Iterates over the nodes and prints out their data to verify the tree genereated. */
class AstPrinter: public parser::AstNodeVisitor<std::string> {
private:
    std::unique_ptr<parser::ProgramNode> program_node_;
    
public:
    AstPrinter(std::unique_ptr<parser::ProgramNode> program_node);
    
    void print_ast();
    
    std::string visit(const parser::ProgramNode& node) override;
    std::string visit(const parser::FunctionNode& node) override;
    std::string visit(const parser::ReturnNode& node) override;
    std::string visit(const parser::UnaryNode& node) override;
    std::string visit(const parser::LiteralNode& node) override;
    
};

} // namespace billiec::codegen
