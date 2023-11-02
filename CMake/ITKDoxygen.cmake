set(ITKDoxygen_DIR ${CMAKE_BINARY_DIR}/ITKDoxygen)
set(ITKDoxygen_TEMP_DIR ${CMAKE_BINARY_DIR}/ITKDoxygen-TEMP)


add_custom_command(OUTPUT ${ITKDoxygen_DIR}/index.html
  COMMAND ${CMAKE_COMMAND} -DITKDoxygen_TEMP_DIR="${ITKDoxygen_TEMP_DIR}" -P ${ITKSphinxExamples_SOURCE_DIR}/CMake/DownloadDoxygen.cmake
  COMMAND ${CMAKE_COMMAND} -E chdir "${ITKDoxygen_TEMP_DIR}" ${CMAKE_COMMAND} -E tar xzf "${ITKDoxygen_TEMP_DIR}/itk-doxygen.tar.gz"
  COMMAND ${CMAKE_COMMAND} -E rename "${ITKDoxygen_TEMP_DIR}/html" "${ITKDoxygen_DIR}"
  COMMAND ${CMAKE_COMMAND} -E remove_directory "${ITKDoxygen_TEMP_DIR}"
  COMMENT "Downloading and unpacking the Doxygen "
  )

add_custom_target(ITKDoxygen ${CMAKE_COMMAND} -E echo "Finished obtaining Doxygen"
  DEPENDS ${ITKDoxygen_DIR}/index.html)

