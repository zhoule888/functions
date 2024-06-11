

add_executable(QRCodeDetector_test QRCodeDetector_test.cpp)
target_link_libraries(QRCodeDetector_test ${OpenCV_LIBS} ${EIGEN3_LIBS}  /usr/local/lib/libzxing.a)



