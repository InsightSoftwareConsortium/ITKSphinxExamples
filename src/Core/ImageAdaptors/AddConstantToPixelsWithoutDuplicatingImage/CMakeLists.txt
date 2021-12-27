cmake_minimum_required(VERSION 3.16.3)

project(AddConstantToPixelsWithoutDuplicatingImage)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})


add_executable(AddConstantToPixelsWithoutDuplicatingImage Code.cxx)
target_link_libraries(AddConstantToPixelsWithoutDuplicatingImage ${ITK_LIBRARIES})

install(TARGETS AddConstantToPixelsWithoutDuplicatingImage
  DESTINATION bin/ITKSphinxExamples/Core/ImageAdaptors
  COMPONENT Runtime
  )

install(FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKSphinxExamples/Code/Core/ImageAdaptors/AddConstantToPixelsWithoutDuplicatingImage/
  COMPONENT Code
  )


enable_testing()
add_test(NAME AddConstantToPixelsWithoutDuplicatingImageTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/AddConstantToPixelsWithoutDuplicatingImage)

