cmake_minimum_required(VERSION 3.10.2)

project(ExhaustiveOptimizer)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})


add_executable(ExhaustiveOptimizer Code.cxx)
target_link_libraries(ExhaustiveOptimizer ${ITK_LIBRARIES})

install(TARGETS ExhaustiveOptimizer
  DESTINATION bin/ITKExamples/Numerics/Optimizers
  COMPONENT Runtime
  )

install(FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKExamples/Code/Numerics/Optimizers/ExhaustiveOptimizer/
  COMPONENT Code
  )


enable_testing()
add_test(NAME ExhaustiveOptimizerTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/ExhaustiveOptimizer)

