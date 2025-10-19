// Copyright 2025 Yasser Zabuair.  See LICENSE for details.
#pragma once

#include <codegen/AssemblerAst.h>

#include <iostream>
#include <vector>

namespace billiec::codegen {
struct AssemblerPassEmit {
    std::vector<AssemblerNode::PtrType>& instructions;
    std::ostream& ostream;
    
    AssemblerPassEmit(std::vector<AssemblerNode::PtrType>& instructions,
                      std::ostream& ostream):
        instructions{instructions},
        ostream{ostream} {
    }
    void process();
    
private:
    void process_node_(AssemblerNode::PtrType& curr_node);
    void visit_node_(CompoundAssemblerNode& node);
    void visit_node_(ProgramAssemblerNode& node);
    void visit_node_(FunctionAssemblerNode& node);
    void visit_node_(MovInstructionNode& node);
    void visit_node_(ReturnInstructionNode& node);
    void visit_node_(LiteralInstructionNode& node);
    void visit_node_(RegisterInstructionNode& node);
    void visit_node_(UnaryInstructionNode& node);
    void visit_node_(AllocateStack& node);
    void visit_node_(PseudoRegister& node);
};

} // namespace billiec::codegen
