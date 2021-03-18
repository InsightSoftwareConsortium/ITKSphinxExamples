cmake_minimum_required(VERSION 3.10.2)

project( MultiplyImageByScalar )

find_package( ITK REQUIRED )
include( ${ITK_USE_FILE} )

add_executable( MultiplyImageByScalar Code.cxx )
target_link_libraries( MultiplyImageByScalar ${ITK_LIBRARIES} )

install( TARGETS MultiplyImageByScalar
  DESTINATION bin/ITKSphinxExamples/Filtering/ImageIntensity
  COMPONENT Runtime
  )

install( FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKSphinxExamples/Code/Filtering/ImageIntensity/MultiplyImageByScalar
  COMPONENT Code
  )

enable_testing()
add_test( NAME MultiplyImageByScalarTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/MultiplyImageByScalar
    ${CMAKE_CURRENT_BINARY_DIR}/Gourds.png 2.5 Output.mha
)
