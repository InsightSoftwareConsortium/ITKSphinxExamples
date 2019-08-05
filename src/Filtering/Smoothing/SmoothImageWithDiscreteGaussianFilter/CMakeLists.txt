cmake_minimum_required(VERSION 3.10.2)

project(SmoothImageWithDiscreteGaussianFilter)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})


add_executable(SmoothImageWithDiscreteGaussianFilter Code.cxx)
target_link_libraries(SmoothImageWithDiscreteGaussianFilter ${ITK_LIBRARIES})

install(TARGETS SmoothImageWithDiscreteGaussianFilter
  DESTINATION bin/ITKExamples/Filtering/Smoothing
  COMPONENT Runtime
  )

install(FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKExamples/Code/Filtering/Smoothing/SmoothImageWithDiscreteGaussianFilter/
  COMPONENT Code
  )


enable_testing()
add_test(NAME SmoothImageWithDiscreteGaussianFilterTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/SmoothImageWithDiscreteGaussianFilter
    Yinyang.png
    8)
