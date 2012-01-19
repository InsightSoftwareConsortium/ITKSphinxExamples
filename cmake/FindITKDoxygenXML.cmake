# - This module looks for Sphinx
# Find the Sphinx documentation generator
#
# This modules defines
#  ITKDoxygenXML_DIR 
#  ITKDoxygenXML_FOUND

find_path(ITKDoxygenXML_DIR NAMES ITK-AllGroups_8dox.xml
  DOC "breathe dir"
)

include(FindPackageHandleStandardArgs)

find_package_handle_standard_args(ITKDoxygenXML DEFAULT_MSG
  ITKDoxygenXML_DIR 
)
