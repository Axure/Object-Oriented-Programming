CMAKE_MINIMUM_REQUIRED(VERSION 3.1)
variable_watch(CMAKE_BUILD_TYPE)
IF (CMAKE_BUILD_TYPE MATCHES "Debug")
    message("debug mode")

ELSE ()
    message("not debug mode")
ENDIF (CMAKE_BUILD_TYPE MATCHES "Debug")

add_library(String
        first/String.hh
        first/String.cc
        )

set_property(TARGET String PROPERTY CXX_STANDARD 11)

add_executable(StringTest
        first/StringTest.cc
        )
set_property(TARGET StringTest PROPERTY CXX_STANDARD 11)
target_link_libraries(StringTest String)

IF (CMAKE_BUILD_TYPE MATCHES "Debug")
    target_compile_definitions(String PRIVATE DEBUG___=1)
    message("debug mode")

ELSE ()
    message("not debug mode")
ENDIF (CMAKE_BUILD_TYPE MATCHES "Debug")