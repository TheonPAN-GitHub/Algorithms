cmake_minimum_required(VERSION 3.25)
project(Algorithms C)

set(CMAKE_C_STANDARD 17)

add_subdirectory("algorithms/sorting/BubbleSort" "algorithms/sorting/BubbleSort/cmake-build-debug")
add_subdirectory("algorithms/sorting/InsertionSort" "algorithms/sorting/InsertionSort/cmake-build-debug")
add_subdirectory("algorithms/sorting/SelectionSort" "algorithms/sorting/SelectionSort/cmake-build-debug")
add_subdirectory("algorithms/sorting/MergeSort" "algorithms/sorting/MergeSort/cmake-build-debug")
add_subdirectory("datastructures/Array/searching" "datastructures/Array/searching/cmake-build-debug")
add_subdirectory("algorithms/sorting/QuickSort" "algorithms/sorting/QuickSort/cmake-build-debug")
add_subdirectory("datastructures/LinkedList" "datastructures/LinkedList/cmake-build-debug")
add_subdirectory("datastructures/BinaryTree" "datastructures/BinaryTree/cmake-build-debug")
add_subdirectory("datastructures/BinarySearchTree" "datastructures/BinarySearchTree/cmake-build-debug")