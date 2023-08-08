cmake_minimum_required(VERSION 3.16.3)

project(ComputeMeanSquareBetweenTwoImages)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})


add_executable(${PROJECT_NAME} Code.cxx)
target_link_libraries(${PROJECT_NAME} ${ITK_LIBRARIES})

install(TARGETS ${PROJECT_NAME}
  DESTINATION bin/ITKSphinxExamples/Registration/Common
  COMPONENT Runtime
  )

install(FILES Code.cxx Code.py CMakeLists.txt
  DESTINATION share/ITKSphinxExamples/Code/Registration/Common/ComputeMeanSquareBetweenTwoImages/
  COMPONENT Code
  )


enable_testing()
add_test(NAME ComputeMeanSquareBetweenTwoImagesTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${PROJECT_NAME}
    Yinyang.png
    Gourds.png)
    
    
if(ITK_WRAP_PYTHON)
  add_test(NAME ComputeMeanSquareBetweenTwoImagesTestPython
    COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/Code.py
	Yinyang.png
	Gourds.png)
endif()
