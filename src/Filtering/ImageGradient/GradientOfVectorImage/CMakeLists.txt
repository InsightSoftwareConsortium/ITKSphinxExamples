cmake_minimum_required(VERSION 3.16.3)

project(GradientOfVectorImage)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})


add_executable(GradientOfVectorImage Code.cxx)
target_link_libraries(GradientOfVectorImage ${ITK_LIBRARIES})

install(TARGETS GradientOfVectorImage
  DESTINATION bin/ITKSphinxExamples/Filtering/ImageGradient
  COMPONENT Runtime
  )

install(FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKSphinxExamples/Code/Filtering/ImageGradient/GradientOfVectorImage/
  COMPONENT Code
  )


enable_testing()
add_test(NAME GradientOfVectorImageTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/GradientOfVectorImage)
