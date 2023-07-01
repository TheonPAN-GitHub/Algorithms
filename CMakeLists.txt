cmake_minimum_required(VERSION 3.25)
project(Algorithms C)

set(CMAKE_C_STANDARD 17)

add_subdirectory("${PROJECT_SOURCE_DIR}/sorting/BubbleSort" "${PROJECT_SOURCE_DIR}/sorting/BubbleSort/cmake-build-debug")
add_subdirectory("${PROJECT_SOURCE_DIR}/sorting/InsertionSort" "${PROJECT_SOURCE_DIR}/sorting/InsertionSort/cmake-build-debug")
add_subdirectory("${PROJECT_SOURCE_DIR}/sorting/SelectionSort" "${PROJECT_SOURCE_DIR}/sorting/SelectionSort/cmake-build-debug")