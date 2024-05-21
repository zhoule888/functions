cmake_minimum_required(VERSION 3.23)
project(Functions)

set(CMAKE_CXX_STANDARD 17)

set(OpenCV_DIR ${PROJECT_SOURCE_DIR}/3rd/opencv490/lib/cmake/opencv4)
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})
message(STATUS ${OpenCV_INCLUDE_DIRS})

find_package(Eigen3)
include_directories(${EIGEN3_INCLUDE_DIR})

add_executable(handdata_convert handdata_convert.cpp)
target_link_libraries(handdata_convert ${OpenCV_LIBS} ${EIGEN3_LIBS})

add_executable(socket_test socket_test.cpp)
add_executable(thread_test std_thread_test.cpp)
target_link_libraries(thread_test pthread)

add_executable(QRCodeDetector_test QRCodeDetector_test.cpp)
target_link_libraries(QRCodeDetector_test ${OpenCV_LIBS} ${EIGEN3_LIBS}  /usr/local/lib/libzxing.a)