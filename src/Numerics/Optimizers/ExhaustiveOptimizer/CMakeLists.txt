cmake_minimum_required(VERSION 3.10.2)

project(ExhaustiveOptimizer)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})


add_executable(ExhaustiveOptimizer Code.cxx)
target_link_libraries(ExhaustiveOptimizer ${ITK_LIBRARIES})

install(TARGETS ExhaustiveOptimizer
  DESTINATION bin/ITKSphinxExamples/Numerics/Optimizers
  COMPONENT Runtime
  )

install(FILES Code.cxx Code.py CMakeLists.txt
  DESTINATION share/ITKSphinxExamples/Code/Numerics/Optimizers/ExhaustiveOptimizer/
  COMPONENT Code
  )


enable_testing()

set(fixed_image ${CMAKE_CURRENT_BINARY_DIR}/orange.jpg)
set(moving_image ${CMAKE_CURRENT_BINARY_DIR}/apple.jpg)

add_test(NAME ExhaustiveOptimizerTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/ExhaustiveOptimizer
	${fixed_image}
	${moving_image})
	
if(ITK_WRAP_PYTHON)
	add_test(NAME ExhaustiveOptimizerTestPython
	 COMMAND ${PYTHON_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/Code.py
	  ${fixed_image}
	  ${moving_image})
endif()
