cmake_minimum_required(VERSION 3.10.2)

project( MultiplyTwoImages )

find_package( ITK REQUIRED )
include( ${ITK_USE_FILE} )

add_executable( MultiplyTwoImages Code.cxx )
target_link_libraries( MultiplyTwoImages ${ITK_LIBRARIES} )

install( TARGETS MultiplyTwoImages
  DESTINATION bin/ITKExamples/Filtering/ImageIntensity
  COMPONENT Runtime
  )

install( FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKExamples/Code/Filtering/ImageIntensity/MultiplyTwoImages
  COMPONENT Code
  )

enable_testing()
add_test( NAME MultiplyTwoImagesTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/MultiplyTwoImages
    ${CMAKE_CURRENT_BINARY_DIR}/Gourds.png
    ${CMAKE_CURRENT_BINARY_DIR}/mask.png
    Output.mha
)
