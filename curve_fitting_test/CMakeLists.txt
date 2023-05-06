cmake_minimum_required(VERSION 3.0)

project(curve)

add_compile_options("-std=c++11")

find_package(OpenCV 3 REQUIRED)
add_executable(curve_fitting_test curve_fitting_test.cc)

target_link_libraries(curve_fitting_test ${OpenCV_LIBS})