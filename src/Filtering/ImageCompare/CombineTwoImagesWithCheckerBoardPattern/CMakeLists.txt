cmake_minimum_required(VERSION 3.16.3)

project(CombineTwoImagesWithCheckerBoardPattern)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})

add_executable(${PROJECT_NAME} Code.cxx)
target_link_libraries(${PROJECT_NAME} ${ITK_LIBRARIES})

install(TARGETS ${PROJECT_NAME}
  DESTINATION bin/ITKSphinxExamples/Filtering/ImageCompare
  COMPONENT Runtime
)

install(FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKSphinxExamples/Code/Filtering/ImageCompare/CombineTwoImagesWithCheckerBoardPattern
  COMPONENT Code
)

enable_testing()

set(output_image Output.png)

add_test(NAME CombineTwoImagesWithCheckerBoardPatternTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${PROJECT_NAME}
    ${output_image}
)

if(ITK_WRAP_PYTHON)
  string(REPLACE . "Python." output_image "${output_image}")
  add_test(NAME CombineTwoImagesWithCheckerBoardPatternTestPython
    COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/Code.py
      ${output_image}
  )
endif()
