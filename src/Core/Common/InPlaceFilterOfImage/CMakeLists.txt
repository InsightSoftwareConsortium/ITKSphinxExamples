cmake_minimum_required(VERSION 3.10.2)

project(InPlaceFilterOfImage)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})


add_executable(InPlaceFilterOfImage Code.cxx)
target_link_libraries(InPlaceFilterOfImage ${ITK_LIBRARIES})

install(TARGETS InPlaceFilterOfImage
  DESTINATION bin/ITKExamples/Core/Common
  COMPONENT Runtime
  )

install(FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKExamples/Code/Core/Common/InPlaceFilterOfImage/
  COMPONENT Code
  )


enable_testing()
add_test(NAME InPlaceFilterOfImageTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/InPlaceFilterOfImage)
