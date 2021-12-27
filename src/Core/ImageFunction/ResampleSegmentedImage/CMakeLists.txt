cmake_minimum_required(VERSION 3.16.3)

project(ResampleSegmentedImage)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})

add_executable(ResampleSegmentedImage Code.cxx)
target_link_libraries(ResampleSegmentedImage ${ITK_LIBRARIES})

install(TARGETS ResampleSegmentedImage
  DESTINATION bin/ITKSphinxExamples/Core/ImageFunction
  COMPONENT Runtime
  )

install(FILES Code.cxx CMakeLists.txt Code.py
  DESTINATION share/ITKSphinxExamples/Code/Core/ImageFunction/ResampleSegmentedImage/
  COMPONENT Code
  )

enable_testing()
add_test(NAME ResampleSegmentedImageTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/ResampleSegmentedImage
  ${CMAKE_CURRENT_BINARY_DIR}/2th_cthead1.png
  0.75
  0.6
  Output.png
  OutputNearest.png
  )

if(ITK_WRAP_PYTHON)
  add_test(NAME ResampleSegmentedImageTestPython
    COMMAND ${PYTHON_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/Code.py
      ${CMAKE_CURRENT_BINARY_DIR}/2th_cthead1.png
      0.75
      0.6
      OutputPython.png
      OutputNearestPython.png
    )
endif()
