cmake_minimum_required(VERSION 3.10.2)

project( FilterImageInFourierDomain )

find_package( ITK REQUIRED )
include( ${ITK_USE_FILE} )

add_executable( FilterImageInFourierDomain Code.cxx )
target_link_libraries( FilterImageInFourierDomain ${ITK_LIBRARIES} )

install( TARGETS FilterImageInFourierDomain
  DESTINATION bin/ITKExamples/Filtering/FFT
  COMPONENT Runtime
  )

install( FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKExamples/Code/Filtering/FFT/FilterImageInFourierDomain
  COMPONENT Code
  )

enable_testing()
add_test( NAME FilterImageInFourierDomainTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/FilterImageInFourierDomain
    ${CMAKE_CURRENT_BINARY_DIR}/HeadMRVolume.mha
    Output.mha
  )
