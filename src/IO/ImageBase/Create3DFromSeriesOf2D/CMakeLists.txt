cmake_minimum_required(VERSION 3.10.2)

project(Create3DFromSeriesOf2D)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})


add_executable(Create3DFromSeriesOf2D Code.cxx)
target_link_libraries(Create3DFromSeriesOf2D ${ITK_LIBRARIES})

install(TARGETS Create3DFromSeriesOf2D
  DESTINATION bin/ITKExamples/IO/ImageBase
  COMPONENT Runtime
  )

install(FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKExamples/Code/IO/ImageBase/Create3DFromSeriesOf2D/
  COMPONENT Code
  )


enable_testing()
add_test(NAME Create3DFromSeriesOf2DTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Create3DFromSeriesOf2D)
