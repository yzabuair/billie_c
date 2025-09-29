// Copyright 2025 Yasser Zabuair.  See LICENSE for details.
#pragma once

#include <codegen/TackyAst.h>
#include <parser/Ast.h>

#include <map>
#include <sstream>
#include <string>
#include <vector>

namespace billiec::codegen {

class TackyGenerator: public parser::AstNodeVisitor<TackyNode::PtrType> {
    parser::AstNode::PtrType program_node_;
    int curr_tmp_num_{0};
    
public:
    TackyGenerator(parser::AstNode::PtrType program_node):
        program_node_{std::move(program_node)} {
    }
    
    TackyNode::PtrType generate_tacky() {
        return parser::accept(*this, program_node_);
    }
    
    TackyNode::PtrType visit(const parser::ProgramNode& node) override {
        return ProgramTackyNode::create(parser::accept(*this, node.function_node));
    }
    
    TackyNode::PtrType visit(const parser::FunctionNode& node) override {
        std::vector<TackyNode::PtrType> instructions;
        for(const auto& curr_node: node.body) {
            instructions.push_back(parser::accept(*this, curr_node));
        }
        
        return FunctionTackyNode::create(node.name, std::move(instructions));
    }
    
    TackyNode::PtrType visit(const parser::ReturnNode& node) override {
        return ReturnTackyNode::create(parser::accept(*this, node.return_expr));
    }
    
    TackyNode::PtrType visit(const parser::UnaryNode& node) override {
        using namespace std::string_literals;
        std::vector<TackyNode::PtrType> instructions;
        
        auto src = parser::accept(*this, node.expr);
        auto dst_name = generate_temp_name_();
        auto dst = VarTackyNode::create(dst_name);
        return UnaryTackyNode::create(node.operation, std::move(src), std::move(dst));
    }
    
    TackyNode::PtrType visit(const parser::LiteralNode& node) override {
        return IntConstTackyNode::create(std::get<int>(node.value));
    }
    
private:
    
    std::string generate_temp_name_() {
        std::stringstream stream;
        
        stream << "tmp." << curr_tmp_num_++;
        
        return stream.str();
    }
};

} // namespace billiec::codegen
