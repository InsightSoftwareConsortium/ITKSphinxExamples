cmake_minimum_required(VERSION 3.16.3)

project(DilateAGrayscaleImage)

find_package(ITK REQUIRED
  COMPONENTS
  ITKCommon
  ITKIOImageBase
  ITKMathematicalMorphology
  ITKIOPNG
  )
include(${ITK_USE_FILE})

add_executable(${PROJECT_NAME} Code.cxx)
target_link_libraries(${PROJECT_NAME} ${ITK_LIBRARIES})

install(TARGETS ${PROJECT_NAME}
  DESTINATION bin/ITKSphinxExamples/Filtering/MathematicalMorphology
  COMPONENT Runtime
)

install(FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKSphinxExamples/Code/Filtering/MathematicalMorphology/DilateAGrayscaleImage
  COMPONENT Code
)

enable_testing()
add_test(NAME DilateAGrayscaleImageTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${PROJECT_NAME}
    ${CMAKE_CURRENT_BINARY_DIR}/cthead1.png
    Output.png
    5
  )

if(ITK_WRAP_PYTHON)
  add_test(NAME DilateAGrayscaleImageTestPython
    COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/Code.py
      ${CMAKE_CURRENT_BINARY_DIR}/cthead1.png
      OutputPython.png
      5
    )
endif()
