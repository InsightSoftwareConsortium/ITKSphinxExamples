cmake_minimum_required( VERSION 2.8 )
project( ITK_EXAMPLES )

find_program( SPHINX_BUILD sphinx-build )

#function( build_example )
add_custom_target( build_docs
  COMMAND ${SPHINX_BUILD} -b dirhtml ${ITK_EXAMPLES_SOURCE_DIR}/src
  ${ITK_EXAMPLES_BINARY_DIR}
  )
#endfunction()

add_subdirectory( src )
