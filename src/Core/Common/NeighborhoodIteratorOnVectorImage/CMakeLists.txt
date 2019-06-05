cmake_minimum_required(VERSION 3.10.2)

project(NeighborhoodIteratorOnVectorImage)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})


add_executable(NeighborhoodIteratorOnVectorImage Code.cxx)
target_link_libraries(NeighborhoodIteratorOnVectorImage ${ITK_LIBRARIES})

install(TARGETS NeighborhoodIteratorOnVectorImage
  DESTINATION bin/ITKExamples/Core/Common
  COMPONENT Runtime
  )

install(FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKExamples/Code/Core/Common/NeighborhoodIteratorOnVectorImage/
  COMPONENT Code
  )


enable_testing()
add_test(NAME NeighborhoodIteratorOnVectorImageTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/NeighborhoodIteratorOnVectorImage)

