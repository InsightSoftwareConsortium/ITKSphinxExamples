cmake_minimum_required(VERSION 3.10.2)

project(PixelDivisionOfTwoImages)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})


add_executable(PixelDivisionOfTwoImages Code.cxx)
target_link_libraries(PixelDivisionOfTwoImages ${ITK_LIBRARIES})

install(TARGETS PixelDivisionOfTwoImages
  DESTINATION bin/ITKExamples/Filtering/ImageIntensity
  COMPONENT Runtime
  )

install(FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKExamples/Code/Filtering/ImageIntensity/PixelDivisionOfTwoImages/
  COMPONENT Code
  )


enable_testing()
add_test(NAME PixelDivisionOfTwoImagesTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/PixelDivisionOfTwoImages)

