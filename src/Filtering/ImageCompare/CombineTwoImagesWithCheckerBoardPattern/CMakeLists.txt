cmake_minimum_required(VERSION 3.10.2)

project( CombineTwoImagesWithCheckerBoardPattern )

find_package( ITK REQUIRED )
include( ${ITK_USE_FILE} )

add_executable( CombineTwoImagesWithCheckerBoardPattern Code.cxx )
target_link_libraries( CombineTwoImagesWithCheckerBoardPattern ${ITK_LIBRARIES} )

install( TARGETS CombineTwoImagesWithCheckerBoardPattern
  DESTINATION bin/ITKSphinxExamples/Filtering/ImageCompare
  COMPONENT Runtime
)

install( FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKSphinxExamples/Code/Filtering/ImageCompare/CombineTwoImagesWithCheckerBoardPattern
  COMPONENT Code
)

enable_testing()
add_test( NAME CombineTwoImagesWithCheckerBoardPatternTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/CombineTwoImagesWithCheckerBoardPattern
    Output.png
)
