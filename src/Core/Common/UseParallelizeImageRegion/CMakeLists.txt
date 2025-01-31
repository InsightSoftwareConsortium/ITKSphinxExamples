cmake_minimum_required(VERSION 3.22.1)

project(UseParallelizeImageRegion)

find_package(ITK 5.0 REQUIRED)
include(${ITK_USE_FILE})

add_executable(${PROJECT_NAME} Code.cxx)
target_link_libraries(${PROJECT_NAME} ${ITK_LIBRARIES})

install(TARGETS ${PROJECT_NAME}
  DESTINATION bin/ITKSphinxExamples/Core/Common
  COMPONENT Runtime
)

install(FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKSphinxExamples/Code/Core/Common/UseParallelizeImageRegion
  COMPONENT Code
)

enable_testing()
add_test(NAME UseParallelizeImageRegionTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${PROJECT_NAME}
  ${CMAKE_CURRENT_BINARY_DIR}/CellsFluorescence1.png
  CellsFluorescence1Out.png
  )
