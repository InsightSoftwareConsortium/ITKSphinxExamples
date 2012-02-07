set( ITKDoxygenTAG_DIR ${CMAKE_BINARY_DIR}/ITKDoxygenTAG )
set( ITKDoxygenTAG_TEMP_DIR ${CMAKE_BINARY_DIR}/ITKDoxygenTAG-TEMP )


add_custom_command( OUTPUT ${ITKDoxygenTAG_DIR}/InsightDoxygen.tag
  COMMAND ${CMAKE_COMMAND} -E chdir "${ITKDoxygenTAG_TEMP_DIR}" ${CMAKE_COMMAND} -E tar xjf "${ITKDoxygenTAG_TEMP_DIR}/InsightDoxygen.tag.tar.bz2"
  COMMAND ${CMAKE_COMMAND} -E rename "${ITKDoxygenTAG_TEMP_DIR}" "${ITKDoxygenTAG_DIR}"
  COMMAND ${CMAKE_COMMAND} -E remove_directory "${ITKDoxygenTAG_TEMP_DIR}"
  COMMENT "Downloading and unpacking the Doxygen TAG"
  )
add_custom_target( ITKDoxygenTAG ${CMAKE_COMMAND} -E echo "Finished obtaining Doxygen TAG"
  DEPENDS ${ITKDoxygenTAG_DIR}/InsightDoxygen.tag )

