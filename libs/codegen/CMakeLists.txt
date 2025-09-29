#add_library(
#    codegen 
#    STATIC
#        include/codegen/AssemblerAst.h
#        include/codegen/AssemblyGenerator.h
#        include/codegen/AstPrinter.h
#        include/codegen/TackyAst.h
#        include/codegen/TackyGenerator.h
#        sources/AssemblyGenerator.cpp
#        sources/AstPrinter.cpp
#        sources/TackyAst.cpp
#        sources/TackyGenerator.cpp
#)

add_library(
    codegen 
    STATIC
        include/codegen/AssemblerAst.h
        include/codegen/AssemblyGenerator.h
        include/codegen/AssemblerPassEmit.h
        include/codegen/AssemblerPassFixInstructions.h
        include/codegen/AssemblerPassPseudoRegister.h
        include/codegen/AstPrinter.h
        include/codegen/TackyAst.h
        include/codegen/TackyGenerator.h
        sources/AssemblyGenerator.cpp
        sources/AssemblerPassEmit.cpp
        sources/AssemblerPassFixInstructions.cpp
        sources/AssemblerPassPseudoRegister.cpp
        sources/AstPrinter.cpp
        sources/TackyAst.cpp
        sources/TackyGenerator.cpp
)

target_include_directories(
    codegen 
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/include
)

target_link_libraries(
    codegen 
        PRIVATE
        core
        parser
        scanner
)

target_compile_features(
    codegen 
        PUBLIC
        cxx_std_23
)
