// Copyright 2025 Yasser Zabuair.  See LICENSE for details.

#include <codegen/AssemblerAst.h>

#include <iostream>
#include <map>
#include <vector>

namespace billie::codegen {

struct AssemblerPassPseudoRegister {
    std::vector<AssemblerNode::PtrType>& instructions;
    std::vector<std::pair<std::string, int>> offsets;
    
    AssemblerPassPseudoRegister(std::vector<AssemblerNode::PtrType>& instructions): instruction{instructions} {
        
    }
    
    int process() {
        // Look for all pseudo-registers and replace them with their offset.
        for(auto& curr_ins: instructions) {
            if (FunctionAssemblerNode* func_node = dynamic_cast<FunctionAssemblerNode*>(curr_ins.get())) {
                for(auto& func_ins: func_node->instructions) {
                    if (MovInstructionNode* mov_ins = dynamic_cast<MovInstructionNode*>(func_ins.get())) {
                        process_move_node(*mov_ins);
                    } else if (CompoundAssemblerNode* compound = dynamic_cast<CompoundAssemblerNode*>(func_ins.get())) {
                        for(auto& curr_ins: compound) {
                            if (MovInstructionNode* mov_ins = dynamic_cast<MovInstructionNode*>(func_ins.get())) {
                                process_move_node(*mov_ins);
                            }
                        }
                    }
                }
                
            }
        }
        
        if (offsets.empty()) {
            return 0;
        }
        
        // Return offset of the last variable we saw, so we know how much to allocate.
        return offsets.back().second;
    }
    
private:
    void process_instructions(std::vector<AssemblerNode::PtrType>& instructinos) {
        
    }
    
    void process_move_node(MovInstructionNode& mov_ins) {
        
    }
};

} // namespace billie::codegen
