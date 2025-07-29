add_library(
    parser
    STATIC
        include/parser/Ast.h
        include/parser/Errors.h
        include/parser/LanguageParser.h
        include/parser/ParserError.h
        sources/Errors.cpp
        sources/LanguageParser.cpp
)

target_include_directories(
    parser
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/include
)

target_link_libraries(
    parser 
        PRIVATE
        core
        scanner
)

target_compile_features(
    parser
        PUBLIC
        cxx_std_23
)
