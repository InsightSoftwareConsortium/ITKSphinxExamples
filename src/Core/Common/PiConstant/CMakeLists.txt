cmake_minimum_required(VERSION 3.10.2)

project(PiConstant)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})


add_executable(PiConstant Code.cxx)
target_link_libraries(PiConstant ${ITK_LIBRARIES})

install(TARGETS PiConstant
  DESTINATION bin/ITKSphinxExamples/Core/Common
  COMPONENT Runtime
  )

install(FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKSphinxExamples/Code/Core/Common/PiConstant/
  COMPONENT Code
  )


enable_testing()
add_test(NAME PiConstantTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/PiConstant)

