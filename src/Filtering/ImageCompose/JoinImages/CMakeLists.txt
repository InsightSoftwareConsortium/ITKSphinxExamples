cmake_minimum_required(VERSION 3.10.2)

project(JoinImages)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})


add_executable(JoinImages Code.cxx)
target_link_libraries(JoinImages ${ITK_LIBRARIES})

install(TARGETS JoinImages
  DESTINATION bin/ITKExamples/Filtering/ImageCompose
  COMPONENT Runtime
  )

install(FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKExamples/Code/Filtering/ImageCompose/JoinImages/
  COMPONENT Code
  )


enable_testing()
add_test(NAME JoinImagesTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/JoinImages)
