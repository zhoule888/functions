cmake_minimum_required(VERSION 3.16)
project(Apriltag)

#set(CMAKE_BUILD_TYPE "Release")

# C++14
set(CMAKE_CXX_STANDARD 14)

find_package(OpenCV 4)
find_package(Eigen3)

set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

include_directories(
    ${PROJECT_SOURCE_DIR}
    ${PROJECT_SOURCE_DIR}/include
)

add_library(ApriTag SHARED
    ${PROJECT_SOURCE_DIR}/src/Edge.cpp
    ${PROJECT_SOURCE_DIR}/src/FloatImage.cpp
    ${PROJECT_SOURCE_DIR}/src/Gaussian.cpp
    ${PROJECT_SOURCE_DIR}/src/GLine2D.cpp
    ${PROJECT_SOURCE_DIR}/src/GLineSegment2D.cpp
    ${PROJECT_SOURCE_DIR}/src/GrayModel.cpp
    ${PROJECT_SOURCE_DIR}/src/Homography33.cpp
    ${PROJECT_SOURCE_DIR}/src/MathUtil.cpp
    ${PROJECT_SOURCE_DIR}/src/Quad.cpp
    ${PROJECT_SOURCE_DIR}/src/Segment.cpp
    ${PROJECT_SOURCE_DIR}/src/TagDetection.cpp
    ${PROJECT_SOURCE_DIR}/src/TagDetector.cpp
    ${PROJECT_SOURCE_DIR}/src/TagFamily.cpp
    ${PROJECT_SOURCE_DIR}/src/UnionFindSimple.cpp
)

target_link_libraries(ApriTag ${OpenCV_LIBS} )

add_executable(ApriTag_test apritag_test.cpp)
target_link_libraries(ApriTag_test ${OpenCV_LIBS}
        ApriTag)
