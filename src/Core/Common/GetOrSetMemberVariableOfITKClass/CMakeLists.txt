cmake_minimum_required(VERSION 3.10.2)

project(GetOrSetMemberVariableOfITKClass)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})


add_executable(GetOrSetMemberVariableOfITKClass Code.cxx)
target_link_libraries(GetOrSetMemberVariableOfITKClass ${ITK_LIBRARIES})

install(TARGETS GetOrSetMemberVariableOfITKClass
  DESTINATION bin/ITKExamples/Core/Common
  COMPONENT Runtime
  )

install(FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKExamples/Code/Core/Common/GetOrSetMemberVariableOfITKClass/
  COMPONENT Code
  )


enable_testing()
add_test(NAME GetOrSetMemberVariableOfITKClassTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/GetOrSetMemberVariableOfITKClass)

