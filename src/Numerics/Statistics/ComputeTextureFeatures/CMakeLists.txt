cmake_minimum_required(VERSION 3.10.2)

project(ComputeTextureFeatures)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})


add_executable(ComputeTextureFeatures Code.cxx)
target_link_libraries(ComputeTextureFeatures ${ITK_LIBRARIES})

install(TARGETS ComputeTextureFeatures
  DESTINATION bin/ITKExamples/Numerics/Statistics
  COMPONENT Runtime
  )

install(FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKExamples/Code/Numerics/Statistics/ComputeTextureFeatures/
  COMPONENT Code
  )


enable_testing()
add_test(NAME ComputeTextureFeaturesTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/ComputeTextureFeatures)

