#---------------------------------------------------------------------------
# Get and build breathe 

set( BREATHE_TAG "origin/master" )

ExternalProject_Add( BREATHE
  GIT_REPOSITORY "${git_protocol}://github.com/arnaudgelas/breathe.git"
  GIT_TAG "${BREATHE_TAG}"
  SOURCE_DIR BREATHE
  BINARY_DIR BREATHE-build
  CMAKE_ARGS
    ${ep_common_args}
  INSTALL_COMMAND ""
)

set(BREATHE_DIR ${CMAKE_BINARY_DIR}/BREATHE)
