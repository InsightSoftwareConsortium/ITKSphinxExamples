cmake_minimum_required(VERSION 3.10.2)

project(ProcessA2DSliceOfA3DImage)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})


add_executable(ProcessA2DSliceOfA3DImage Code.cxx)
target_link_libraries(ProcessA2DSliceOfA3DImage ${ITK_LIBRARIES})

install(TARGETS ProcessA2DSliceOfA3DImage
  DESTINATION bin/ITKSphinxExamples/Core/Common
  COMPONENT Runtime
  )

install(FILES Code.cxx CMakeLists.txt Code.py
  DESTINATION share/ITKSphinxExamples/Code/Core/Common/ProcessA2DSliceOfA3DImage/
  COMPONENT Code
  )


enable_testing()
set(input_image ${CMAKE_CURRENT_BINARY_DIR}/105769fixed_B.nii.gz)
set(output_image Output.mha)
set(test_options 232) # slice number

add_test(NAME ProcessA2DSliceOfA3DImageTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/ProcessA2DSliceOfA3DImage
    ${input_image}
    ${output_image}
    ${test_options}
  )

if(ITK_WRAP_PYTHON)
  find_package(PythonInterp REQUIRED)
  string(REPLACE . "Python." output_image "${output_image}")
  add_test(NAME ProcessA2DSliceOfA3DImageTestPython
    COMMAND ${PYTHON_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/Code.py
      ${input_image}
      ${output_image}
      ${test_options}
    )
endif()
