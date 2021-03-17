cmake_minimum_required(VERSION 3.10.2)

project( ApplyAccumulateImageFilter )

find_package( ITK REQUIRED )
include( ${ITK_USE_FILE} )

add_executable( ApplyAccumulateImageFilter Code.cxx )
target_link_libraries( ApplyAccumulateImageFilter ${ITK_LIBRARIES} )

install( TARGETS ApplyAccumulateImageFilter
  DESTINATION bin/ITKSphinxExamples/Filtering/ImageStatistics
  COMPONENT Runtime
  )

install( FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKSphinxExamples/Code/Filtering/ImageStatistics/ApplyAccumulateImageFilter
  COMPONENT Code
  )

enable_testing()

foreach( i RANGE 0 2 )
  add_test( NAME ApplyAccumulateImageFilterTest${i}
    COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/ApplyAccumulateImageFilter
      ${CMAKE_CURRENT_BINARY_DIR}/HeadMRVolume.mha
      ${CMAKE_CURRENT_BINARY_DIR}/ApplyAccumulateImageFilterTestOutput${i}.mha
      ${i}
  )
endforeach()
