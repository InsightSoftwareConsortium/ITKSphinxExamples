cmake_minimum_required(VERSION 3.10.2)

project(CreateGaussianDistribution)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})


add_executable(CreateGaussianDistribution Code.cxx)
target_link_libraries(CreateGaussianDistribution ${ITK_LIBRARIES})

install(TARGETS CreateGaussianDistribution
  DESTINATION bin/ITKExamples/Numerics/Statistics
  COMPONENT Runtime
  )

install(FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKExamples/Code/Numerics/Statistics/CreateGaussianDistribution/
  COMPONENT Code
  )


enable_testing()
add_test(NAME CreateGaussianDistributionTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/CreateGaussianDistribution)

