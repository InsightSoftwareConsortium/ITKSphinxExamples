cmake_minimum_required(VERSION 3.22.1)

project(GetOrSetMemberVariableOfITKClass)

find_package(ITK REQUIRED)


add_executable(${PROJECT_NAME} Code.cxx)
target_link_libraries(${PROJECT_NAME}
  PRIVATE
    ITK::ITKCommonModule
)

install(TARGETS ${PROJECT_NAME}
  DESTINATION bin/ITKSphinxExamples/Core/Common
  COMPONENT Runtime
  )

install(FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKSphinxExamples/Code/Core/Common/GetOrSetMemberVariableOfITKClass/
  COMPONENT Code
  )


enable_testing()
add_test(NAME GetOrSetMemberVariableOfITKClassTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${PROJECT_NAME})
