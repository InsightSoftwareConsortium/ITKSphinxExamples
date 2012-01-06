cmake_minimum_required( VERSION 2.8.5 )
project( ITK_EXAMPLES )

# Tests are added with add_test() can be run with the 'ctest' command line program.
enable_testing()

# ExternalData setup.  We use the CMake ExternalData features to download binary
# files from a configurable location(s) -- including the local filesystem -- to
# avoid storing the potentially large files in the Git history.
set( CMAKE_MODULE_PATH ${ITK_EXAMPLES_SOURCE_DIR}/cmake ${CMAKE_MODULE_PATH} )
# The CMake magic to download the data.
set( ExternalData_SOURCE_ROOT "${ITK_EXAMPLES_SOURCE_DIR}" )
set( ExternalData_BINARY_ROOT "${ITK_EXAMPLES_BINARY_DIR}" )
include( ITKExamplesExternalData )
# By default we copy all the content links in the source tree to their
# corresponding locations in the binary tree.
file( GLOB_RECURSE content_links RELATIVE "${ITK_EXAMPLES_SOURCE_DIR}" "*.md5" )
foreach(link ${content_links})
  string( REGEX REPLACE "\\.md5$" "" link ${link} )
  ExternalData_Expand_Arguments( ITKExamplesData
    link_location
    DATA{${link}}
  )
endforeach()
# Function to copy the given <source>.md5 to the <destination> directory
# relative to ${ITK_EXAMPLES_BINARY_DIR} in the binary tree.
function( copy_external_data_to_binary source destination )
  # todo
endfunction()
# We must also duplicate the source tree since the images need to be present
# with the source.
add_custom_target( copy_sources ALL
  COMMAND ${CMAKE_COMMAND} -E copy_directory "${ITK_EXAMPLES_SOURCE_DIR}/src"
  "${ITK_EXAMPLES_BINARY_DIR}/src"
  COMMENT "Copying sources"
  )

# Build the documentation?
option( BUILD_DOCUMENTATION "Build the examples documentation." ON )
  if( BUILD_DOCUMENTATION )
  # Builds the documentation.
  find_package( Sphinx )

  set( SPHINX_CONF_DIR ${ITK_EXAMPLES_SOURCE_DIR}/formatting )

  set( SPHINX_INPUT_DIR ${ITK_EXAMPLES_BINARY_DIR}/src )

  set( HTML_DESTINATION ${ITK_EXAMPLES_BINARY_DIR}/html )

  Sphinx_add_target( build_html dirhtml ${SPHINX_CONF_DIR} ${SPHINX_INPUT_DIR} ${HTML_DESTINATION} )

  set( LATEX_DESTINATION ${ITK_EXAMPLES_BINARY_DIR}/latex )

  Sphinx_add_target( build_latex latex ${SPHINX_CONF_DIR} ${SPHINX_INPUT_DIR} ${LATEX_DESTINATION} )

  set( TEXT_DESTINATION ${ITK_EXAMPLES_BINARY_DIR}/text )

  Sphinx_add_target( build_text text ${SPHINX_CONF_DIR} ${SPHINX_INPUT_DIR} ${TEXT_DESTINATION} )

  add_dependencies( build_html copy_sources )

  add_subdirectory( formatting )
endif()

# Build the example executables?
option( BUILD_EXECUTABLES "Build the example executables." ON )
if( BUILD_EXECUTABLES )
  add_subdirectory( src )
endif()

# This needs to be at the end in case we needed to fetch any other ExternalData.
ExternalData_Add_Target( ITKExamplesData )
