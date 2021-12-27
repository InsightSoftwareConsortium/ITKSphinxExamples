cmake_minimum_required(VERSION 3.16.3)

project(Ellipse)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})


add_executable(Ellipse Code.cxx)
target_link_libraries(Ellipse ${ITK_LIBRARIES})

install(TARGETS Ellipse
  DESTINATION bin/ITKSphinxExamples/Core/SpatialObjects
  COMPONENT Runtime
  )

install(FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKSphinxExamples/Code/Core/SpatialObjects/Ellipse/
  COMPONENT Code
  )


enable_testing()
add_test(NAME EllipseTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Ellipse
    output.png)
