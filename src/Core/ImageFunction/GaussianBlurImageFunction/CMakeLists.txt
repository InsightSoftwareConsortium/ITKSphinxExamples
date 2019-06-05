cmake_minimum_required(VERSION 3.10.2)

project(GaussianBlurImageFunction)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})


add_executable(GaussianBlurImageFunction Code.cxx)
target_link_libraries(GaussianBlurImageFunction ${ITK_LIBRARIES})

install(TARGETS GaussianBlurImageFunction
  DESTINATION bin/ITKExamples/Core/ImageFunction
  COMPONENT Runtime
  )

install(FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKExamples/Code/Core/ImageFunction/GaussianBlurImageFunction/
  COMPONENT Code
  )


enable_testing()
add_test(NAME GaussianBlurImageFunctionTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/GaussianBlurImageFunction
  )
