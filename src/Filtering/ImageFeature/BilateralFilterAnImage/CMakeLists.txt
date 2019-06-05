cmake_minimum_required(VERSION 3.10.2)

project(BilateralFilterAnImage)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})


add_executable(BilateralFilterAnImage Code.cxx)
target_link_libraries(BilateralFilterAnImage ${ITK_LIBRARIES})

install(TARGETS BilateralFilterAnImage
  DESTINATION bin/ITKExamples/Filtering/ImageFeature
  COMPONENT Runtime
  )

install(FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKExamples/Code/Filtering/ImageFeature/BilateralFilterAnImage/
  COMPONENT Code
  )


enable_testing()
add_test(NAME BilateralFilterAnImageTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/BilateralFilterAnImage)
