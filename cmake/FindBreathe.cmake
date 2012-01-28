# - This module looks for Breathe
# Find the Breathe Sphinx-Doxygen bridge.
#
# This modules defines
#  BREATHE_DIR 
#  BREATHE_FOUND

find_path(BREATHE_DIR NAMES breathe.cmake
  DOC "breathe directory."
)

include(FindPackageHandleStandardArgs)

find_package_handle_standard_args(Breathe DEFAULT_MSG
  BREATHE_DIR 
)
