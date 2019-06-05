cmake_minimum_required(VERSION 3.10.2)

project(ShapeAttributesForBinaryImage)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})


add_executable(ShapeAttributesForBinaryImage Code.cxx)
target_link_libraries(ShapeAttributesForBinaryImage ${ITK_LIBRARIES})

install(TARGETS ShapeAttributesForBinaryImage
  DESTINATION bin/ITKExamples/Filtering/LabelMap
  COMPONENT Runtime
  )

install(FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKExamples/Code/Filtering/LabelMap/ShapeAttributesForBinaryImage/
  COMPONENT Code
  )


enable_testing()
add_test(NAME ShapeAttributesForBinaryImageTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/ShapeAttributesForBinaryImage)

