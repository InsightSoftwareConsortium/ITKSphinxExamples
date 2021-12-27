cmake_minimum_required(VERSION 3.16.3)

project(ScalePixelSumToConstant)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})


add_executable(ScalePixelSumToConstant Code.cxx)
target_link_libraries(ScalePixelSumToConstant ${ITK_LIBRARIES})

install(TARGETS ScalePixelSumToConstant
  DESTINATION bin/ITKSphinxExamples/Filtering/ImageIntensity
  COMPONENT Runtime
  )

install(FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKSphinxExamples/Code/Filtering/ImageIntensity/ScalePixelSumToConstant/
  COMPONENT Code
  )


enable_testing()


add_test(NAME ScalePixelSumToConstantTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/ScalePixelSumToConstant)
