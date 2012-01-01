cmake_minimum_required( VERSION 2.8 )
project( ITK_EXAMPLES )

find_program( SPHINX_BUILD sphinx-build )

set( HTML_DESTINATION ${ITK_EXAMPLES_BINARY_DIR}/html )
#function( build_example )
add_custom_target( build_html
  COMMAND ${SPHINX_BUILD} -b dirhtml
  -c ${ITK_EXAMPLES_SOURCE_DIR}/formatting
  ${ITK_EXAMPLES_SOURCE_DIR}/src
  ${HTML_DESTINATION}
  )
#endfunction()

add_subdirectory( formatting )
add_subdirectory( src )
