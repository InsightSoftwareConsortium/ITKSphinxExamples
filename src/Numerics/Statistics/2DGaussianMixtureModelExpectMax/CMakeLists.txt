cmake_minimum_required(VERSION 3.10.2)

project(2DGaussianMixtureModelExpectMax)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})


add_executable(2DGaussianMixtureModelExpectMax Code.cxx)
target_link_libraries(2DGaussianMixtureModelExpectMax ${ITK_LIBRARIES})

install(TARGETS 2DGaussianMixtureModelExpectMax
  DESTINATION bin/ITKExamples/Numerics/Statistics
  COMPONENT Runtime
  )

install(FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKExamples/Code/Numerics/Statistics/2DGaussianMixtureModelExpectMax/
  COMPONENT Code
  )


enable_testing()
add_test(NAME 2DGaussianMixtureModelExpectMaxTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/2DGaussianMixtureModelExpectMax)
