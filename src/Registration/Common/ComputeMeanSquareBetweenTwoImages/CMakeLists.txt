cmake_minimum_required(VERSION 3.10.2)

project(ComputeMeanSquareBetweenTwoImages)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})


add_executable(ComputeMeanSquareBetweenTwoImages Code.cxx)
target_link_libraries(ComputeMeanSquareBetweenTwoImages ${ITK_LIBRARIES})

install(TARGETS ComputeMeanSquareBetweenTwoImages
  DESTINATION bin/ITKSphinxExamples/Registration/Common
  COMPONENT Runtime
  )

install(FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKSphinxExamples/Code/Registration/Common/ComputeMeanSquareBetweenTwoImages/
  COMPONENT Code
  )


enable_testing()
add_test(NAME ComputeMeanSquareBetweenTwoImagesTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/ComputeMeanSquareBetweenTwoImages
    Yinyang.png
    Gourds.png)
