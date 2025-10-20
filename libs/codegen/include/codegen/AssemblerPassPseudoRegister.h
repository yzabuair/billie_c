// Copyright 2025 Yasser Zabuair.  See LICENSE for details.

#include <codegen/AssemblerAst.h>

#include <iostream>
#include <map>
#include <vector>

namespace billiec::codegen {

struct AssemblerPassPseudoRegister {
    std::vector<AssemblerNode::PtrType> instructions;
    std::vector<std::pair<std::string, int>> offsets;
    
    AssemblerPassPseudoRegister(std::vector<AssemblerNode::PtrType> instructions): instructions{std::move(instructions)} {
    }
    
    int process();
    
private:
    void process_node_(AssemblerNode::PtrType& curr_node);
    void visit_node_(CompoundAssemblerNode& node);
    void visit_node_(ProgramAssemblerNode& node);
    void visit_node_(FunctionAssemblerNode& node);
    void visit_node_(MovInstructionNode& node);
    int get_offset_(const std::string& pseudo_register);
};

} // namespace billie::codegen
