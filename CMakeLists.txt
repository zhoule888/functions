cmake_minimum_required(VERSION 3.23)
project(Functions)

set(CMAKE_CXX_STANDARD 17)

set(OpenCV_DIR ${PROJECT_SOURCE_DIR}/3rd/opencv490/lib/cmake/opencv4)
find_package(OpenCV REQUIRED)
if(OpenCV_FOUND)
    message(STATUS "OpenCV version: "${OpenCV_VERSION})
endif ()
include_directories(${OpenCV_INCLUDE_DIRS})

find_package(Eigen3)
include_directories(${EIGEN3_INCLUDE_DIR})

#set(ONNXRuntime_DIR /usr/local/lib)
#find_package(ONNXRuntime)
set(ONNXRuntime_INCLUDE_DIRS /usr/local/include/onnxruntime/core/session)
set(ONNXRuntime_LIBRARIES /usr/local/lib/libonnxruntime.so)

message(STATUS "ONNXRuntime include: "${ONNXRuntime_INCLUDE_DIRS})
message(STATUS "ONNXRuntime_LIBRARIES: "${ONNXRuntime_LIBRARIES})


add_executable(handdata_convert handdata_convert.cpp)
target_link_libraries(handdata_convert ${OpenCV_LIBS} ${EIGEN3_LIBS})

add_executable(socket_test socket_test.cpp)
add_executable(thread_test std_thread_test.cpp)
target_link_libraries(thread_test pthread)


add_executable(circle_test circle_detect.cpp)
target_link_libraries(circle_test ${OpenCV_LIBS} ${EIGEN3_LIBS})

add_subdirectory(AprilTag)
add_subdirectory(wechat_qr_detect)
add_subdirectory(informative-drawings-onnxrun-cpp-py-main)
add_subdirectory(CodeFormer-onnxrun-cpp-py-main)
add_subdirectory(gaze-estimation-opencv-dnn-main)
add_subdirectory(facefusion)

