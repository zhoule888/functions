

include_directories(${ONNXRuntime_INCLUDE_DIRS})

add_executable(gaze_estimation gaze_estimation.cpp)
target_link_libraries(gaze_estimation ${OpenCV_LIBS} ${ONNXRuntime_LIBRARIES})


