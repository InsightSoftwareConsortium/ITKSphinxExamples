cmake_minimum_required(VERSION 3.10.2)

project(MultiplyKernelWithAnImageAtLocation)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})


add_executable(MultiplyKernelWithAnImageAtLocation Code.cxx)
target_link_libraries(MultiplyKernelWithAnImageAtLocation ${ITK_LIBRARIES})

install(TARGETS MultiplyKernelWithAnImageAtLocation
  DESTINATION bin/ITKExamples/Core/ImageFunction
  COMPONENT Runtime
  )

install(FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKExamples/Code/Core/ImageFunction/MultiplyKernelWithAnImageAtLocation/
  COMPONENT Code
  )


enable_testing()
add_test(NAME MultiplyKernelWithAnImageAtLocationTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/MultiplyKernelWithAnImageAtLocation
  )

