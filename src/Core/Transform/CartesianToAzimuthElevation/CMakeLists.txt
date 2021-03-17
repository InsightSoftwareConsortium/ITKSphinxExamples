cmake_minimum_required(VERSION 3.10.2)

project(CartesianToAzimuthElevation)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})


add_executable(CartesianToAzimuthElevation Code.cxx)
target_link_libraries(CartesianToAzimuthElevation ${ITK_LIBRARIES})

install(TARGETS CartesianToAzimuthElevation
  DESTINATION bin/ITKSphinxExamples/Core/Transform
  COMPONENT Runtime
  )

install(FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKSphinxExamples/Code/Core/Transform/CartesianToAzimuthElevation/
  COMPONENT Code
  )


enable_testing()
add_test(NAME CartesianToAzimuthElevationTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/CartesianToAzimuthElevation)

