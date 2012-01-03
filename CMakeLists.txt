cmake_minimum_required( VERSION 2.8.5 )
project( ITK_EXAMPLES )

# Builds the documentation.
find_program( SPHINX_BUILD sphinx-build )

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
endfunction()

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

# This needs to be at the end in case we needed to fetch any other ExternalData.
ExternalData_Add_Target( ITKExamplesData )
