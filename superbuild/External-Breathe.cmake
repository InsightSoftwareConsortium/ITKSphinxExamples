#---------------------------------------------------------------------------
# Get and build breathe 

set( BREATHE_TAG "origin/master" )

ExternalProject_Add( BREATHE
  GIT_REPOSITORY "${git_protocol}://github.com/arnaudgelas/breathe.git"
  GIT_TAG "${BREATHE_TAG}"
  SOURCE_DIR BREATHE
  CONFIGURE_COMMAND ""
  BUILD_COMMAND ""
  INSTALL_COMMAND ""
)

set(BREATHE_DIR ${CMAKE_BINARY_DIR}/BREATHE)
