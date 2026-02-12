cmake_minimum_required(VERSION 4.1)
project(opencv_demo)

set(CMAKE_CXX_STANDARD 20)

find_package(OpenCV REQUIRED)

file(COPY data DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

add_subdirectory(third_party/opencv_contrib)

add_executable(opencv_demo main.cpp)
target_link_libraries(opencv_demo ${OpenCV_LIBS})
target_link_libraries(opencv_demo aruco)


