cmake_minimum_required(VERSION 3.10.2)

project(MutualInformation)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})


add_executable(MutualInformation Code.cxx)
target_link_libraries(MutualInformation ${ITK_LIBRARIES})

install(TARGETS MutualInformation
  DESTINATION bin/ITKExamples/Registration/Common
  COMPONENT Runtime
  )

install(FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKExamples/Code/Registration/Common/MutualInformation/
  COMPONENT Code
  )


enable_testing()
add_test(NAME MutualInformationTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/MutualInformation
  fixed.png
  moving.png
  output.png)
