cmake_minimum_required(VERSION 3.22.1)

project(DisplayITKImage)

find_package(ITK REQUIRED)
itk_generate_factory_registration()


add_executable(${PROJECT_NAME} Code.cxx)
target_link_libraries(${PROJECT_NAME}
  PRIVATE
    ITK::ITKImageIO
    ITK::ITKCommonModule
    ITK::ITKVtkGlueModule
)

install(TARGETS ${PROJECT_NAME}
  DESTINATION bin/ITKSphinxExamples/Remote/WikiExamples
  COMPONENT Runtime
  )

install(FILES Code.cxx CMakeLists.txt
  DESTINATION share/ITKSphinxExamples/Code/Remote/WikiExamples/DisplayITKImage/
  COMPONENT Code
  )


enable_testing()
add_test(NAME DisplayITKImageTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${PROJECT_NAME})
