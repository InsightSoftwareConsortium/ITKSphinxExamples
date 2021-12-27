cmake_minimum_required(VERSION 3.16.3)

project(ResampleAScalarImage )

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})

add_executable(ResampleAScalarImage Code.cxx)
target_link_libraries(ResampleAScalarImage ${ITK_LIBRARIES})

install(TARGETS ResampleAScalarImage
  DESTINATION bin/ITKSphinxExamples/Filtering/ImageGrid
  COMPONENT Runtime
  )

install(FILES Code.cxx CMakeLists.txt Code.py
  DESTINATION share/ITKSphinxExamples/Code/Filtering/ImageGrid/ResampleAScalarImage
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

if(ITK_WRAP_PYTHON)
  add_test(NAME ResampleAScalarImageTestPython
    COMMAND ${PYTHON_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/Code.py
      ${CMAKE_CURRENT_BINARY_DIR}/Gourds.png
      OutputPython.png
      160
      120
    )
endif()
