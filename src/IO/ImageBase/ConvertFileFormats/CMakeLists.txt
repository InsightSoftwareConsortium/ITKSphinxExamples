cmake_minimum_required(VERSION 3.8.2)

project( ConvertFileFormats )

find_package( ITK REQUIRED )
include( ${ITK_USE_FILE} )

add_executable( ConvertFileFormats Code.cxx )
target_link_libraries( ConvertFileFormats ${ITK_LIBRARIES} )

install( TARGETS ConvertFileFormats
  DESTINATION bin/ITKExamples/IO/ImageBase
  COMPONENT Runtime
  )

install( FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKExamples/Code/IO/ImageBase/ConvertFileFormats
  COMPONENT Code
  )

enable_testing()
add_test( NAME ConvertFileFormatsTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/ConvertFileFormats
    ${CMAKE_CURRENT_BINARY_DIR}/Gourds.png
    ${CMAKE_CURRENT_BINARY_DIR}/Output.jpg
  )
