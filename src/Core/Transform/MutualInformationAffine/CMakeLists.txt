cmake_minimum_required(VERSION 3.10.2)

project(MutualInformationAffine)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})


add_executable(MutualInformationAffine Code.cxx)
target_link_libraries(MutualInformationAffine ${ITK_LIBRARIES})

install(TARGETS MutualInformationAffine
  DESTINATION bin/ITKSphinxExamples/Core/Transform
  COMPONENT Runtime
  )

install(FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKSphinxExamples/Code/Core/Transform/MutualInformationAffine/
  COMPONENT Code
  )


enable_testing()
add_test(NAME MutualInformationAffineTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/MutualInformationAffine
  fixed.png
  moving.png
  output.png)

