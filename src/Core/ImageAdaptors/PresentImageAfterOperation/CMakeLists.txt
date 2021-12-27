cmake_minimum_required(VERSION 3.16.3)

project(PresentImageAfterOperation)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})


add_executable(PresentImageAfterOperation Code.cxx)
target_link_libraries(PresentImageAfterOperation ${ITK_LIBRARIES})

install(TARGETS PresentImageAfterOperation
  DESTINATION bin/ITKSphinxExamples/Core/ImageAdaptors
  COMPONENT Runtime
  )

install(FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKSphinxExamples/Code/Core/ImageAdaptors/PresentImageAfterOperation/
  COMPONENT Code
  )

enable_testing()
add_test(NAME PresentImageAfterOperationTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/PresentImageAfterOperation)

