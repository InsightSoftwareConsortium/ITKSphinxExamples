cmake_minimum_required(VERSION 3.10.2)

project(ResampleDICOMSeries)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})


add_executable(ResampleDICOMSeries Code.cxx)
target_link_libraries(ResampleDICOMSeries ${ITK_LIBRARIES})

install(TARGETS ResampleDICOMSeries
  DESTINATION bin/ITKExamples/IO/GDCM
  COMPONENT Runtime
  )

install(FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKExamples/Code/IO/GDCM/ResampleDICOMSeries/
  COMPONENT Code
  )


enable_testing()
add_test(NAME ResampleDICOMSeriesTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/ResampleDICOMSeries

  )
