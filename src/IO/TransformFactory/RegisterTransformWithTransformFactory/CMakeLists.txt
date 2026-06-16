cmake_minimum_required(VERSION 3.22.1)

project(RegisterTransformWithTransformFactory)

find_package(ITK REQUIRED)
itk_generate_factory_registration()

add_executable(${PROJECT_NAME} Code.cxx)
target_link_libraries(
  ${PROJECT_NAME}
  PRIVATE
    ITK::ITKTransformIO
    ITK::ITKTransformModule
    ITK::ITKTransformFactoryModule
)

install(
  TARGETS
    ${PROJECT_NAME}
  DESTINATION bin/ITKSphinxExamples/IO/TransformFactory
  COMPONENT Runtime
)

install(
  FILES
    Code.cxx
    CMakeLists.txt
    Code.py
  DESTINATION
    share/ITKSphinxExamples/Code/IO/TransformFactory/RegisterTransformWithTransformFactory/
  COMPONENT Code
)

enable_testing()
add_test(
  NAME RegisterTransformWithTransformFactoryTest
  COMMAND
    ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${PROJECT_NAME}
)
