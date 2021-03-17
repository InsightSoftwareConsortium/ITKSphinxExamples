cmake_minimum_required(VERSION 3.10.2)

project(LinearlyInterpolatePositionInImage)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})


add_executable(LinearlyInterpolatePositionInImage Code.cxx)
target_link_libraries(LinearlyInterpolatePositionInImage ${ITK_LIBRARIES})

install(TARGETS LinearlyInterpolatePositionInImage
  DESTINATION bin/ITKSphinxExamples/Core/ImageFunction
  COMPONENT Runtime
  )

install(FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKSphinxExamples/Code/Core/ImageFunction/LinearlyInterpolatePositionInImage/
  COMPONENT Code
  )


enable_testing()
add_test(NAME LinearlyInterpolatePositionInImageTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/LinearlyInterpolatePositionInImage)
