cmake_minimum_required(VERSION 3.10.2)

project(AmoebaOptimizer)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})


add_executable(AmoebaOptimizer Code.cxx ExampleCostFunction.h)
target_link_libraries(AmoebaOptimizer ${ITK_LIBRARIES})

install(TARGETS AmoebaOptimizer
  DESTINATION bin/ITKSphinxExamples/Numerics/Optimizers
  COMPONENT Runtime
  )

install(FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKSphinxExamples/Code/Numerics/Optimizers/AmoebaOptimizer/
  COMPONENT Code
  )


enable_testing()

add_test(NAME AmoebaOptimizerTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/AmoebaOptimizer
  )
