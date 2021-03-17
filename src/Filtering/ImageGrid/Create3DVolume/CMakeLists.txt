cmake_minimum_required(VERSION 3.10.2)

project( Create3DVolume )

find_package( ITK REQUIRED )
include( ${ITK_USE_FILE} )

add_executable( Create3DVolume
  Code.cxx )
target_link_libraries( Create3DVolume ${ITK_LIBRARIES} )

install( TARGETS Create3DVolume
  DESTINATION bin/ITKSphinxExamples/Filtering/ImageGrid
  COMPONENT Runtime
  )

install( FILES Create3DVolume.cxx CMakeLists.txt
  DESTINATION share/ITKSphinxExamples/Code/Filtering/ImageGrid/Create3DVolume
  COMPONENT Code
  )

enable_testing()
add_test( NAME Create3DVolumeTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Create3DVolume
    ${CMAKE_CURRENT_BINARY_DIR}/mri3D_0.mha
    ${CMAKE_CURRENT_BINARY_DIR}/mri3D_1.mha
    ${CMAKE_CURRENT_BINARY_DIR}/mri3D_2.mha
    Output.mha
  )

if( ITK_WRAP_PYTHON )
  add_test( NAME Create3DVolumeTestPython
    COMMAND ${PYTHON_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/Code.py
      ${CMAKE_CURRENT_BINARY_DIR}/mri3D_0.mha
      ${CMAKE_CURRENT_BINARY_DIR}/mri3D_1.mha
      ${CMAKE_CURRENT_BINARY_DIR}/mri3D_2.mha
      OutputPython.mha
    )
endif()
