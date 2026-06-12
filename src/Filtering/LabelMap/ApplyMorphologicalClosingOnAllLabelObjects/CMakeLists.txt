cmake_minimum_required(VERSION 3.22.1)
project(ApplyMorphologicalClosingOnAllLabelObjects)

find_package(ITK REQUIRED)
itk_generate_factory_registration()

add_executable(${PROJECT_NAME} Code.cxx)
target_link_libraries(${PROJECT_NAME}
  PRIVATE
    ITK::ITKImageIO
    ITK::ITKBinaryMathematicalMorphologyModule
    ITK::ITKLabelMapModule
    ITK::ITKMathematicalMorphologyModule
)

install(TARGETS ${PROJECT_NAME}
  DESTINATION bin/ITKSphinxExamples/Filtering/LabelMap
  COMPONENT Runtime
  )

install(FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKSphinxExamples/Code/Filtering/LabelMap/ApplyMorphologicalClosingOnAllLabelObjects
  COMPONENT Code
  )

enable_testing()
add_test(NAME ApplyMorphologicalClosingOnAllLabelObjectsTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${PROJECT_NAME}
    ${CMAKE_CURRENT_BINARY_DIR}/2th_cthead1.png
    Output.png
    1
)
