cmake_minimum_required(VERSION 3.8.2)

project( TranslateImage )

find_package( ITK REQUIRED )
include( ${ITK_USE_FILE} )

add_executable( TranslateImage Code.cxx )
target_link_libraries( TranslateImage ${ITK_LIBRARIES} )

install( TARGETS TranslateImage
  DESTINATION bin/ITKExamples/Core/Transform
  COMPONENT Runtime
  )

install( FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKExamples/Code/Core/Transform/TranslateImage
  COMPONENT Code
  )

enable_testing()
add_test( NAME TranslateImageTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/TranslateImage ${CMAKE_CURRENT_BINARY_DIR}/Gourds.png Output.png 25. 50. )
