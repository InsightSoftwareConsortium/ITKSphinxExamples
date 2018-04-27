cmake_minimum_required(VERSION 3.10.2)

project( ConvertRGBImageToGrayscaleImage )

find_package( ITK REQUIRED )
include( ${ITK_USE_FILE} )

add_executable( ConvertRGBImageToGrayscaleImage Code.cxx )
target_link_libraries( ConvertRGBImageToGrayscaleImage ${ITK_LIBRARIES} )

install( TARGETS ConvertRGBImageToGrayscaleImage
  DESTINATION bin/ITKExamples/Filtering/ImageIntensity
  COMPONENT Runtime
)

install( FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKExamples/Code/Filtering/ImageIntensity/ConvertRGBImageToGrayscaleImage
  COMPONENT Code
)

enable_testing()
set(input_image ${CMAKE_CURRENT_BINARY_DIR}/itk_eg_logo.png)
set(output_image Output.png)

add_test( NAME ConvertRGBImageToGrayscaleImageTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/ConvertRGBImageToGrayscaleImage
    ${input_image}
    ${output_image}
)

if(ITK_WRAP_PYTHON)
  find_package(PythonInterp REQUIRED)
  string(REPLACE . "Python." output_image "${output_image}")
  add_test(NAME ConvertRGBImageToGrayscaleImageTestPython
    COMMAND ${PYTHON_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/Code.py
      ${input_image}
      ${output_image}
    )
endif()
