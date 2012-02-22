cmake_minimum_required( VERSION 2.8 )

project( CreateAFixedArray )

find_package( ITK REQUIRED )

include( ${ITK_USE_FILE} )
add_executable( CreateAFixedArray CreateAFixedArray.cxx )
target_link_libraries( CreateAFixedArray ${ITK_LIBRARIES} )

install( TARGETS CreateAFixedArray
  DESTINATION bin/ITKExamples/Core/Common
  COMPONENT Runtime
)

install( FILES CreateAFixedArray.cxx CMakeLists.txt
  DESTINATION share/ITKExamples/Code/Core/Common/CreateAFixedArray
  COMPONENT Code
)

enable_testing()
add_test( NAME CreateAFixedArrayTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/CreateAFixedArray )
