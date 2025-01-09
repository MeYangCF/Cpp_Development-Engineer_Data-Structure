cmake_minimum_required(VERSION 3.19)
get_filename_component(ProjectId ${CMAKE_CURRENT_SOURCE_DIR} NAME)
string(REPLACE " " "_" ProjectId ${ProjectId})
project(${ProjectId} CXX)

# 设定 C++11 标准
set(CMAKE_CXX_STANDARD 11)  # 将 C++ 标准设置为 C++11
set(CMAKE_CXX_STANDARD_REQUIRED ON)  # C++11 是强制要求，不会衰退至低版本

# 遍历项目根目录下所有的 .cpp 文件，自动添加
file(GLOB_RECURSE files *.cpp **/*.cpp)
foreach (file ${files})
    string(REGEX REPLACE ".+/(.+)\\..*" "\\1" exe ${file})
    # 将目标名限制为字母、数字和下划线
    string(REPLACE "/" "_" exe ${exe})
    add_executable(${exe} ${file})
endforeach ()