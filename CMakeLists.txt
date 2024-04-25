cmake_minimum_required(VERSION 3.23)
project(Functions)

set(CMAKE_CXX_STANDARD 17)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

find_package(Eigen3)
include_directories(${EIGEN3_INCLUDE_DIR})

add_executable(handdata_convert handdata_convert.cpp)
target_link_libraries(handdata_convert ${OpenCV_LIBS} ${EIGEN3_LIBS})

add_executable(socket_test socket_test.cpp)
