cmake_minimum_required( VERSION 2.8 )

project( CombineTwoImagesWithCheckerBoardPattern )

find_package( ITK REQUIRED )

include( ${ITK_USE_FILE} )
add_executable( CombineTwoImagesWithCheckerBoardPattern CombineTwoImagesWithCheckerBoardPattern.cxx )
target_link_libraries( CombineTwoImagesWithCheckerBoardPattern ${ITK_LIBRARIES} )

install( TARGETS CombineTwoImagesWithCheckerBoardPattern
  DESTINATION bin/ITKExamples/Filtering/ImageCompare
  COMPONENT Runtime
)

install( FILES CombineTwoImagesWithCheckerBoardPattern.cxx CMakeLists.txt
  DESTINATION share/ITKExamples/Code/Filtering/ImageCompare/CombineTwoImagesWithCheckerBoardPattern
  COMPONENT Code
)

enable_testing()
add_test( NAME CombineTwoImagesWithCheckerBoardPatternTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/CombineTwoImagesWithCheckerBoardPattern
    CombineTwoImagesWithCheckerBoardPatternOutput.png
)
