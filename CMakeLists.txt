cmake_minimum_required(VERSION 3.15)
project(BIUAdvanedProg1-MS-2)

set(CMAKE_CXX_STANDARD 14)

add_executable(BIUAdvanedProg1-MS-2 Server.cpp Server.h main.cpp CacheManager.cpp CacheManager.h Solver.cpp Solver.h)
find_package (Threads REQUIRED)

target_link_libraries(BIUAdvanedProg1-MS-2 ${CMAKE_THREAD_LIBS_INIT})