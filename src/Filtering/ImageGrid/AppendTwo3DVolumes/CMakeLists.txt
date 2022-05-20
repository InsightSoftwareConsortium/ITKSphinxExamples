cmake_minimum_required(VERSION 3.16.3)

project(AppendTwo3DVolumes)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})

add_executable(AppendTwo3DVolumes Code.cxx)
target_link_libraries(AppendTwo3DVolumes ${ITK_LIBRARIES})

install(TARGETS AppendTwo3DVolumes
  DESTINATION bin/ITKSphinxExamples/Filtering/ImageGrid
  COMPONENT Runtime
  )

install(FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKSphinxExamples/Code/Filtering/ImageGrid/AppendTwo3DVolumes
  COMPONENT Code
  )

enable_testing()
add_test(NAME AppendTwo3DVolumesTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/AppendTwo3DVolumes
    ${CMAKE_CURRENT_BINARY_DIR}/HeadMRVolume.mha
    ${CMAKE_CURRENT_BINARY_DIR}/HeadMRVolume.mha
    Output.mha
  )
