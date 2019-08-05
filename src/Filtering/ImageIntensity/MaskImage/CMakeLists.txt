cmake_minimum_required(VERSION 3.10.2)

project(MaskImage)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})


add_executable(MaskImage Code.cxx)
target_link_libraries(MaskImage ${ITK_LIBRARIES})

install(TARGETS MaskImage
  DESTINATION bin/ITKExamples/Filtering/ImageIntensity
  COMPONENT Runtime
  )

install(FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKExamples/Code/Filtering/ImageIntensity/MaskImage/
  COMPONENT Code
  )


enable_testing()
add_test(NAME MaskImageTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/MaskImage
    Yinyang.png
    )
