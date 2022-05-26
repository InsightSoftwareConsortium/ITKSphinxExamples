cmake_minimum_required(VERSION 3.16.3)

project(CovariantVectorDotProduct)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})

add_executable(${PROJECT_NAME} Code.cxx)
target_link_libraries(${PROJECT_NAME} ${ITK_LIBRARIES})

install(TARGETS ${PROJECT_NAME}
  DESTINATION bin/ITKSphinxExamples/Core/Common
  COMPONENT Runtime
)

install(FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKSphinxExamples/Code/Core/Common/CovariantVectorDotProduct
  COMPONENT Code
)

enable_testing()
add_test(NAME CovariantVectorDotProductTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${PROJECT_NAME})
