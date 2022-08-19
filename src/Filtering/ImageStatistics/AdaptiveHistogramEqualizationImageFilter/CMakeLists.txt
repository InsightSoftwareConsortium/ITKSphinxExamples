cmake_minimum_required(VERSION 3.16.3)

project(AdaptiveHistogramEqualizationImageFilter)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})


add_executable(${PROJECT_NAME} Code.cxx)
target_link_libraries(${PROJECT_NAME} ${ITK_LIBRARIES})

install(TARGETS ${PROJECT_NAME}
  DESTINATION bin/ITKSphinxExamples/Filtering/Statistics
  COMPONENT Runtime
  )

install(FILES Code.cxx CMakeLists.txt Code.py
  DESTINATION share/ITKSphinxExamples/Code/Filtering/Statistics/AdaptiveHistogramEqualizationImageFilter/
  COMPONENT Code
  )


enable_testing()
set(input_image ${CMAKE_CURRENT_BINARY_DIR}/sf4.png)
set(alpha01 0.0)
set(alpha02 0.25)
set(alpha03 0.5)
set(alpha04 0.75)
set(alpha05 1.0)
set(beta01 0.0)
set(beta02 0.25)
set(beta03 0.5)
set(beta04 0.75)
set(beta05 1.0)
set(radius01 1)
set(radius02 2)
set(radius03 5)
set(radius04 10)


add_test(NAME AdaptiveHistogramEqualizationImageFilterTest01
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${PROJECT_NAME}
    ${input_image}
    AdaptiveHistogramEqualizationImageFilterTest01.png
    ${alpha01}
    ${beta01}
    ${radius01}
  )
add_test(NAME AdaptiveHistogramEqualizationImageFilterTest02
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${PROJECT_NAME}
    ${input_image}
    AdaptiveHistogramEqualizationImageFilterTest02.png
    ${alpha02}
    ${beta02}
    ${radius02}
  )
add_test(NAME AdaptiveHistogramEqualizationImageFilterTest03
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${PROJECT_NAME}
    ${input_image}
    AdaptiveHistogramEqualizationImageFilterTest03.png
    ${alpha03}
    ${beta03}
    ${radius03}
  )
add_test(NAME AdaptiveHistogramEqualizationImageFilterTest04
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${PROJECT_NAME}
    ${input_image}
    AdaptiveHistogramEqualizationImageFilterTest04.png
    ${alpha04}
    ${beta04}
    ${radius01}
  )
 add_test(NAME AdaptiveHistogramEqualizationImageFilterTest05
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${PROJECT_NAME}
    ${input_image}
    AdaptiveHistogramEqualizationImageFilterTest05.png
    ${alpha05}
    ${beta05}
    ${radius02}
  )
  add_test(NAME AdaptiveHistogramEqualizationImageFilterTest06
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${PROJECT_NAME}
    ${input_image}
    AdaptiveHistogramEqualizationImageFilterTest06.png
    ${alpha05}
    ${beta02}
    ${radius04}
    )

# Not supported in itk 5.1.0
if(0)
if(ITK_WRAP_PYTHON)
  add_test(NAME AdaptiveHistogramEqualizationImageFilterTest01Python
    COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/Code.py
      ${input_image}
      AdaptiveHistogramEqualizationImageFilterTest01Python.png
      ${alpha01}
      ${beta01}
      ${radius01}
    )
  add_test(NAME AdaptiveHistogramEqualizationImageFilterTest02Python
    COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/Code.py
      ${input_image}
      AdaptiveHistogramEqualizationImageFilterTest02Python.png
      ${alpha02}
      ${beta02}
      ${radius02}
    )
  add_test(NAME AdaptiveHistogramEqualizationImageFilterTest03Python
    COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/Code.py
      ${input_image}
      AdaptiveHistogramEqualizationImageFilterTest03Python.png
      ${alpha03}
      ${beta03}
      ${radius03}
    )
  add_test(NAME AdaptiveHistogramEqualizationImageFilterTest04Python
    COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/Code.py
      ${input_image}
      AdaptiveHistogramEqualizationImageFilterTest04Python.png
      ${alpha04}
      ${beta04}
      ${radius01}
    )
  add_test(NAME AdaptiveHistogramEqualizationImageFilterTest05Python
    COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/Code.py
      ${input_image}
      AdaptiveHistogramEqualizationImageFilterTest05Python.png
      ${alpha05}
      ${beta05}
      ${radius02}
    )
  add_test(NAME AdaptiveHistogramEqualizationImageFilterTest06Python
    COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/Code.py
      ${input_image}
      AdaptiveHistogramEqualizationImageFilterTest06Python.png
      ${alpha05}
      ${beta02}
      ${radius04}
    )
endif()
endif()
