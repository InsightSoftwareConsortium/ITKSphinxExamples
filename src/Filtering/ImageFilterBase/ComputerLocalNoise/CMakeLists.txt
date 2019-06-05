cmake_minimum_required(VERSION 3.10.2)

project(ComputerLocalNoise)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})


add_executable(ComputerLocalNoise Code.cxx)
target_link_libraries(ComputerLocalNoise ${ITK_LIBRARIES})

install(TARGETS ComputerLocalNoise
  DESTINATION bin/ITKExamples/Filtering/ImageFilterBase
  COMPONENT Runtime
  )

install(FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKExamples/Code/Filtering/ImageFilterBase/ComputerLocalNoise/
  COMPONENT Code
  )


enable_testing()
add_test(NAME ComputerLocalNoiseTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/ComputerLocalNoise)

