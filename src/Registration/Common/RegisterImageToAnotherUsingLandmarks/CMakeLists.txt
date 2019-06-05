cmake_minimum_required(VERSION 3.10.2)

project(RegisterImageToAnotherUsingLandmarks)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})


add_executable(RegisterImageToAnotherUsingLandmarks Code.cxx)
target_link_libraries(RegisterImageToAnotherUsingLandmarks ${ITK_LIBRARIES})

install(TARGETS RegisterImageToAnotherUsingLandmarks
  DESTINATION bin/ITKExamples/Registration/Common
  COMPONENT Runtime
  )

install(FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKExamples/Code/Registration/Common/RegisterImageToAnotherUsingLandmarks/
  COMPONENT Code
  )

enable_testing()
add_test(NAME RegisterImageToAnotherUsingLandmarksTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/RegisterImageToAnotherUsingLandmarks)
