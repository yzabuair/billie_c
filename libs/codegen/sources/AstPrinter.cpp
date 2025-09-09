// Copyright 2025 Yasser Zabuair.  See LICENSE for details.
#include <codegen/AstPrinter.h>

#include <scanner/Token.h>

#include <iostream>
#include <sstream>

namespace billiec::codegen {

AstPrinter::AstPrinter(std::unique_ptr<parser::ProgramNode> program_node):
    program_node_{std::move(program_node)} {
    
}

void AstPrinter::print_ast() {
    std::cout <<  parser::accept(*this, *program_node_);
}

std::string AstPrinter::visit(const parser::ProgramNode& node) {
    std::stringstream stream;
    
    stream << "Program{\n";
    
    stream << parser::accept(*this, node.function_node);
    
    stream << "}\n";
    
    return stream.str();
}

std::string AstPrinter::visit(const parser::FunctionNode& node) {
    std::stringstream stream;
    
    stream << "\t" << std::get<std::string>(node.name.token_value) << "{\n";
    
    for(const auto& curr_node: node.body) {
        stream << "\t\t" << accept(*this, curr_node);
    }
    
    stream << "\t" << "}\n";
    
    return stream.str();
}

std::string AstPrinter::visit(const parser::ReturnNode& node) {
    std::stringstream stream;
    
    stream << node.token.lexeme;
    
    stream << " " << accept(*this, node.return_expr);
    
    stream << "\n";
    
    return stream.str();
}

std::string AstPrinter::visit(const parser::UnaryNode& node) {
    std::stringstream stream;
    
    stream << node.operation.lexeme << accept(*this, node.expr);
    
    return stream.str();
}

std::string AstPrinter::visit(const parser::LiteralNode& node) {
    std::stringstream stream;
    
    using billiec::scanner::operator<<;
    stream << node.value;
    
    return stream.str();
}

} // namespace billiec::codegen
