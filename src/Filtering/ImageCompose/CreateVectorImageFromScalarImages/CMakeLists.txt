cmake_minimum_required(VERSION 3.16.3)

project(CreateVectorImageFromScalarImages)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})


add_executable(CreateVectorImageFromScalarImages Code.cxx)
target_link_libraries(CreateVectorImageFromScalarImages ${ITK_LIBRARIES})

install(TARGETS CreateVectorImageFromScalarImages
  DESTINATION bin/ITKSphinxExamples/Filtering/ImageCompose
  COMPONENT Runtime
  )

install(FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKSphinxExamples/Code/Filtering/ImageCompose/CreateVectorImageFromScalarImages/
  COMPONENT Code
  )


enable_testing()
add_test(NAME CreateVectorImageFromScalarImagesTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/CreateVectorImageFromScalarImages)
