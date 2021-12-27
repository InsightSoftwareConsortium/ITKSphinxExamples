cmake_minimum_required(VERSION 3.16.3)

project(DataStructureForPieceWiseLinearCurve)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})


add_executable(DataStructureForPieceWiseLinearCurve Code.cxx)
target_link_libraries(DataStructureForPieceWiseLinearCurve ${ITK_LIBRARIES})

install(TARGETS DataStructureForPieceWiseLinearCurve
  DESTINATION bin/ITKSphinxExamples/Filtering/Path
  COMPONENT Runtime
  )

install(FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKSphinxExamples/Code/Filtering/Path/DataStructureForPieceWiseLinearCurve/
  COMPONENT Code
  )


enable_testing()
add_test(NAME DataStructureForPieceWiseLinearCurveTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/DataStructureForPieceWiseLinearCurve)

