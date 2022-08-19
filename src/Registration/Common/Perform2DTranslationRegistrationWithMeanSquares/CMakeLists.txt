cmake_minimum_required(VERSION 3.16.3)

set(input_image1 ${CMAKE_CURRENT_BINARY_DIR}/BrainProtonDensitySliceBorder20.png)
set(input_image2 ${CMAKE_CURRENT_BINARY_DIR}/BrainProtonDensitySliceShifted13x17y.png)
set(output_image1 Output.png)
set(output_image2 ImageRegistration1DifferenceAfter.png)
set(output_image3 ImageRegistration1DifferenceBefore.png)

project(Perform2DTranslationRegistrationWithMeanSquares)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})

add_executable(${PROJECT_NAME} Code.cxx)
target_link_libraries(${PROJECT_NAME} ${ITK_LIBRARIES})

install(TARGETS ${PROJECT_NAME}
  DESTINATION bin/ITKSphinxExamples/Registration/Common
  COMPONENT Runtime
  )

install(FILES Code.cxx CMakeLists.txt Code.py
  DESTINATION share/ITKSphinxExamples/Code/Registration/Common/Perform2DTranslationRegistrationWithMeanSquares
  COMPONENT Code
  )

enable_testing()
add_test(NAME Perform2DTranslationRegistrationWithMeanSquaresTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${PROJECT_NAME}
  ${input_image1}
  ${input_image2}
  ${output_image1}
  ${output_image2}
  ${output_image3}
  )

if(ITK_WRAP_PYTHON)
  string(REPLACE . "Python." output_image1 "${output_image1}")
  string(REPLACE . "Python." output_image2 "${output_image2}")
  string(REPLACE . "Python." output_image3 "${output_image3}")
  add_test(NAME Perform2DTranslationRegistrationWithMeanSquaresTestPython
    COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/Code.py
    ${input_image1}
    ${input_image2}
    ${output_image1}
    ${output_image2}
    ${output_image3}
    )
endif()
