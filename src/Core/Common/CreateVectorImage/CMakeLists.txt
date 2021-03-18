cmake_minimum_required(VERSION 3.10.2)

project(CreateVectorImage)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})


add_executable(CreateVectorImage Code.cxx)
target_link_libraries(CreateVectorImage ${ITK_LIBRARIES})

install(TARGETS CreateVectorImage
  DESTINATION bin/ITKSphinxExamples/Core/Common
  COMPONENT Runtime
  )

install(FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKSphinxExamples/Code/Core/Common/CreateVectorImage/
  COMPONENT Code
  )


enable_testing()
add_test(NAME CreateVectorImageTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/CreateVectorImage)

