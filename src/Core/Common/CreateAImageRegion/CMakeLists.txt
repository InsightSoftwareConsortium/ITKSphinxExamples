project( CreateAImageRegion )

find_package( ITK REQUIRED )

include( ${ITK_USE_FILE} )
add_executable( CreateAImageRegion Code.cxx )
target_link_libraries( CreateAImageRegion ${ITK_LIBRARIES} )

install( TARGETS CreateAImageRegion
  DESTINATION bin/ITKExamples/Core/Common
  COMPONENT Runtime
)

install( FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKExamples/Code/Core/Common/CreateAImageRegion
  COMPONENT Code
)

enable_testing()
add_test( NAME CreateAImageRegionTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/CreateAImageRegion )
