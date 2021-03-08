cmake_minimum_required(VERSION 3.10.2)

project(ResampleAScalarImage )

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})

add_executable(ResampleAScalarImage Code.cxx)
target_link_libraries(ResampleAScalarImage ${ITK_LIBRARIES})

install(TARGETS ResampleAScalarImage
  DESTINATION bin/ITKExamples/Filtering/ImageGrid
  COMPONENT Runtime
  )

install(FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKExamples/Code/Filtering/ImageGrid/ResampleAScalarImage
  COMPONENT Code
  )

enable_testing()
add_test(NAME ResampleAScalarImageTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/ResampleAScalarImage
    ${CMAKE_CURRENT_BINARY_DIR}/Gourds.png
    Output.png
    160
    120
  )
