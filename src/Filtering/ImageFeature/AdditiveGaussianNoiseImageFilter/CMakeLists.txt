cmake_minimum_required(VERSION 3.10.2)

project( AdditiveGaussianNoiseImageFilter )

find_package( ITK REQUIRED )
include( ${ITK_USE_FILE} )

add_executable( AdditiveGaussianNoiseImageFilter Code.cxx )
target_link_libraries( AdditiveGaussianNoiseImageFilter ${ITK_LIBRARIES} )

install( TARGETS AdditiveGaussianNoiseImageFilter
  DESTINATION bin/ITKSphinxExamples/Filtering/ImageFeature
  COMPONENT Runtime
)

install( FILES Code.cxx CMakeLists.txt Code.py
  DESTINATION share/ITKSphinxExamples/Code/Filtering/ImageFeature/AdditiveGaussianNoiseImageFilter
  COMPONENT Code
)

enable_testing()
add_test( NAME AdditiveGaussianNoiseImageFilterTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/AdditiveGaussianNoiseImageFilter
  ${CMAKE_CURRENT_BINARY_DIR}/Gourds.png
  Output.png
  20
  1
  )

if(ITK_WRAP_PYTHON)
    find_package(PythonInterp REQUIRED)
    add_test( NAME AdditiveGaussianNoiseImageFilterTestPython
      COMMAND ${PYTHON_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/Code.py
      ${CMAKE_CURRENT_BINARY_DIR}/Gourds.png
      OutputPython.png
      20
      1
      )
endif()