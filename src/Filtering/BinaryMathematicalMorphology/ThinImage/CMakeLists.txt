cmake_minimum_required(VERSION 3.22.1)

project(ThinImage)

find_package(ITK REQUIRED)
itk_generate_factory_registration()


add_executable(${PROJECT_NAME} Code.cxx)
target_link_libraries(${PROJECT_NAME}
  PRIVATE
    ITK::ITKImageIO
    ITK::ITKBinaryMathematicalMorphologyModule
    ITK::ITKCommonModule
    ITK::ITKImageIntensityModule
)

install(TARGETS ${PROJECT_NAME}
  DESTINATION bin/ITKSphinxExamples/Filtering/BinaryMathematicalMorphology
  COMPONENT Runtime
  )

install(FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKSphinxExamples/Code/Filtering/BinaryMathematicalMorphology/ThinImage/
  COMPONENT Code
  )


enable_testing()
add_test(NAME ThinImageTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${PROJECT_NAME})

if(ITK_WRAP_PYTHON)
add_test(NAME ThinImageTestPython
  COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/Code.py)
endif()
