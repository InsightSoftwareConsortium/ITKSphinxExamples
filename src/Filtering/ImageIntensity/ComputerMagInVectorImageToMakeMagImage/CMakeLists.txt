cmake_minimum_required(VERSION 3.10.2)

project(ComputerMagInVectorImageToMakeMagImage)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})


add_executable(ComputerMagInVectorImageToMakeMagImage Code.cxx)
target_link_libraries(ComputerMagInVectorImageToMakeMagImage ${ITK_LIBRARIES})

install(TARGETS ComputerMagInVectorImageToMakeMagImage
  DESTINATION bin/ITKSphinxExamples/Filtering/ImageIntensity
  COMPONENT Runtime
  )

install(FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKSphinxExamples/Code/Filtering/ImageIntensity/ComputerMagInVectorImageToMakeMagImage/
  COMPONENT Code
  )


enable_testing()
add_test(NAME ComputerMagInVectorImageToMakeMagImageTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/ComputerMagInVectorImageToMakeMagImage
    Yinyang.png
    output.png)
