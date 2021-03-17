cmake_minimum_required(VERSION 3.10.2)

project(ViewComponentVectorImageAsScaleImage)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})


add_executable(ViewComponentVectorImageAsScaleImage Code.cxx)
target_link_libraries(ViewComponentVectorImageAsScaleImage ${ITK_LIBRARIES})

install(TARGETS ViewComponentVectorImageAsScaleImage
  DESTINATION bin/ITKSphinxExamples/Core/ImageAdaptors
  COMPONENT Runtime
  )

install(FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKSphinxExamples/Code/Core/ImageAdaptors/ViewComponentVectorImageAsScaleImage/
  COMPONENT Code
  )


enable_testing()
add_test(NAME ViewComponentVectorImageAsScaleImageTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/ViewComponentVectorImageAsScaleImage)

