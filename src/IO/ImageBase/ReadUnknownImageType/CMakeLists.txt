cmake_minimum_required(VERSION 3.10.2)

project( ReadUnknownImageType )

find_package( ITK REQUIRED )
include( ${ITK_USE_FILE} )

add_executable( ReadUnknownImageType Code.cxx )
target_link_libraries( ReadUnknownImageType ${ITK_LIBRARIES} )

install( TARGETS ReadUnknownImageType
  DESTINATION bin/ITKSphinxExamples/IO/ImageBase
  COMPONENT Runtime
  )

install( FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKSphinxExamples/Code/IO/ImageBase/ReadUnknownImageType
  COMPONENT Code
  )

enable_testing()
add_test( NAME ReadUnknownImageTypeTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/ReadUnknownImageType
    ${CMAKE_CURRENT_BINARY_DIR}/Gourds.png
  )

add_test( NAME ReadUnknownImageTypeTest1
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/ReadUnknownImageType
    ${CMAKE_CURRENT_BINARY_DIR}/HeadMRVolume.mha
  )
