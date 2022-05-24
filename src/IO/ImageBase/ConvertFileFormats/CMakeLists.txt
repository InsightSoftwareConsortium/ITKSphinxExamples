cmake_minimum_required(VERSION 3.16.3)

project(ConvertFileFormats)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})

add_executable(${PROJECT_NAME} Code.cxx)
target_link_libraries(${PROJECT_NAME} ${ITK_LIBRARIES})

install(TARGETS ${PROJECT_NAME}
  DESTINATION bin/ITKSphinxExamples/IO/ImageBase
  COMPONENT Runtime
  )

install(FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKSphinxExamples/Code/IO/ImageBase/ConvertFileFormats
  COMPONENT Code
  )

enable_testing()
add_test(NAME ConvertFileFormatsTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${PROJECT_NAME}
    ${CMAKE_CURRENT_BINARY_DIR}/Gourds.png
    ${CMAKE_CURRENT_BINARY_DIR}/Output.jpg
  )
