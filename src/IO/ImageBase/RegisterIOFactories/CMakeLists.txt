cmake_minimum_required(VERSION 3.22.1)

project(RegisterIOFactories)

find_package(ITK REQUIRED)
# Registering the IO classes manually is usually not necessary,
# unless this variable is set before calling
#   "include(${ITK_USE_FILE})"
set(ITK_NO_IMAGEIO_FACTORY_REGISTER_MANAGER 1)
include(${ITK_USE_FILE})

add_executable(${PROJECT_NAME} Code.cxx)
target_link_libraries(${PROJECT_NAME} ${ITK_LIBRARIES})

install(TARGETS ${PROJECT_NAME}
  DESTINATION bin/ITKSphinxExamples/IO/ImageBase
  COMPONENT Runtime
  )

install(FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKSphinxExamples/Code/IO/ImageBase/RegisterIOFactories
  COMPONENT Code
  )

enable_testing()
add_test(NAME RegisterIOFactoriesTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${PROJECT_NAME}
    ${CMAKE_CURRENT_BINARY_DIR}/HeadMRVolume.mha
    ${CMAKE_CURRENT_BINARY_DIR}/Yinyang.png
  )
