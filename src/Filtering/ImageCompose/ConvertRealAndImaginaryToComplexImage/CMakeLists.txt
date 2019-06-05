cmake_minimum_required(VERSION 3.10.2)

project(ConvertRealAndImaginaryToComplexImage)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})


add_executable(ConvertRealAndImaginaryToComplexImage Code.cxx)
target_link_libraries(ConvertRealAndImaginaryToComplexImage ${ITK_LIBRARIES})

install(TARGETS ConvertRealAndImaginaryToComplexImage
  DESTINATION bin/ITKExamples/Filtering/ImageCompose
  COMPONENT Runtime
  )

install(FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKExamples/Code/Filtering/ImageCompose/ConvertRealAndImaginaryToComplexImage/
  COMPONENT Code
  )


enable_testing()
add_test(NAME ConvertRealAndImaginaryToComplexImageTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/ConvertRealAndImaginaryToComplexImage)
