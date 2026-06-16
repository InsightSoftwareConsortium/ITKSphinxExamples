cmake_minimum_required(VERSION 3.22.1)

project(GlobalRegistrationTwoImagesBSpline)

find_package(ITK REQUIRED)
itk_generate_factory_registration()

if(ENABLE_QUICKVIEW)
  find_package(
    VTK
    REQUIRED
    COMPONENTS
      ${_vtk_prefix}RenderingCore
      ${_vtk_prefix}RenderingGL2PSOpenGL2
  )
  if(VTK_VERSION VERSION_LESS "8.90.0")
    include(${VTK_USE_FILE})
  endif()

  add_executable(${PROJECT_NAME} Code.cxx)
  target_link_libraries(
    ${PROJECT_NAME}
    PRIVATE
      ITK::ITKImageIO
      ITK::ITKCommonModule
      ITK::ITKImageFilterBaseModule
      ITK::ITKImageGridModule
      ITK::ITKOptimizersModule
      ITK::ITKRegistrationCommonModule
      ITK::ITKSpatialObjectsModule
      ITK::ITKTransformModule
      ${VTK_LIBRARIES}
  )

  if(NOT VTK_VERSION VERSION_LESS "8.90.0")
    vtk_module_autoinit(
      TARGETS GlobalRegistrationTwoImagesBSpline
      MODULES ${VTK_LIBRARIES}
    )
  endif()
else()
  add_executable(${PROJECT_NAME} Code.cxx)
  target_link_libraries(
    ${PROJECT_NAME}
    PRIVATE
      ITK::ITKImageIO
      ITK::ITKCommonModule
      ITK::ITKImageFilterBaseModule
      ITK::ITKImageGridModule
      ITK::ITKOptimizersModule
      ITK::ITKRegistrationCommonModule
      ITK::ITKSpatialObjectsModule
      ITK::ITKTransformModule
  )
endif()

install(
  TARGETS
    ${PROJECT_NAME}
  DESTINATION bin/ITKSphinxExamples/Core/Transform
  COMPONENT Runtime
)

install(
  FILES
    Code.cxx
    CMakeLists.txt
  DESTINATION
    share/ITKSphinxExamples/Code/Core/Transform/GlobalRegistrationTwoImagesBSpline/
  COMPONENT Code
)

enable_testing()
add_test(
  NAME GlobalRegistrationTwoImagesBSplineTest
  COMMAND
    ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${PROJECT_NAME}
)
