cmake_minimum_required(VERSION 3.16.3)

project(ComposeVectorFromThreeScalarImages)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})


add_executable(ComposeVectorFromThreeScalarImages Code.cxx)
target_link_libraries(ComposeVectorFromThreeScalarImages ${ITK_LIBRARIES})

install(TARGETS ComposeVectorFromThreeScalarImages
  DESTINATION bin/ITKSphinxExamples/Filtering/ImageCompose
  COMPONENT Runtime
  )

install(FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKSphinxExamples/Code/Filtering/ImageCompose/ComposeVectorFromThreeScalarImages/
  COMPONENT Code
  )


enable_testing()
add_test(NAME ComposeVectorFromThreeScalarImagesTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/ComposeVectorFromThreeScalarImages)
