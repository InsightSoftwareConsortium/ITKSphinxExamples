cmake_minimum_required(VERSION 3.22.1)

project(IterateWithNeighborhoodWithoutAccess)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})


add_executable(${PROJECT_NAME} Code.cxx)
target_link_libraries(${PROJECT_NAME} ${ITK_LIBRARIES})

install(TARGETS ${PROJECT_NAME}
  DESTINATION bin/ITKSphinxExamples/Core/Common
  COMPONENT Runtime
  )

install(FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKSphinxExamples/Code/Core/Common/IterateWithNeighborhoodWithoutAccess/
  COMPONENT Code
  )


enable_testing()
set(input_image Yinyang.png)

add_test(NAME IterateWithNeighborhoodWithoutAccessTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${PROJECT_NAME}
    ${input_image})
