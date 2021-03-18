cmake_minimum_required(VERSION 3.10.2)

project(DeepCopyImage)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})


add_executable(DeepCopyImage Code.cxx)
target_link_libraries(DeepCopyImage ${ITK_LIBRARIES})

install(TARGETS DeepCopyImage
  DESTINATION bin/ITKSphinxExamples/Core/Common
  COMPONENT Runtime
  )

install(FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKSphinxExamples/Code/Core/Common/DeepCopyImage/
  COMPONENT Code
  )


enable_testing()
add_test(NAME DeepCopyImageTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/DeepCopyImage)
