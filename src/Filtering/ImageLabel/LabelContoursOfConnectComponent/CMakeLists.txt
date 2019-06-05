cmake_minimum_required(VERSION 3.10.2)

project(LabelContoursOfConnectComponent)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})


add_executable(LabelContoursOfConnectComponent Code.cxx)
target_link_libraries(LabelContoursOfConnectComponent ${ITK_LIBRARIES})

install(TARGETS LabelContoursOfConnectComponent
  DESTINATION bin/ITKExamples/Filtering/ImageLabel
  COMPONENT Runtime
  )

install(FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKExamples/Code/Filtering/ImageLabel/LabelContoursOfConnectComponent/
  COMPONENT Code
  )


enable_testing()
add_test(NAME LabelContoursOfConnectComponentTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/LabelContoursOfConnectComponent)
