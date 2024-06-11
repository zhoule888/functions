

include_directories(${ONNXRuntime_INCLUDE_DIRS})

include_directories(cpp)
add_executable(facefusion cpp/facefusion_main.cpp cpp/faceswap.cpp cpp/facerecognizer.cpp cpp/faceenhancer.cpp
                            cpp/face68landmarks.cpp cpp/yolov8face.cpp cpp/utils.cpp)
target_link_libraries(facefusion ${OpenCV_LIBS} ${ONNXRuntime_LIBRARIES})


