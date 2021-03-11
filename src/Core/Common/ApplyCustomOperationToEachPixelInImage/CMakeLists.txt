cmake_minimum_required(VERSION 3.10.2)

project(CustomOperationToEachPixelInImage)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})


add_executable(CustomOperationToEachPixelInImage Code.cxx)
target_link_libraries(CustomOperationToEachPixelInImage ${ITK_LIBRARIES})

install(TARGETS CustomOperationToEachPixelInImage
  DESTINATION bin/ITKExamples/Core/Common
  COMPONENT Runtime
  )

install(FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKExamples/Code/Core/Common/CustomOperationToEachPixelInImage/
  COMPONENT Code
  )


enable_testing()
add_test(NAME CustomOperationToEachPixelInImageTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/CustomOperationToEachPixelInImage)
