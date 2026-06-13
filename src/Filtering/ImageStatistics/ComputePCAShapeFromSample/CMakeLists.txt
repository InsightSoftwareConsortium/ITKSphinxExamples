cmake_minimum_required(VERSION 3.22.1)

project(ComputePCAShapeFromSample)

find_package(ITK REQUIRED)
itk_generate_factory_registration()


add_executable(${PROJECT_NAME} Code.cxx)
target_link_libraries(${PROJECT_NAME}
  PRIVATE
    ITK::ITKImageIO
    ITK::ITKAnisotropicSmoothingModule
    ITK::ITKCommonModule
    ITK::ITKFastMarchingModule
    ITK::ITKImageGradientModule
    ITK::ITKImageGridModule
    ITK::ITKImageIntensityModule
    ITK::ITKImageStatisticsModule
    ITK::ITKLevelSetsModule
    ITK::ITKOptimizersModule
    ITK::ITKSignedDistanceFunctionModule
    ITK::ITKSpatialFunctionModule
    ITK::ITKStatisticsModule
    ITK::ITKThresholdingModule
    ITK::ITKTransformModule
)

install(TARGETS ${PROJECT_NAME}
  DESTINATION bin/ITKSphinxExamples/Filtering/ImageStatistics
  COMPONENT Runtime
  )

install(FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKSphinxExamples/Code/Filtering/ImageStatistics/ComputePCAShapeFromSample/
  COMPONENT Code
  )


enable_testing()
add_test(NAME ComputePCAShapeFromSampleTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${PROJECT_NAME})
