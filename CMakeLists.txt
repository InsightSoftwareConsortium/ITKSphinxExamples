cmake_minimum_required( VERSION 2.8.5 )
project( ITK_EXAMPLES )

set( ITK_EXAMPLES_MAJOR_VERSION 4 )
set( ITK_EXAMPLES_MINOR_VERSION 0 )
set( ITK_EXAMPLES_PATCH_VERSION 0 )

set( ITK_EXAMPLES_VERSION
  "${ITK_EXAMPLES_MAJOR_VERSION}.${ITK_EXAMPLES_MINOR_VERSION}"
)

set( ITK_EXAMPLES_RELEASE_VERSION
   "${ITK_EXAMPLES_MAJOR_VERSION}.${ITK_EXAMPLES_MINOR_VERSION}.${ITK_EXAMPLES_PATCH_VERSION}"
)

include( CTest )
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
set( _RootSubDirs
  cmake
  formatting
  scripts
  src
  superbuild
)

set( content_links )

# By default we copy all the content links in the source tree to their
# corresponding locations in the binary tree.
foreach( _dir ${_RootSubDirs} )
  file( GLOB_RECURSE ${_dir}_content_links
    RELATIVE "${ITK_EXAMPLES_SOURCE_DIR}" "${_dir}/*.md5" )
  set( content_links ${content_links} ${${_dir}_content_links} )
endforeach()

foreach(link ${content_links})
  string( REGEX REPLACE "\\.md5$" "" link ${link} )
  ExternalData_Expand_Arguments( ITKExamplesData
    link_location
    DATA{${link}}
  )
endforeach()
ExternalData_Add_Target( ITKExamplesData )
# We must also duplicate the source tree since the images need to be present
# with the source.
add_custom_target( copy_sources ALL
  COMMAND ${CMAKE_COMMAND} -E copy_directory "${ITK_EXAMPLES_SOURCE_DIR}/src"
  "${ITK_EXAMPLES_BINARY_DIR}/src"
  COMMAND ${CMAKE_COMMAND} -E copy_directory "${ITK_EXAMPLES_SOURCE_DIR}/formatting"
  "${ITK_EXAMPLES_BINARY_DIR}/formatting"
  COMMAND ${CMAKE_COMMAND} -E copy_directory "${ITK_EXAMPLES_SOURCE_DIR}/scripts"
  "${ITK_EXAMPLES_BINARY_DIR}/scripts"
  COMMENT "Copying sources"
  )
# For unknown reasons, this was the only effective way to ensure ITKExamplesData
# was built before build_html.
add_dependencies( copy_sources ITKExamplesData )

# Build the documentation?
option( BUILD_DOCUMENTATION "Build the examples documentation." OFF )
if( BUILD_DOCUMENTATION )

  find_package( Breathe )

  if(NOT ITKDoxygenXML_DIR )
    include( ${CMAKE_SOURCE_DIR}/cmake/ITKDoxygenXML.cmake )
  endif()

  # Builds the documentation.
  find_package( Sphinx REQUIRED )
  set( SPHINX_HTML_OUTPUT ON )
  set( SPHINX_LATEX_OUTPUT OFF )
  set( SPHINX_TEXT_OUTPUT OFF )
  set( SPHINX_CONF_DIR ${ITK_EXAMPLES_BINARY_DIR}/formatting )
  set( SPHINX_INPUT_DIR ${ITK_EXAMPLES_BINARY_DIR}/src )
  set( SPHINX_DESTINATION ${ITK_EXAMPLES_BINARY_DIR} )
  set( SPHINX_DEPENDENCIES copy_sources ITKDoxygenXML ITKExamplesData )
  Sphinx_add_targets( build ${SPHINX_CONF_DIR} ${SPHINX_INPUT_DIR} ${SPHINX_DESTINATION} ${SPHINX_DEPENDENCIES} )

  # Build the PDF with pdflatex
  find_package( LATEX )
  if( NOT PDFLATEX_COMPILER )
    message("pdflatex compiler was not found. Please pass to advanced mode and provide its full path")
  else()
    # Needs to be executed twice to get table of contents.
    add_custom_command( TARGET build_latex 
      POST_BUILD
      COMMAND ${PDFLATEX_COMPILER}
        ${SPHINX_DESTINATION}/latex/ITKExamples.tex
        -output-directory ${SPHINX_DESTINATION}/latex
      COMMAND ${PDFLATEX_COMPILER}
        ${SPHINX_DESTINATION}/latex/ITKExamples.tex
        -output-directory ${SPHINX_DESTINATION}/latex
      WORKING_DIRECTORY ${SPHINX_DESTINATION}/latex
      COMMENT "Building PDF"
      )
  endif()

  add_subdirectory( formatting )
endif()

# Build the example executables?
option( BUILD_EXECUTABLES "Build the example executables." ON )
if( BUILD_EXECUTABLES )
  add_subdirectory( src )
endif()

configure_file( ${CMAKE_SOURCE_DIR}/scripts/CreateNewExample.py.in
  ${CMAKE_BINARY_DIR}/scripts/CreateNewExample.py
  @ONLY
)
