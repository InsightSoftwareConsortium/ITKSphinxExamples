cmake_minimum_required(VERSION 3.16.3)

project( GenerateRandomImage )

find_package( ITK REQUIRED )
include( ${ITK_USE_FILE} )

add_executable( GenerateRandomImage Code.cxx )
target_link_libraries( GenerateRandomImage ${ITK_LIBRARIES} )

install( TARGETS GenerateRandomImage
  DESTINATION bin/ITKSphinxExamples/Core/TestKernel
  COMPONENT Runtime
)

install( FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKSphinxExamples/Code/Core/TestKernel/GenerateRandomImage
  COMPONENT Code
)

enable_testing()
add_test( NAME GenerateRandomImageTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/GenerateRandomImage
    ${CMAKE_CURRENT_BINARY_DIR}/Output.png
  )
