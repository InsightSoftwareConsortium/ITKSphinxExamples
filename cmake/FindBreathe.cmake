# - This module looks for Sphinx
# Find the Sphinx documentation generator
#
# This modules defines
#  BREATHE_DIR 
#  BREATHE_FOUND

find_path(BREATHE_DIR NAMES breathe.cmake
  DOC "breathe dir"
)

include(FindPackageHandleStandardArgs)

find_package_handle_standard_args(Breathe DEFAULT_MSG
  BREATHE_DIR 
)
