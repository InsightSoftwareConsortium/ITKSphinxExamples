cmake_minimum_required(VERSION 3.10.2)

project(OutOfBoundsPixelsReturnConstValue)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})


add_executable(OutOfBoundsPixelsReturnConstValue Code.cxx)
target_link_libraries(OutOfBoundsPixelsReturnConstValue ${ITK_LIBRARIES})

install(TARGETS OutOfBoundsPixelsReturnConstValue
  DESTINATION bin/ITKExamples/Core/Common
  COMPONENT Runtime
  )

install(FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKExamples/Code/Core/Common/OutOfBoundsPixelsReturnConstValue/
  COMPONENT Code
  )


enable_testing()
add_test(NAME OutOfBoundsPixelsReturnConstValueTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/OutOfBoundsPixelsReturnConstValue)

