cmake_minimum_required(VERSION 3.10.2)

project(MatchFeaturePoints)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})


add_executable(MatchFeaturePoints Code.cxx)
target_link_libraries(MatchFeaturePoints ${ITK_LIBRARIES})

install(TARGETS MatchFeaturePoints
  DESTINATION bin/ITKExamples/Registration/Common
  COMPONENT Runtime
  )

install(FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKExamples/Code/Registration/Common/MatchFeaturePoints/
  COMPONENT Code
  )


enable_testing()
add_test(NAME MatchFeaturePointsTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/MatchFeaturePoints)

