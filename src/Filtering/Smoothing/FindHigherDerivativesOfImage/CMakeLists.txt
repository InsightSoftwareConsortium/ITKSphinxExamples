cmake_minimum_required(VERSION 3.10.2)

project(FindHigherDerivativesOfImage)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})


add_executable(FindHigherDerivativesOfImage Code.cxx)
target_link_libraries(FindHigherDerivativesOfImage ${ITK_LIBRARIES})

install(TARGETS FindHigherDerivativesOfImage
  DESTINATION bin/ITKExamples/Filtering/Smoothing
  COMPONENT Runtime
  )

install(FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKExamples/Code/Filtering/Smoothing/FindHigherDerivativesOfImage/
  COMPONENT Code
  )


enable_testing()
add_test(NAME FindHigherDerivativesOfImageTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/FindHigherDerivativesOfImage
    Yinyang.png)
