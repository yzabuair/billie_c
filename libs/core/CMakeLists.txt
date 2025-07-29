add_library(
    core
    STATIC
        include/core/ErrorHelpers.h
        sources/ErrorHelpers.cpp
)

target_include_directories(
    core
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/include
)

target_compile_features(
    core
        PUBLIC
        cxx_std_23
)
