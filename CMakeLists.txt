cmake_minimum_required(VERSION 3.10)

project(log_analyzer LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_library(log_analyzer_lib
    src/LogAnalyzer.cpp
)#创建一个实验库命名为log_analyzer_lib,再将src/LogAnalyzer.cpp添加入库

target_include_directories(log_analyzer_lib
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)#把src目录下的文件都加入到log_analyzer_lib这个库中供include使用

add_executable(log_analyzer
    src/main.cpp
)#可执行程序

target_link_libraries(log_analyzer
    PRIVATE
        log_analyzer_lib
)#将库和可执行程序连接

include(CTest)

if(BUILD_TESTING)
    find_package(GTest REQUIRED)

    add_executable(log_analyzer_tests
        tests/test_LogAnalyzer.cpp
    )

    target_link_libraries(log_analyzer_tests
        PRIVATE
            log_analyzer_lib
            GTest::gtest_main
    )

    include(GoogleTest)
    gtest_discover_tests(log_analyzer_tests)
endif()