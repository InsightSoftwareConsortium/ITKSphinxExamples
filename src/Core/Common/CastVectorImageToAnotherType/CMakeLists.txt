cmake_minimum_required(VERSION 3.10.2)

project(CastVectorImageToAnotherType)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})


add_executable(CastVectorImageToAnotherType Code.cxx)
target_link_libraries(CastVectorImageToAnotherType ${ITK_LIBRARIES})

install(TARGETS CastVectorImageToAnotherType
  DESTINATION bin/ITKExamples/Core/Common
  COMPONENT Runtime
  )

install(FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKExamples/Code/Core/Common/CastVectorImageToAnotherType/
  COMPONENT Code
  )


enable_testing()
add_test(NAME CastVectorImageToAnotherTypeTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/CastVectorImageToAnotherType)
