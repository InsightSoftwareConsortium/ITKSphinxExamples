cmake_minimum_required(VERSION 3.22.1)

project(GlobalRegistrationTwoImagesAffine)

find_package(ITK REQUIRED)
itk_generate_factory_registration()


add_executable(${PROJECT_NAME} Code.cxx)
target_link_libraries(${PROJECT_NAME}
  PRIVATE
    ITK::ITKImageIO
    ITK::ITKCommonModule
    ITK::ITKImageFilterBaseModule
    ITK::ITKImageFunctionModule
    ITK::ITKImageGridModule
    ITK::ITKImageIntensityModule
    ITK::ITKOptimizersModule
    ITK::ITKRegistrationCommonModule
    ITK::ITKSpatialObjectsModule
    ITK::ITKTransformModule
)

install(TARGETS ${PROJECT_NAME}
  DESTINATION bin/ITKSphinxExamples/Core/Transform
  COMPONENT Runtime
  )

install(FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKSphinxExamples/Code/Core/Transform/GlobalRegistrationTwoImagesAffine/
  COMPONENT Code
  )


enable_testing()
add_test(NAME GlobalRegistrationTwoImagesAffineTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${PROJECT_NAME})
