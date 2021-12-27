cmake_minimum_required(VERSION 3.16.3)

project(Matrix)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})


add_executable(Matrix Code.cxx)
target_link_libraries(Matrix ${ITK_LIBRARIES})

install(TARGETS Matrix
  DESTINATION bin/ITKSphinxExamples/Core/Common
  COMPONENT Runtime
  )

install(FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKSphinxExamples/Code/Core/Common/Matrix/
  COMPONENT Code
  )


enable_testing()
add_test(NAME MatrixTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Matrix
  )

