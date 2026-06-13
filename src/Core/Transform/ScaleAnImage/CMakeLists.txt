cmake_minimum_required(VERSION 3.22.1)

project(ScaleAnImage)

find_package(ITK REQUIRED)
itk_generate_factory_registration()


add_executable(${PROJECT_NAME} Code.cxx)
target_link_libraries(${PROJECT_NAME}
  PRIVATE
    ITK::ITKImageIO
    ITK::ITKCommonModule
    ITK::ITKImageGridModule
    ITK::ITKTransformModule
)

install(TARGETS ${PROJECT_NAME}
  DESTINATION bin/ITKSphinxExamples/Core/Transform
  COMPONENT Runtime
  )

install(FILES Code.cxx Code.py CMakeLists.txt
  DESTINATION share/ITKSphinxExamples/Code/Core/Transform/ScaleAnImage/
  COMPONENT Code
  )


enable_testing()

add_test(NAME ScaleAnImageTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${PROJECT_NAME}
    ${CMAKE_CURRENT_BINARY_DIR}/ScaleAnImageInput.png
    ${CMAKE_CURRENT_BINARY_DIR}/ScaleAnImageOutput.png
  )

if(ITK_WRAP_PYTHON)
add_test(NAME ScaleAnImageTestPython
COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/Code.py
    ${CMAKE_CURRENT_BINARY_DIR}/ScaleAnImageInput.png
    ${CMAKE_CURRENT_BINARY_DIR}/ScaleAnImageOutputPython.png)
endif()
