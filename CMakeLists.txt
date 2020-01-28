cmake_minimum_required(VERSION 3.15)
project(BIUAdvanedProg1-MS-2)

set(CMAKE_CXX_STANDARD 14)

add_executable(BIUAdvanedProg1-MS-2 Server.cpp Server.h main.cpp CacheManager.h Solver.h
        ClientHandler.h ClientHandler.cpp Searchable.h
        Matrix.h State.h StringBuilder.h StateValueContainer.h
        Searcher.h
        SearchOnMatrixExperiment.cpp SearchOnMatrixExperiment.h
        MyPriorityQueue.h BFS.h BestFS.h AStar.h DFS.h)
find_package(Threads REQUIRED)

target_link_libraries(BIUAdvanedProg1-MS-2 ${CMAKE_THREAD_LIBS_INIT})