cmake_minimum_required(VERSION 3.16.3)

project(DeformAVolumeWithAThinPlateSpline)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})

add_executable(DeformAVolumeWithAThinPlateSpline Code.cxx)
target_link_libraries(DeformAVolumeWithAThinPlateSpline ${ITK_LIBRARIES})

install(TARGETS DeformAVolumeWithAThinPlateSpline
  DESTINATION bin/ITKSphinxExamples/Core/Transform
  COMPONENT Runtime
)

install(FILES Code.cxx CMakeLists.txt Code.py
  DESTINATION share/ITKSphinxExamples/Code/Core/Transform/DeformAVolumeWithAThinPlateSpline
  COMPONENT Code
)

enable_testing()

set(source_landmarks ${CMAKE_CURRENT_BINARY_DIR}/SourceLandmarks.vtk)
set(target_landmarks ${CMAKE_CURRENT_BINARY_DIR}/TargetLandmarks.vtk)
set(input_image ${CMAKE_CURRENT_BINARY_DIR}/brainweb165a10f17.mha)
set(deformed_image DeformedImage.mha)
set(checkerboard_image CheckerBoardImage.mha)

add_test(NAME DeformAVolumeWithAThinPlateSplineTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/DeformAVolumeWithAThinPlateSpline
  ${source_landmarks}
  ${target_landmarks}
  ${input_image}
  ${deformed_image}
  ${checkerboard_image}
)

if(ITK_WRAP_PYTHON)
  find_package(Python3 ${PYTHON_REQUIRED_VERSION} COMPONENTS Interpreter)
  string(REPLACE . "Python." deformed_image "${deformed_image}")
  add_test(NAME DeformAVolumeWithAThinPlateSplineTestPython
    COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/Code.py
      ${source_landmarks}
      ${target_landmarks}
      ${input_image}
      ${deformed_image}
      ${checkerboard_image}
    )
endif()
