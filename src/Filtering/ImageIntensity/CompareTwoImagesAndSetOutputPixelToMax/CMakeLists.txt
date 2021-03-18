cmake_minimum_required(VERSION 3.10.2)

project(CompareTwoImagesAndSetOutputPixelToMax)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})


add_executable(CompareTwoImagesAndSetOutputPixelToMax Code.cxx)
target_link_libraries(CompareTwoImagesAndSetOutputPixelToMax ${ITK_LIBRARIES})

install(TARGETS CompareTwoImagesAndSetOutputPixelToMax
  DESTINATION bin/ITKSphinxExamples/Filtering/ImageIntensity
  COMPONENT Runtime
  )

install(FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKSphinxExamples/Code/Filtering/ImageIntensity/CompareTwoImagesAndSetOutputPixelToMax/
  COMPONENT Code
  )


enable_testing()
add_test(NAME CompareTwoImagesAndSetOutputPixelToMaxTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/CompareTwoImagesAndSetOutputPixelToMax)
