cmake_minimum_required(VERSION 3.15)
project(BIUAdvanedProg1-MS-2)

set(CMAKE_CXX_STANDARD 14)

add_executable(BIUAdvanedProg1-MS-2 Server.cpp Server.h main.cpp CacheManager.cpp CacheManager.h Solver.cpp Solver.h
        ClientHandler.h ClientHandler.cpp Searchable.cpp Searchable.h
        Matrix.cpp Matrix.h StringBuilder.cpp State.h State.cpp StringBuilder.h StateValueContainer.cpp StateValueContainer.h
        Searcher.cpp Searcher.h
        SearchOnMatrixExperiment.cpp SearchOnMatrixExperiment.h)
find_package(Threads REQUIRED)

target_link_libraries(BIUAdvanedProg1-MS-2 ${CMAKE_THREAD_LIBS_INIT})