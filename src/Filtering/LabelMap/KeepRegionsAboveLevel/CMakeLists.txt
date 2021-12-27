cmake_minimum_required(VERSION 3.16.3)

project(KeepRegionsAboveLevel)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})


add_executable(KeepRegionsAboveLevel Code.cxx)
target_link_libraries(KeepRegionsAboveLevel ${ITK_LIBRARIES})

install(TARGETS KeepRegionsAboveLevel
  DESTINATION bin/ITKSphinxExamples/Filtering/LabelMap
  COMPONENT Runtime
  )

install(FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKSphinxExamples/Code/Filtering/LabelMap/KeepRegionsAboveLevel/
  COMPONENT Code
  )


enable_testing()
add_test(NAME KeepRegionsAboveLevelTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/KeepRegionsAboveLevel
  )
