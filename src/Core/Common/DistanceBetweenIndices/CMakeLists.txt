cmake_minimum_required(VERSION 3.16.3)

project(DistanceBetweenIndices)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})

add_executable(DistanceBetweenIndices Code.cxx)
target_link_libraries(DistanceBetweenIndices ${ITK_LIBRARIES})

install(TARGETS DistanceBetweenIndices
  DESTINATION bin/ITKSphinxExamples/Core/Common
  COMPONENT Runtime
)

install(FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKSphinxExamples/Code/Core/Common/DistanceBetweenIndices
  COMPONENT Code
)

enable_testing()
add_test(NAME DistanceBetweenIndicesTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/DistanceBetweenIndices)
