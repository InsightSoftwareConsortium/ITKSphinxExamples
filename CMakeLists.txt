cmake_minimum_required( VERSION 2.8 )
project( ITK_EXAMPLES )

find_program( SPHINX_BUILD sphinx-build )

set( HTML_DESTINATION ${ITK_EXAMPLES_BINARY_DIR}/html )
set( HTML_COLOR_THEME "light" )
configure_file( ${ITK_EXAMPLES_SOURCE_DIR}/formatting/conf.py.in
  ${HTML_DESTINATION}/light/conf.py )
set( HTML_COLOR_THEME "dark" )
configure_file( ${ITK_EXAMPLES_SOURCE_DIR}/formatting/conf.py.in
  ${HTML_DESTINATION}/dark/conf.py )
#function( build_example )
add_custom_target( build_html_docs_dark
  COMMAND ${SPHINX_BUILD} -b dirhtml
  -c ${HTML_DESTINATION}/dark/
  ${ITK_EXAMPLES_SOURCE_DIR}/src
  ${HTML_DESTINATION}/dark
  )
add_custom_target( build_html_docs_light
  COMMAND ${SPHINX_BUILD} -b dirhtml
  -c ${HTML_DESTINATION}/light/
  ${ITK_EXAMPLES_SOURCE_DIR}/src
  ${HTML_DESTINATION}/light
  )
#endfunction()

add_subdirectory( formatting )
add_subdirectory( src )
