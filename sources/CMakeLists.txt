add_executable(
    billie
        Errors.cpp
        Errors.h
        main.cpp
        RuntimeConfig.h
        RuntimeError.h
)

target_link_libraries(
    billie
        PRIVATE
        codegen
        core
        parser
        scanner
)

target_compile_features(
    billie
        PUBLIC
        cxx_std_23
)
