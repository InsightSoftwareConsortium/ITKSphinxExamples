cmake_minimum_required(VERSION 3.10.2)

project(ResamleDICOMSeries)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})


add_executable(ResamleDICOMSeries Code.cxx)
target_link_libraries(ResamleDICOMSeries ${ITK_LIBRARIES})

install(TARGETS ResamleDICOMSeries
  DESTINATION bin/ITKExamples/IO/GDCM
  COMPONENT Runtime
  )

install(FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKExamples/Code/IO/GDCM/ResamleDICOMSeries/
  COMPONENT Code
  )


enable_testing()
add_test(NAME ResamleDICOMSeriesTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/ResamleDICOMSeries

  )

