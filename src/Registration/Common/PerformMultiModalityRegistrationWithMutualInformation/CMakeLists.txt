cmake_minimum_required( VERSION 2.8.6 )

project( PerformMultiModalityRegistrationWithMutualInformation )

find_package( ITK REQUIRED )
include( ${ITK_USE_FILE} )

add_executable( PerformMultiModalityRegistrationWithMutualInformation Code.cxx )
target_link_libraries( PerformMultiModalityRegistrationWithMutualInformation ${ITK_LIBRARIES} )

install( TARGETS PerformMultiModalityRegistrationWithMutualInformation
  DESTINATION bin/ITKExamples/Registration/Common
  COMPONENT Runtime
  )

install( FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKExamples/Code/Registration/Common/PerformMultiModalityRegistrationWithMutualInformation
  COMPONENT Code
  )

enable_testing()
add_test( NAME PerformMultiModalityRegistrationWithMutualInformationTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/PerformMultiModalityRegistrationWithMutualInformation
  BrainT1SliceBorder20.png
  BrainProtonDensitySliceShifted13x17y.png
  Output.png
  PerformMultiModalityRegistrationWithMutualInformationCheckerboardBefore.png
  PerformMultiModalityRegistrationWithMutualInformationCheckerboardAfter.png
  )
set_tests_properties( PerformMultiModalityRegistrationWithMutualInformationTest PROPERTIES
  LABELS RUNS_LONG )
