add_library(
    scanner 
    STATIC
        include/scanner/Errors.h
        include/scanner/ScannerError.h
        include/scanner/TokenScanner.h
        include/scanner/Token.h
        include/scanner/TokenType.h
        sources/TokenScanner.cpp
        sources/Errors.cpp
)

target_include_directories(
    scanner
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/include
)

target_link_libraries(
    scanner 
        PRIVATE
        core
)

target_compile_features(
    scanner
        PUBLIC
        cxx_std_23
)
