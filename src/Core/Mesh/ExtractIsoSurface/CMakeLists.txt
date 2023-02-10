cmake_minimum_required(VERSION 3.16.3)

project(ExtractIsoSurface)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})

add_executable(${PROJECT_NAME} Code.cxx)
target_link_libraries(${PROJECT_NAME} ${ITK_LIBRARIES})

install(TARGETS ${PROJECT_NAME}
  DESTINATION bin/ITKSphinxExamples/Core/Mesh
  COMPONENT Runtime
  )

install(FILES Code.cxx CMakeLists.txt Code.py
  DESTINATION share/ITKSphinxExamples/Code/Core/Mesh/ExtractIsoSurface
  COMPONENT Code
  )

set(input_volume ${CMAKE_CURRENT_BINARY_DIR}/HeadMRVolume.mha)
set(output_mesh ${CMAKE_CURRENT_BINARY_DIR}/Output.vtk)
set(lower_threshold 64)
set(upper_threshold 255)

enable_testing()
add_test(NAME ExtractIsoSurfaceTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${PROJECT_NAME}
    ${input_volume}
    ${output_mesh}
    ${lower_threshold}
    ${upper_threshold}
)

if(ITK_WRAP_PYTHON)
  add_test(NAME ExtractIsoSurfaceTestPython
    COMMAND ${PYTHON_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/Code.py
    ${input_volume}
    OutputPython.vtk
    ${lower_threshold}
    ${upper_threshold}
    )
endif()
