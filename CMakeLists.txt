cmake_minimum_required(VERSION 3.10)

project(tetris)

add_executable(tetris "${PROJECT_SOURCE_DIR}/src/main.cpp")

include_directories(include)

add_library(block "${PROJECT_SOURCE_DIR}/src/block.cpp")
add_library(grid "${PROJECT_SOURCE_DIR}/src/grid.cpp")
add_library(grid_cell "${PROJECT_SOURCE_DIR}/src/grid_cell.cpp")


target_link_libraries(tetris PRIVATE block)
target_link_libraries(tetris PRIVATE grid_cell)
target_link_libraries(tetris PRIVATE grid)
target_link_libraries(grid PRIVATE grid_cell)


target_link_libraries(tetris PRIVATE "${PROJECT_SOURCE_DIR}/lib/libraylib.so")
target_link_libraries(grid PRIVATE "${PROJECT_SOURCE_DIR}/lib/libraylib.so")
target_link_libraries(block PRIVATE "${PROJECT_SOURCE_DIR}/lib/libraylib.so")
target_link_libraries(grid_cell PRIVATE "${PROJECT_SOURCE_DIR}/lib/libraylib.so")

target_include_directories(tetris PUBLIC
                          "${PROJECT_SOURCE_DIR}/include"
                          "${PROJECT_SOURCE_DIR}/lib"
                          )
