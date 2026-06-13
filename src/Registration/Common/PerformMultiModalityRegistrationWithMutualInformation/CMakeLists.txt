cmake_minimum_required(VERSION 3.22.1)

project(PerformMultiModalityRegistrationWithMutualInformation)

find_package(ITK REQUIRED)
itk_generate_factory_registration()

add_executable(${PROJECT_NAME} Code.cxx)
target_link_libraries(${PROJECT_NAME}
  PRIVATE
    ITK::ITKImageIO
    ITK::ITKCommonModule
    ITK::ITKImageCompareModule
    ITK::ITKImageFilterBaseModule
    ITK::ITKImageGridModule
    ITK::ITKImageIntensityModule
    ITK::ITKOptimizersModule
    ITK::ITKRegistrationCommonModule
    ITK::ITKSmoothingModule
    ITK::ITKTransformModule
)

install(TARGETS ${PROJECT_NAME}
  DESTINATION bin/ITKSphinxExamples/Registration/Common
  COMPONENT Runtime
  )

install(FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKSphinxExamples/Code/Registration/Common/PerformMultiModalityRegistrationWithMutualInformation
  COMPONENT Code
  )

enable_testing()
add_test(NAME PerformMultiModalityRegistrationWithMutualInformationTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${PROJECT_NAME}
  BrainT1SliceBorder20.png
  BrainProtonDensitySliceShifted13x17y.png
  Output.png
  PerformMultiModalityRegistrationWithMutualInformationCheckerboardBefore.png
  PerformMultiModalityRegistrationWithMutualInformationCheckerboardAfter.png
  )
set_tests_properties(PerformMultiModalityRegistrationWithMutualInformationTest PROPERTIES
  LABELS RUNS_LONG)
