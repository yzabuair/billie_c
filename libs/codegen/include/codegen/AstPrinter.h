// Copyright 2025 Yasser Zabuair.  See LICENSE for details.
#pragma once

#include <parser/Ast.h>

#include <memory>
#include <string>
namespace billiec::codegen {

/** @brief  Iterates over the nodes and prints out their data to verify the tree genereated. */
class AstPrinter: parser::AstVisitor {
private:
    std::unique_ptr<parser::AstNode> program_node_;
    
public:
    AstPrinter(std::unique_ptr<parser::AstNode> program_node);
    
    void print_ast();
    
    void visit(const parser::ProgramNode& node) override;
    void visit(const parser::FunctionNode& node) override;
    void visit(const parser::ReturnNode& node) override;
    void visit(const parser::LiteralNode& node) override;
    
};

} // namespace billiec::codegen
