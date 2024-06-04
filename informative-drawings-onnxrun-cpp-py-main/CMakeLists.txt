

include_directories(${ONNXRuntime_INCLUDE_DIRS})

add_executable(informative-draw drawing.cpp)
target_link_libraries(informative-draw ${OpenCV_LIBS} ${ONNXRuntime_LIBRARIES})


