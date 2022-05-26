cmake_minimum_required(VERSION 3.16.3)

project(RegisterTransformWithTransformFactory)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})


add_executable(${PROJECT_NAME} Code.cxx)
target_link_libraries(${PROJECT_NAME} ${ITK_LIBRARIES})

install(TARGETS ${PROJECT_NAME}
  DESTINATION bin/ITKSphinxExamples/IO/TransformFactory
  COMPONENT Runtime
  )

install(FILES Code.cxx CMakeLists.txt Code.py
  DESTINATION share/ITKSphinxExamples/Code/IO/TransformFactory/RegisterTransformWithTransformFactory/
  COMPONENT Code
  )


enable_testing()
add_test(NAME RegisterTransformWithTransformFactoryTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${PROJECT_NAME})
