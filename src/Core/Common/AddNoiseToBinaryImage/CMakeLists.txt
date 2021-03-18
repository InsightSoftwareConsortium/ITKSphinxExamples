cmake_minimum_required(VERSION 3.10.2)

project(AddNoiseToBinaryImage)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})


add_executable(AddNoiseToBinaryImage Code.cxx)
target_link_libraries(AddNoiseToBinaryImage ${ITK_LIBRARIES})

install(TARGETS AddNoiseToBinaryImage
  DESTINATION bin/ITKSphinxExamples/Core/Common
  COMPONENT Runtime
  )

install(FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKSphinxExamples/Code/Core/Common/AddNoiseToBinaryImage/
  COMPONENT Code
  )


enable_testing()
add_test(NAME AddNoiseToBinaryImageTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/AddNoiseToBinaryImage
    Yinyang.png
    output.png
    50)