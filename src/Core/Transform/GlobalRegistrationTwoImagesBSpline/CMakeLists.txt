cmake_minimum_required(VERSION 3.10.2)

project(GlobalRegistrationTwoImagesBSpline)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})


add_executable(GlobalRegistrationTwoImagesBSpline Code.cxx)
target_link_libraries(GlobalRegistrationTwoImagesBSpline ${ITK_LIBRARIES})

install(TARGETS GlobalRegistrationTwoImagesBSpline
  DESTINATION bin/ITKExamples/Core/Transform
  COMPONENT Runtime
  )

install(FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKExamples/Code/Core/Transform/GlobalRegistrationTwoImagesBSpline/
  COMPONENT Code
  )


enable_testing()
add_test(NAME GlobalRegistrationTwoImagesBSplineTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/GlobalRegistrationTwoImagesBSpline)
