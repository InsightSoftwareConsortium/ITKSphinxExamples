set( ITKDoxygenXML_DIR ${CMAKE_BINARY_DIR}/ITKDoxygenXML )
set( ITKDoxygenXML_TEMP_DIR ${CMAKE_BINARY_DIR}/ITKDoxygenXML-TEMP )


add_custom_command( OUTPUT ${ITKDoxygenXML_DIR}/index.xml
  COMMAND ${CMAKE_COMMAND} -DITKDoxygenXML_TEMP_DIR="${ITKDoxygenXML_TEMP_DIR}" -P ${ITK_EXAMPLES_SOURCE_DIR}/cmake/DownloadDoxygenXML.cmake
  COMMAND ${CMAKE_COMMAND} -E chdir "${ITKDoxygenXML_TEMP_DIR}" ${CMAKE_COMMAND} -E tar xjf "${ITKDoxygenXML_TEMP_DIR}/itk-doxygen-xml.tar.bz2"
  COMMAND ${CMAKE_COMMAND} -E rename "${ITKDoxygenXML_TEMP_DIR}/xml" "${ITKDoxygenXML_DIR}"
  COMMAND ${CMAKE_COMMAND} -E remove_directory "${ITKDoxygenXML_TEMP_DIR}"
  COMMENT "Downloading and unpacking the Doxygen XML"
  )
add_custom_target( ITKDoxygenXML ${CMAKE_COMMAND} -E echo "Finished obtaining Doxygen XML"
  DEPENDS ${ITKDoxygenXML_DIR}/index.xml )
