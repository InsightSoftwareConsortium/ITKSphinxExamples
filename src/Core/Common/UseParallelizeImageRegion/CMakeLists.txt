cmake_minimum_required(VERSION 3.10.2)

project( UseParallelizeImageRegion )

find_package( ITK 5.0 REQUIRED )
include( ${ITK_USE_FILE} )

add_executable( UseParallelizeImageRegion Code.cxx )
target_link_libraries( UseParallelizeImageRegion ${ITK_LIBRARIES} )

install( TARGETS UseParallelizeImageRegion
  DESTINATION bin/ITKExamples/Core/Common
  COMPONENT Runtime
)

install( FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKExamples/Code/Core/Common/UseParallelizeImageRegion
  COMPONENT Code
)

enable_testing()
add_test( NAME UseParallelizeImageRegionTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/UseParallelizeImageRegion
  ${CMAKE_CURRENT_BINARY_DIR}/CellsFluorescence1.png
  CellsFluorescence1Out.png
  )
