cmake_minimum_required(VERSION 3.10.2)

project(TileImagesSideBySide)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})


add_executable(TileImagesSideBySide Code.cxx)
target_link_libraries(TileImagesSideBySide ${ITK_LIBRARIES})

install(TARGETS TileImagesSideBySide
  DESTINATION bin/ITKSphinxExamples/Filtering/ImageGrid
  COMPONENT Runtime
  )

install(FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKSphinxExamples/Code/Filtering/ImageGrid/TileImagesSideBySide/
  COMPONENT Code
  )


enable_testing()
add_test(NAME TileImagesSideBySideTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/TileImagesSideBySide
    Gourds.png
    Gourds.png
    output.png
  )
