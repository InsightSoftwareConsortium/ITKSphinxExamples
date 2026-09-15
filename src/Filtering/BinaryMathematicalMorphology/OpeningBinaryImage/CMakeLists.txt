cmake_minimum_required(VERSION 3.22.1)

project(OpeningBinaryImage)

find_package(ITK REQUIRED)
itk_generate_factory_registration()

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
      ITK::ITKImageIO
      ITK::ITKBinaryMathematicalMorphologyModule
      ITK::ITKCommonModule
      ITK::ITKImageIntensityModule
      ITK::ITKMathematicalMorphologyModule
      ITK::ITKVtkGlueModule
      ${VTK_LIBRARIES}
  )

  vtk_module_autoinit(
    TARGETS OpeningBinaryImage
    MODULES ${VTK_LIBRARIES}
  )
else()
  add_executable(${PROJECT_NAME} Code.cxx)
  target_link_libraries(
    ${PROJECT_NAME}
    PRIVATE
      ITK::ITKImageIO
      ITK::ITKBinaryMathematicalMorphologyModule
      ITK::ITKCommonModule
      ITK::ITKImageIntensityModule
      ITK::ITKMathematicalMorphologyModule
  )
endif()

install(
  TARGETS
    ${PROJECT_NAME}
  DESTINATION bin/ITKSphinxExamples/Filtering/BinaryMathematicalMorphology
  COMPONENT Runtime
)

install(
  FILES
    Code.cxx
    CMakeLists.txt
  DESTINATION
    share/ITKSphinxExamples/Code/Filtering/BinaryMathematicalMorphology/OpeningBinaryImage/
  COMPONENT Code
)

enable_testing()
add_test(
  NAME OpeningBinaryImageTest
  COMMAND
    ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${PROJECT_NAME}
)
