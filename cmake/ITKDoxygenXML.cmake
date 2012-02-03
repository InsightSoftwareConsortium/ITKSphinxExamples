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

if( NOT ITKDoxygenTAG_DIR )
## TAG file
set( ITKDoxygenTAG_DIR ${CMAKE_BINARY_DIR}/ITKDoxygenTAG )
set( ITKDoxygenTAG_TEMP_DIR ${CMAKE_BINARY_DIR}/ITKDoxygenTAG-TEMP )

file( DOWNLOAD http://dl.dropbox.com/u/15135983/InsightDoxygen.tag.tar.bz2
  ${ITKDoxygenTAG_TEMP_DIR}/InsightDoxygen.tag.tar.bz2 SHOW_PROGRESS
  )

add_custom_command( OUTPUT ${ITKDoxygenTAG_DIR}/InsightDoxygen.tag
  COMMAND ${CMAKE_COMMAND} -E chdir "${ITKDoxygenTAG_TEMP_DIR}" ${CMAKE_COMMAND} -E tar xjf "${ITKDoxygenTAG_TEMP_DIR}/InsightDoxygen.tag.tar.bz2"
  COMMAND ${CMAKE_COMMAND} -E rename "${ITKDoxygenTAG_TEMP_DIR}" "${ITKDoxygenTAG_DIR}"
  COMMAND ${CMAKE_COMMAND} -E remove_directory "${ITKDoxygenTAG_TEMP_DIR}"
  COMMENT "Downloading and unpacking the Doxygen TAG"
  )
add_custom_target( ITKDoxygenTAG ${CMAKE_COMMAND} -E echo "Finished obtaining Doxygen TAG"
  DEPENDS ${ITKDoxygenTAG_DIR}/InsightDoxygen.tag )

endif()
