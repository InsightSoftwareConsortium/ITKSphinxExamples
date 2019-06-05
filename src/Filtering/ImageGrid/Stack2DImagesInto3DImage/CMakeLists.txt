cmake_minimum_required(VERSION 3.10.2)

project(Stack2DImagesInto3DImage)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})


add_executable(Stack2DImagesInto3DImage Code.cxx)
target_link_libraries(Stack2DImagesInto3DImage ${ITK_LIBRARIES})

install(TARGETS Stack2DImagesInto3DImage
  DESTINATION bin/ITKExamples/Filtering/ImageGrid
  COMPONENT Runtime
  )

install(FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKExamples/Code/Filtering/ImageGrid/Stack2DImagesInto3DImage/
  COMPONENT Code
  )


enable_testing()
add_test(NAME Stack2DImagesInto3DImageTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Stack2DImagesInto3DImage)

