cmake_minimum_required( VERSION 2.8 )

project( ReadAnImage )

find_package( ITK REQUIRED )

include( ${ITK_USE_FILE} )
add_executable( ReadAnImage ReadAnImage.cxx )
target_link_libraries( ReadAnImage ${ITK_LIBRARIES} )

install( TARGETS ReadAnImage
  DESTINATION bin/ITKExamples/IO/ImageBase/
  COMPONENT Runtime
)

install( FILES ReadAnImage.cxx CMakeLists.txt
  DESTINATION share/ITKExamples/Code/IO/ImageBase/ReadAnImage
  COMPONENT Code
)

enable_testing()
add_test( NAME ReadAnImageTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/ReadAnImage
    ${CMAKE_CURRENT_BINARY_DIR}/Yinyang.png
)
