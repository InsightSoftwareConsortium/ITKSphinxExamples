#-----------------------------------------------------------------------------
# Get and build ITK using FetchContent

include(FetchContent)

# Set ITK Git repository and tag
set(ITK_GIT_REPOSITORY "https://github.com/InsightSoftwareConsortium/ITK.git")
set(ITK_GIT_TAG "main")

if(NOT DEFINED ITK_BUILD_DEFAULT_MODULES)
  set(ITK_BUILD_DEFAULT_MODULES ON)
endif()

# Configure ITK-specific options that need to be set before FetchContent_Declare
if(NOT BUILD_SHARED_LIBS)
  set(CMAKE_C_VISIBILITY_PRESET "hidden")
  set(CMAKE_CXX_VISIBILITY_PRESET "hidden")
  set(ITK_TEMPLATE_VISIBILITY_DEFAULT OFF)
endif()

set(Module_ITKReview ON CACHE INTERNAL "")

# Set ITK build options
set(ITK_USE_KWSTYLE OFF)
set(BUILD_TESTING OFF)
set(BUILD_EXAMPLES OFF)

FetchContent_Declare(
  ITK
  GIT_REPOSITORY "${ITK_GIT_REPOSITORY}"
  GIT_TAG "${ITK_GIT_TAG}"
  EXCLUDE_FROM_ALL
  FIND_PACKAGE_ARGS
    NAMES
    ITK
)

FetchContent_MakeAvailable(ITK)

# Check if FetchContent used find_package() or fetched from source
FetchContent_GetProperties(ITK)
if(ITK_SOURCE_DIR)
  message(STATUS "ITK fetched from repository and built from source")
  message(STATUS "  Source directory: ${ITK_SOURCE_DIR}")
  message(STATUS "  Binary directory: ${ITK_BINARY_DIR}")
  set(ITK_DIR "${ITK_BINARY_DIR}")

  include(${ITK_DIR}/ITKConfig.cmake)
elseif(DEFINED ITK_FOUND)
  message(STATUS "ITK found via find_package()")
  # ITK_DIR should already be set by find_package()
else()
  message(FATAL_ERROR "ITK configuration failed - no targets available")
endif()

# These ITK options conflict with ITKSphinxExamples build options.
# Allow ITKSphinxExamples' cache variables to be respected.
unset(BUILD_TESTING)
unset(BUILD_EXAMPLES)
