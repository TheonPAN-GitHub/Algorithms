CMAKE_MINIMUM_REQUIRED(VERSION 3.25)

PROJECT(searching C)

set(CMAKE_C_STANDARD 17)

add_executable(LinearSearching LinearSearching.c)
add_executable(SentinelLinearSearch SentinelLinearSearch.c)
add_executable(IterativeBinarySearch IterativeBinarySearch.c)
add_executable(RecursiveBinarySearch RecursiveBinarySearch.c)
add_executable(MetaBinarySearch MetaBinarySearch.c)