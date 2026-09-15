cmake_minimum_required(VERSION 3.22.1)

project(ExtractBoundariesOfConnectedRegionsInBinaryImage)

find_package(ITK REQUIRED)

if(ENABLE_QUICKVIEW)
  find_package(
    VTK
    REQUIRED
    COMPONENTS
      RenderingCore
      RenderingGL2PSOpenGL2
  )

  add_executable(${PROJECT_NAME} Code.cxx)
  target_link_libraries(
    ${PROJECT_NAME}
    PRIVATE
      ITK::ITKCommonModule
      ITK::ITKImageLabelModule
      ITK::ITKVtkGlueModule
      ${VTK_LIBRARIES}
  )

  vtk_module_autoinit(
    TARGETS ExtractBoundariesOfConnectedRegionsInBinaryImage
    MODULES ${VTK_LIBRARIES}
  )
else()
  add_executable(${PROJECT_NAME} Code.cxx)
  target_link_libraries(
    ${PROJECT_NAME}
    PRIVATE
      ITK::ITKCommonModule
      ITK::ITKImageLabelModule
  )
endif()

install(
  TARGETS
    ${PROJECT_NAME}
  DESTINATION bin/ITKSphinxExamples/Filtering/ImageLabel
  COMPONENT Runtime
)

install(
  FILES
    Code.cxx
    CMakeLists.txt
  DESTINATION
    share/ITKSphinxExamples/Code/Filtering/ImageLabel/ExtractBoundariesOfConnectedRegionsInBinaryImage/
  COMPONENT Code
)

enable_testing()
add_test(
  NAME ExtractBoundariesOfConnectedRegionsInBinaryImageTest
  COMMAND
    ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${PROJECT_NAME}
)
