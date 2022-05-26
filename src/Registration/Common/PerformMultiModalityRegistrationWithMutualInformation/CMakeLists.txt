cmake_minimum_required(VERSION 3.16.3)

project(PerformMultiModalityRegistrationWithMutualInformation)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})

add_executable(${PROJECT_NAME} Code.cxx)
target_link_libraries(${PROJECT_NAME} ${ITK_LIBRARIES})

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
