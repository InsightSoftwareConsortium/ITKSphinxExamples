cmake_minimum_required(VERSION 3.10.2)

project(WatchRegistration)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})


add_executable(WatchRegistration Code.cxx)
target_link_libraries(WatchRegistration ${ITK_LIBRARIES})

install(TARGETS WatchRegistration
  DESTINATION bin/ITKExamples/Registration/Common
  COMPONENT Runtime
  )

install(FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKExamples/Code/Registration/Common/WatchRegistration/
  COMPONENT Code
  )


enable_testing()
add_test(NAME WatchRegistrationTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/WatchRegistration)

