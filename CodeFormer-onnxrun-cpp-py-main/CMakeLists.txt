

include_directories(${ONNXRuntime_INCLUDE_DIRS})

add_executable(CodeFormer codeformer.cpp)
target_link_libraries(CodeFormer ${OpenCV_LIBS} ${ONNXRuntime_LIBRARIES})


