cmake_minimum_required(VERSION 3.22.1)
# 设置编译器为gcc/g++
# SET(CMAKE_C_COMPILER /usr/bin/gcc)
# SET(CMAKE_CXX_COMPILER /usr/bin/g++)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(code_library)
# 设置必须跟上面的一样，即c++17
include_directories(${CMAKE_SOURCE_DIR}/src/)

# 设置生成 compile_commands

# 显示编译时间
set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE "${CMAKE_COMMAND} -E time")
set_property(GLOBAL PROPERTY RULE_LAUNCH_LINK "${CMAKE_COMMAND} -E time")

# 设置成debug模式
set(CMAKE_BUILD_TYPE "Debug")
# # 设置调试的指令
add_compile_options(-Wall -Wextra -Wshadow -Wpedantic) # fsanitize=undefined -fsanitize=address

# 加入本项目的头文件

add_executable(main main.cc)

# target_include_directories(main PUBLIC ${CMAKE_SOURCE_DIR}/src/)