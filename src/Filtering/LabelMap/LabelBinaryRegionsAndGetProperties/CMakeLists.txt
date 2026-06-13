cmake_minimum_required(VERSION 3.22.1)

project(LabelBinaryRegionsAndGetProperties)

find_package(ITK REQUIRED)
itk_generate_factory_registration()


add_executable(${PROJECT_NAME} Code.cxx)
target_link_libraries(${PROJECT_NAME}
  PRIVATE
    ITK::ITKImageIO
    ITK::ITKCommonModule
    ITK::ITKLabelMapModule
)

install(TARGETS ${PROJECT_NAME}
  DESTINATION bin/ITKSphinxExamples/Filtering/LabelMap
  COMPONENT Runtime
  )

install(FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKSphinxExamples/Code/Filtering/LabelMap/LabelBinaryRegionsAndGetProperties/
  COMPONENT Code
  )


enable_testing()
add_test(NAME LabelBinaryRegionsAndGetPropertiesTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${PROJECT_NAME})
