cmake_minimum_required(VERSION 3.10.2)

project(ExtractComponentOfVectorImage)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})


add_executable(ExtractComponentOfVectorImage Code.cxx)
target_link_libraries(ExtractComponentOfVectorImage ${ITK_LIBRARIES})

install(TARGETS ExtractComponentOfVectorImage
  DESTINATION bin/ITKExamples/Filtering/ImageIntensity
  COMPONENT Runtime
  )

install(FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKExamples/Code/Filtering/ImageIntensity/ExtractComponentOfVectorImage/
  COMPONENT Code
  )


enable_testing()
add_test(NAME ExtractComponentOfVectorImageTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/ExtractComponentOfVectorImage)
