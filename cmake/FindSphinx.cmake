# - This module looks for Sphinx
# Find the Sphinx documentation generator
#
# This modules defines
#  SPHINX_EXECUTABLE
#  SPHINX_FOUND

find_program(SPHINX_EXECUTABLE NAMES sphinx-build
  DOC "Sphinx documentation generator"
)

include(FindPackageHandleStandardArgs)

find_package_handle_standard_args(Sphinx DEFAULT_MSG
  SPHINX_EXECUTABLE
)


option( SPHINX_HTML_OUTPUT "Build a single HTML with the whole content." ON )
option( SPHINX_DIRHTML_OUTPUT "Build HTML pages, but with a single directory per document." OFF )
option( SPHINX_HTMLHELP_OUTPUT "Build HTML pages with additional information for building a documentation collection in htmlhelp." OFF )
option( SPHINX_QTHELP_OUTPUT "Build HTML pages with additional information for building a documentation collection in qthelp." OFF )
option( SPHINX_DEVHELP_OUTPUT "Build HTML pages with additional information for building a documentation collection in devhelp." OFF )
option( SPHINX_EPUB_OUTPUT "Build HTML pages with additional information for building a documentation collection in epub." OFF )
option( SPHINX_LATEX_OUTPUT "Build LaTeX sources that can be compiled to a PDF document using pdflatex." OFF )
option( SPHINX_MAN_OUTPUT "Build manual pages in groff format for UNIX systems." OFF )
option( SPHINX_TEXT_OUTPUT "Build plain text files." OFF )


mark_as_advanced(
  SPHINX_EXECUTABLE
  SPHINX_HTML_OUTPUT
  SPHINX_DIRHTML_OUTPUT
  SPHINX_HTMLHELP_OUTPUT
  SPHINX_QTHELP_OUTPUT
  SPHINX_DEVHELP_OUTPUT
  SPHINX_EPUB_OUTPUT
  SPHINX_LATEX_OUTPUT
  SPHINX_MAN_OUTPUT
  SPHINX_TEXT_OUTPUT
)

function(Sphinx_add_target target_name builder conf source destination )
  add_custom_target( ${target_name} ALL
    COMMAND ${SPHINX_EXECUTABLE} -b ${builder}
    -c ${conf}
    ${source}
    ${destination}
    COMMENT "Generating sphinx documentation: ${builder}"
    )

  set_property(
    DIRECTORY APPEND PROPERTY
    ADDITIONAL_MAKE_CLEAN_FILES
    ${destination}
    )
endfunction()
