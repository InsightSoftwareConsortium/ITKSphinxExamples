cmake_minimum_required(VERSION 3.10.2)

project(ApplyGradientRecursiveGaussian)

find_package(ITK 4.7.0 REQUIRED)
include(${ITK_USE_FILE})

add_executable(ApplyGradientRecursiveGaussian Code.cxx)
target_link_libraries(ApplyGradientRecursiveGaussian ${ITK_LIBRARIES})

install(TARGETS ApplyGradientRecursiveGaussian
  DESTINATION bin/ITKSphinxExamples/Filtering/ImageGradient/
  COMPONENT Runtime
  )

install(FILES Code.cxx CMakeLists.txt Code.py
  DESTINATION share/ITKSphinxExamples/Code/Filtering/ImageGradient/ApplyGradientRecursiveGaussian
  COMPONENT Code
  )


enable_testing()

set(input_image ${CMAKE_CURRENT_BINARY_DIR}/Gourds.png)
set(output_image OutputX.png OutputY.png OutputMagnitude.png)

add_test(NAME ApplyGradientRecursiveGaussianTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/ApplyGradientRecursiveGaussian
  ${input_image}
  ${output_image}
  )

if(ITK_WRAP_PYTHON)
  string(REPLACE . "Python." output_image "${output_image}")
  add_test(NAME ApplyGradientRecursiveGaussianTestPython
    COMMAND ${PYTHON_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/Code.py
      ${input_image}
      ${output_image}
    )
endif()
