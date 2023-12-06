cmake_minimum_required(VERSION 3.10)
PROJECT(TEAP_logger)

SET(SOURCE_FILES main.cc)

find_package(PkgConfig REQUIRED)
pkg_check_modules(JSONCPP jsoncpp)
include_directories(${JSONCPP_INCLUDE_DIRS})

add_executable(output.out ${SOURCE_FILES})

target_link_libraries(output.out ${JSONCPP_LIBRARIES})
set_property(TARGET output.out PROPERTY CXX_STANDARD 17)
