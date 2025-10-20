// Copyright 2025 Yasser Zabuair.  See LICENSE for details.
#pragma once

#include <codegen/AssemblerAst.h>

#include <vector>

namespace billiec::codegen {

struct AssemblerPassFixInstructions {
    std::vector<AssemblerNode::PtrType> instructions;
    int stack_size{0};
    FunctionAssemblerNode* curr_func{nullptr};
    
public:
    AssemblerPassFixInstructions(std::vector<AssemblerNode::PtrType> instructions,
                                 int stack_size):
        instructions{std::move(instructions)},
        stack_size{stack_size} {
    }
    
    void process();
    
private:
    void process_node_(AssemblerNode::PtrType& curr_node);
    void visit_node_(CompoundAssemblerNode& node);
    void visit_node_(ProgramAssemblerNode& node);
    void visit_node_(FunctionAssemblerNode& node);
    bool check_ret_node_(std::vector<AssemblerNode::PtrType>& instructions,
                         std::vector<AssemblerNode::PtrType>::iterator itr);
    void visit_node_(MovInstructionNode* node);
    
};

} // namespace billiec::codegen
