// Copyright 2025 Yasser Zabuair.  See LICENSE for details.
#include <codegen/AstPrinter.h>

#include <scanner/Token.h>

#include <iostream>

namespace billiec::codegen {

AstPrinter::AstPrinter(std::unique_ptr<parser::AstNode> program_node):
program_node_{std::move(program_node)} {
    
}

void AstPrinter::print_ast() {
    program_node_->accept(*this);
}

void AstPrinter::visit(const parser::ProgramNode& node) {
    std::cout << "Program{\n";
    
    node.function_definition->accept(*this);
    
    std::cout << "}\n";

}

void AstPrinter::visit(const parser::FunctionNode& node) {
    std::cout << "\t" << std::get<std::string>(node.name.token_value) << "{\n";
    
    for(const auto& curr_node: node.body) {
        curr_node->accept(*this);
    }
    
    std::cout << "\t}\n";
}

void AstPrinter::visit(const parser::ReturnNode& node) {
    std::cout << "\t\t return ";
    
    node.return_expr->accept(*this);
    
    std::cout << "\n";
}

void AstPrinter::visit(const parser::LiteralNode& node) {
    using billiec::scanner::operator<<;
    std::cout << node.value;
}

} // namespace billiec::codegen
