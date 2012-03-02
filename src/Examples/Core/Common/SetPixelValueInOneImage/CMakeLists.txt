cmake_minimum_required( VERSION 2.8 )

project( SetPixelValueInOneImage )

find_package( ITK REQUIRED )

include( ${ITK_USE_FILE} )
add_executable( SetPixelValueInOneImage SetPixelValueInOneImage.cxx )
target_link_libraries( SetPixelValueInOneImage ${ITK_LIBRARIES} )

install( TARGETS SetPixelValueInOneImage
  DESTINATION bin/ITKExamples/Core/Common
  COMPONENT Runtime
)

install( FILES SetPixelValueInOneImage.cxx CMakeLists.txt
  DESTINATION share/ITKExamples/Code/Core/Common/SetPixelValueInOneImage
  COMPONENT Code
)

enable_testing()
add_test( NAME SetPixelValueInOneImageTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/SetPixelValueInOneImage
  ${CMAKE_CURRENT_BINARY_DIR}/SetPixelValueInOneImageOutput.png
)
