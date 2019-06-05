cmake_minimum_required(VERSION 3.10.2)

project(ConvolveImageWithKernel)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})


add_executable(ConvolveImageWithKernel Code.cxx)
target_link_libraries(ConvolveImageWithKernel ${ITK_LIBRARIES})

install(TARGETS ConvolveImageWithKernel
  DESTINATION bin/ITKExamples/Filtering/Convolution
  COMPONENT Runtime
  )

install(FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKExamples/Code/Filtering/Convolution/ConvolveImageWithKernel/
  COMPONENT Code
  )


enable_testing()
add_test(NAME ConvolveImageWithKernelTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/ConvolveImageWithKernel)
