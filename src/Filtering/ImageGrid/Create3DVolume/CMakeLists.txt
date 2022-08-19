cmake_minimum_required(VERSION 3.16.3)

project(Create3DVolume)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})

add_executable(${PROJECT_NAME}
  Code.cxx)
target_link_libraries(${PROJECT_NAME} ${ITK_LIBRARIES})

install(TARGETS ${PROJECT_NAME}
  DESTINATION bin/ITKSphinxExamples/Filtering/ImageGrid
  COMPONENT Runtime
  )

install(FILES Code.cxx CMakeLists.txt Code.py
  DESTINATION share/ITKSphinxExamples/Code/Filtering/ImageGrid/Create3DVolume
  COMPONENT Code
  )

enable_testing()
add_test(NAME Create3DVolumeTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${PROJECT_NAME}
    ${CMAKE_CURRENT_BINARY_DIR}/mri3D_0.mha
    ${CMAKE_CURRENT_BINARY_DIR}/mri3D_1.mha
    ${CMAKE_CURRENT_BINARY_DIR}/mri3D_2.mha
    Output.mha
  )

if(ITK_WRAP_PYTHON)
  add_test(NAME Create3DVolumeTestPython
    COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/Code.py
      ${CMAKE_CURRENT_BINARY_DIR}/mri3D_0.mha
      ${CMAKE_CURRENT_BINARY_DIR}/mri3D_1.mha
      ${CMAKE_CURRENT_BINARY_DIR}/mri3D_2.mha
      OutputPython.mha
    )
endif()
