cmake_minimum_required(VERSION 3.16.3)

set(input_image ${CMAKE_CURRENT_BINARY_DIR}/HeadMRVolume.mha)
set(output_image Output)

project(GenerateSlicesFromVolume)

find_package(ITK REQUIRED
  COMPONENTS
  ITKCommon
  ITKIOImageBase
  ITKImageIntensity
  ITKIOPNG
  ITKIOMeta
  )
include(${ITK_USE_FILE})

add_executable(${PROJECT_NAME} Code.cxx)
target_link_libraries(${PROJECT_NAME} ${ITK_LIBRARIES})

install(TARGETS ${PROJECT_NAME}
  DESTINATION bin/ITKSphinxExamples/IO/ImageBase/
  COMPONENT Runtime
  )

install(FILES Code.cxx CMakeLists.txt Code.py
  DESTINATION share/ITKSphinxExamples/Code/IO/ImageBase/GenerateSlicesFromVolume
  COMPONENT Code
)

enable_testing()

add_test(NAME GenerateSlicesFromVolumeTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${PROJECT_NAME}
    ${input_image}
    ${output_image}
)

if(ITK_WRAP_PYTHON)
  add_test(NAME GenerateSlicesFromVolumeTestPython
    COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/Code.py
      ${input_image}
      ${output_image}
      "Python.png"
    )
endif()
