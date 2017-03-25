cmake_minimum_required(VERSION 3.6)
project(ShelfyDetector)

set(CMAKE_CXX_STANDARD 11)

find_package(OpenCV REQUIRED)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin")

set(SOURCE_FILES main.cpp Detector.cpp Detector.h)
add_executable(ShelfyDetector ${SOURCE_FILES})
include_directories(${OpenCV_INCLUDE_DIRS})
target_link_libraries(ShelfyDetector ${OpenCV_LIBS})

