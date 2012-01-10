configure_file( ${CMAKE_SOURCE_DIR}/formatting/conf.py.in
  ${CMAKE_BINARY_DIR}/formatting/conf.py
  @ONLY
)

execute_process( COMMAND ${CMAKE_COMMAND} -E copy_directory
  ${CMAKE_SOURCE_DIR}/formatting/itk
  ${CMAKE_BINARY_DIR}/formatting/itk
)

execute_process( COMMAND ${CMAKE_COMMAND} -E copy_directory
  ${CMAKE_SOURCE_DIR}/formatting/static
  ${CMAKE_BINARY_DIR}/formatting/static
)

execute_process( COMMAND ${CMAKE_COMMAND} -E copy_directory
  ${CMAKE_SOURCE_DIR}/formatting/templates
  ${CMAKE_BINARY_DIR}/formatting/templates
)
