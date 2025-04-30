cmake_minimum_required(VERSION 3.23)
project(Functions)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/output/lib/${CMAKE_SYSTEM_PROCESSOR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/output/bin/${CMAKE_SYSTEM_PROCESSOR})
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/output/lib/${CMAKE_SYSTEM_PROCESSOR})

if (MSVC)
    set(OpenCV_DIR D:/projects/carina_win/thirdparty/opencv/windows_x64/build)
endif()
find_package(OpenCV REQUIRED)
if(OpenCV_FOUND)
    message(STATUS "OpenCV version: "${OpenCV_VERSION})
endif ()
include_directories(${OpenCV_INCLUDE_DIRS})




#set(ONNXRuntime_DIR /usr/local/lib)
#find_package(ONNXRuntime)
if (${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    set(ONNXRuntime_INCLUDE_DIRS /usr/local/include/onnxruntime/core/session)
    set(ONNXRuntime_LIBRARIES /usr/local/lib/libonnxruntime.so)

    find_package(Eigen3)
    include_directories(${EIGEN3_INCLUDE_DIR})
else (${CMAKE_SYSTEM_NAME} MATCHES "Windows")
    set(ONNXRuntime_INCLUDE_DIRS
            ${PROJECT_SOURCE_DIR}/3rd/onnxruntime-win-x64-gpu-1.21.0/include)
    set(ONNXRuntime_LIBRARIES
            ${PROJECT_SOURCE_DIR}/3rd/onnxruntime-win-x64-gpu-1.21.0/lib/onnxruntime_providers_cuda.lib
            ${PROJECT_SOURCE_DIR}/3rd/onnxruntime-win-x64-gpu-1.21.0/lib/onnxruntime.lib
            ${PROJECT_SOURCE_DIR}/3rd/onnxruntime-win-x64-gpu-1.21.0/lib/onnxruntime_providers_shared.lib
            ${PROJECT_SOURCE_DIR}/3rd/onnxruntime-win-x64-gpu-1.21.0/lib/onnxruntime_providers_tensorrt.lib)

    set(Eigen3_DIR ${PROJECT_SOURCE_DIR}/3rd/eigen3)
    include_directories(${EIGEN3_INCLUDE_DIR})
endif()

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
add_subdirectory(fmt)
