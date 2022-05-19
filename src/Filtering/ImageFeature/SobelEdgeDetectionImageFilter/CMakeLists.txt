cmake_minimum_required(VERSION 3.16.3)

project(SobelEdgeDetectionImageFilter)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})

add_executable(SobelEdgeDetectionImageFilter Code.cxx)
target_link_libraries(SobelEdgeDetectionImageFilter ${ITK_LIBRARIES})

install(TARGETS SobelEdgeDetectionImageFilter
  DESTINATION bin/ITKSphinxExamples/Filtering/ImageFeature
  COMPONENT Runtime
)

install(FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKSphinxExamples/Code/Filtering/ImageFeature/SobelEdgeDetectionImageFilter
  COMPONENT Code
)

enable_testing()

set(input_image ${CMAKE_CURRENT_BINARY_DIR}/Gourds.png)
set(output_image Output.mha)

add_test(NAME SobelEdgeDetectionImageFilterTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/SobelEdgeDetectionImageFilter
    ${input_image}
    ${output_image}
)

if(ITK_WRAP_PYTHON)
  string(REPLACE . "Python." output_image "${output_image}")
  add_test(NAME SobelEdgeDetectionImageFilterTestPython
    COMMAND ${PYTHON_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/Code.py
      ${input_image}
      ${output_image}
  )
endif()
