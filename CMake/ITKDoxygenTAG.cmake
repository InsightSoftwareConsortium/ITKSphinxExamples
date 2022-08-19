set( ITKDoxygenTAG_DIR ${CMAKE_BINARY_DIR}/ITKDoxygenTAG )
set( ITKDoxygenTAG_TEMP_DIR ${CMAKE_BINARY_DIR}/ITKDoxygenTAG-TEMP )

find_package(Python3 COMPONENTS Interpreter REQUIRED)

add_custom_command( OUTPUT ${ITKDoxygenTAG_DIR}/InsightDoxygen.tag
  COMMAND ${CMAKE_COMMAND} -DITKDoxygenTAG_TEMP_DIR="${ITKDoxygenTAG_TEMP_DIR}" -P ${CMAKE_CURRENT_SOURCE_DIR}/CMake/DownloadDoxygenTAG.cmake
  COMMAND ${Python3_EXECUTABLE} "${ITKSphinxExamples_SOURCE_DIR}/Utilities/GUnzip.py" "${ITKDoxygenTAG_TEMP_DIR}/InsightDoxygen.tag.gz"

  COMMAND ${CMAKE_COMMAND} -E remove_directory "${ITKDoxygenTAG_DIR}"
  COMMAND ${CMAKE_COMMAND} -E rename "${ITKDoxygenTAG_TEMP_DIR}" "${ITKDoxygenTAG_DIR}"
  COMMAND ${CMAKE_COMMAND} -E remove_directory "${ITKDoxygenTAG_TEMP_DIR}"

  COMMENT "Downloading and unpacking the Doxygen TAG"
  )
add_custom_target( ITKDoxygenTAG ${CMAKE_COMMAND} -E echo "Finished obtaining Doxygen TAG"
  DEPENDS ${ITKDoxygenTAG_DIR}/InsightDoxygen.tag )

