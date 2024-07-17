# CMakeList.txt: test 的 CMake 项目，在此处包括源代码并定义
# 项目特定的逻辑。
#
cmake_minimum_required (VERSION 3.8)
set(CMAKE_CXX_STANDARD 17)
project (LetsTalk)

add_subdirectory(modules)

include_directories(.)

# 将源代码添加到此项目的可执行文件。
aux_source_directory(net NET_SOURCE_LIST)
aux_source_directory(chat CHAT_SOURCE_LIST)
aux_source_directory(connection CONNECTION_SOURCE_LIST)
add_executable (LetsTalk "main.cpp" ${NET_SOURCE_LIST} ${CHAT_SOURCE_LIST} ${CONNECTION_SOURCE_LIST})
link_directories(LetsTalk ws2_32 jsoncpp)


set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
set(CMAKE_PDB_OUTPUT_DIRECTORY     "${CMAKE_BINARY_DIR}/bin")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")