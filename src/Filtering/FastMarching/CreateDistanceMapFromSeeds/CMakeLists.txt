cmake_minimum_required(VERSION 3.10.2)

project( CreateDistanceMapFromSeeds )

find_package( ITK REQUIRED )
include( ${ITK_USE_FILE} )

add_executable( CreateDistanceMapFromSeeds Code.cxx )
target_link_libraries( CreateDistanceMapFromSeeds ${ITK_LIBRARIES} )

install( TARGETS CreateDistanceMapFromSeeds
  DESTINATION bin/ITKExamples/Filtering/FastMarching
  COMPONENT Runtime
)

install( FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKExamples/Code/Filtering/FastMarching/CreateDistanceMapFromSeeds
  COMPONENT Code
)

enable_testing()
add_test( NAME CreateDistanceMapFromSeedsTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/CreateDistanceMapFromSeeds
    ${CMAKE_CURRENT_BINARY_DIR}/Output.mha
)
