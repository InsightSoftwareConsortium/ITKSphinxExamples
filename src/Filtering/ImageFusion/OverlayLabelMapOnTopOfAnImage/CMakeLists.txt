cmake_minimum_required(VERSION 3.16.3)
project(OverlayLabelMapOnTopOfAnImage)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})

add_executable(${PROJECT_NAME} Code.cxx)
target_link_libraries(${PROJECT_NAME} ${ITK_LIBRARIES})

install(TARGETS ${PROJECT_NAME}
  DESTINATION bin/ITKSphinxExamples/Filtering/ImageFusion
  COMPONENT Runtime
  )

install(FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKSphinxExamples/Code/Filtering/ImageFusion/OverlayLabelMapOnTopOfAnImage
  COMPONENT Code
  )


enable_testing()

set(input_images
  ${CMAKE_CURRENT_BINARY_DIR}/Gourds.png
  ${CMAKE_CURRENT_BINARY_DIR}/label.png
  )
set(output_image Output.png)

add_test(NAME OverlayLabelMapOnTopOfAnImageTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${PROJECT_NAME}
    ${input_images}
    ${output_image}
  )

if(ITK_WRAP_PYTHON)
  string(REPLACE . "Python." output_image "${output_image}")
  add_test(NAME OverlayLabelMapOnTopOfAnImageTestPython
    COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/Code.py
      ${input_images}
      ${output_image}
    )
endif()
