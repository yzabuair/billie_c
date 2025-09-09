// Copyright 2025 Yasser Zabuair.  See LICENSE for details.
#pragma once

#include <codegen/TackyAst.h>
#include <parser/Ast.h>

#include <map>
#include <vector>

namespace billiec::codegen {

class TackyGenerator: public parser::AstNodeVisitor<TackyNode::PtrType> {
    parser::AstNode::PtrType program_node_;
    
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
        
    }
    
    TackyNode::PtrType visit(const parser::LiteralNode& node) override {
        return IntConstTackyNode::create(std::get<int>(node.value));
    }
};

} // namespace billiec::codegen
