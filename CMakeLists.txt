

add_library(String
        first/String.hh
        first/String.cc
        )

add_executable(StringTest
        first/StringTest.cc
        )

target_link_libraries(StringTest String)