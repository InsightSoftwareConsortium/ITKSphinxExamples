cmake_minimum_required(VERSION 3.10.2)

project(ProduceImageProgrammatically)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})


add_executable(ProduceImageProgrammatically Code.cxx)
target_link_libraries(ProduceImageProgrammatically ${ITK_LIBRARIES})

install(TARGETS ProduceImageProgrammatically
  DESTINATION bin/ITKExamples/Core/Common
  COMPONENT Runtime
  )

install(FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKExamples/Code/Core/Common/ProduceImageProgrammatically/
  COMPONENT Code
  )


enable_testing()
add_test(NAME ProduceImageProgrammaticallyTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/ProduceImageProgrammatically)

