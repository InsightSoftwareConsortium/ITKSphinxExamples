cmake_minimum_required(VERSION 3.10.2)

project(Ellipse)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})


add_executable(Ellipse Code.cxx)
target_link_libraries(Ellipse ${ITK_LIBRARIES})

install(TARGETS Ellipse
  DESTINATION bin/ITKExamples/Core/SpatialObjects
  COMPONENT Runtime
  )

install(FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKExamples/Code/Core/SpatialObjects/Ellipse/
  COMPONENT Code
  )


enable_testing()
add_test(NAME EllipseTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Ellipse)
