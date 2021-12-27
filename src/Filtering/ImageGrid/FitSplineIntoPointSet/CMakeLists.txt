cmake_minimum_required(VERSION 3.16.3)

project(FitSplineIntoPointSet)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})


add_executable(FitSplineIntoPointSet Code.cxx)
target_link_libraries(FitSplineIntoPointSet ${ITK_LIBRARIES})

install(TARGETS FitSplineIntoPointSet
  DESTINATION bin/ITKSphinxExamples/Filtering/ImageGrid
  COMPONENT Runtime
  )

install(FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKSphinxExamples/Code/Filtering/ImageGrid/FitSplineIntoPointSet/
  COMPONENT Code
  )


enable_testing()
add_test(NAME FitSplineIntoPointSetTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/FitSplineIntoPointSet)
