find_package(Git)

if(NOT GIT_FOUND)
  message(ERROR "Cannot find git. git is required for Superbuild")
endif()

option( USE_GIT_PROTOCOL "If behind a firewall turn this off to use http instead." OFF)

set(git_protocol "git")
if(NOT USE_GIT_PROTOCOL)
  set(git_protocol "https")
endif()

include( ExternalProject )

set(ep_common_args
  -DCMAKE_BUILD_TYPE:STRING=${CMAKE_BUILD_TYPE}
  -DCMAKE_CXX_COMPILER:STRING=${CMAKE_CXX_COMPILER}
  -DCMAKE_C_COMPILER:STRING=${CMAKE_C_COMPILER}
  -DCMAKE_GENERATOR:STRING=${CMAKE_GENERATOR}
  -DCMAKE_RUNTIME_OUTPUT_DIRECTORY:PATH=${CMAKE_BINARY_DIR}/ITKEx-build/bin
  )

# Compute -G arg for configuring external projects with the same CMake generator:
if(CMAKE_EXTRA_GENERATOR)
  set(gen "${CMAKE_EXTRA_GENERATOR} - ${CMAKE_GENERATOR}")
else()
  set(gen "${CMAKE_GENERATOR}" )
endif()

set(ITKSphinxExamples_DEPENDENCIES )
set(ITK_DEPENDENCIES )

option(ITKSphinxExamples_USE_VTK "Add VTK to the superbuild." OFF)

option(ITKSphinxExamples_USE_OpenCV "Add OpenCV to the superbuild" OFF)
if(NOT OpenCV_DIR AND ITKSphinxExamples_USE_OpenCV)
  include(${CMAKE_SOURCE_DIR}/External-OpenCV.cmake)
  list(APPEND ITKSphinxExamples_DEPENDENCIES OpenCV)
  list(APPEND ITK_DEPENDENCIES OpenCV)
endif()


set(_use_python_default ON)
if(WIN32)
  set(_use_python_default OFF)
endif()
option(ITKSphinxExamples_USE_WRAP_PYTHON "Enable downloads of the ITK Python wrapping to the superbuild" ${_use_python_default})
if(NOT EXISTS Python3_EXECUTABLE AND ITKSphinxExamples_USE_WRAP_PYTHON OR ITKSphinxExamples_USE_VTK)
  include(${CMAKE_SOURCE_DIR}/External-Python.cmake)
  list(APPEND ITKSphinxExamples_DEPENDENCIES ITKPython)
  set(_python_args "-DPython3_EXECUTABLE:FILEPATH=${ITKPython3_EXECUTABLE}")
endif()

if(NOT VTK_DIR AND ITKSphinxExamples_USE_VTK)
  include(${CMAKE_SOURCE_DIR}/External-VTK.cmake)
  list(APPEND ITKSphinxExamples_DEPENDENCIES VTK)
  list(APPEND ITK_DEPENDENCIES VTK)
endif()

if(NOT ITK_DIR)
  include(${CMAKE_SOURCE_DIR}/External-ITK.cmake)
  list(APPEND ITKSphinxExamples_DEPENDENCIES ITK)
endif()

option(BUILD_DOCUMENTATION "Build documentation" OFF)
set(_build_doc_args)
if(BUILD_DOCUMENTATION)
  if(ITKDoxygen_DIR)
    set(_build_doc_args "${_build_doc_args} -DITKDoxygen_DIR:PATH=${ITKDoxygen_DIR}")
  endif()
  if(ITKDoxygenXML_DIR)
    set(_build_doc_args "${_build_doc_args} -DITKDoxygenXML_DIR:PATH=${ITKDoxygenXML_DIR}")
  endif()
  if(ITKDoxygenTAG_DIR)
    set(_build_doc_args "${_build_doc_args} -DITKDoxygenTAG_DIR:PATH=${ITKDoxygenTAG_DIR}")
  endif()
  if(DOC_WITH_LOCAL_DOXYGEN)
    set(_build_doc_args "${_build_doc_args} -DDOC_WITH_LOCAL_DOXYGEN:PATH=${DOC_WITH_LOCAL_DOXYGEN}")
  endif()
  find_package(Sphinx REQUIRED)
  list(APPEND _build_doc_args
    "-DSPHINX_EXECUTABLE:PATH=${SPHINX_EXECUTABLE}"
    "-DSPHINX_DEVHELP_OUTPUT:BOOL=${SPHINX_DEVHELP_OUTPUT}"
    "-DSPHINX_DIRHTML_OUTPUT:BOOL=${SPHINX_DIRHTML_OUTPUT}"
    "-DSPHINX_EPUB_OUTPUT:BOOL=${SPHINX_EPUB_OUTPUT}"
    "-DSPHINX_HTML_OUTPUT:BOOL=${SPHINX_HTML_OUTPUT}"
    "-DSPHINX_LATEX_OUTPUT:BOOL=${SPHINX_LATEX_OUTPUT}"
    "-DSPHINX_MAN_OUTPUT:BOOL=${SPHINX_MAN_OUTPUT}"
    "-DSPHINX_QTHELP_OUTPUT:BOOL=${SPHINX_QTHELP_OUTPUT}"
    "-DSPHINX_TEXT_OUTPUT:BOOL=${SPHINX_TEXT_OUTPUT}"
    "-DSPHINX_LINKCHECK:BOOL=${SPHINX_LINKCHECK}"
    )
endif()

include(CTest)
option(BUILD_TESTING "Build testing" OFF)

ExternalProject_Add(ITKSphinxExamples
  DEPENDS ${ITKSphinxExamples_DEPENDENCIES}
  PREFIX ITKEx-prefix
  DOWNLOAD_COMMAND ""
  SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/..
  BINARY_DIR ITKEx-build
  CMAKE_GENERATOR ${gen}
  CMAKE_ARGS
    ${ep_common_args}
    ${_build_doc_args}
    ${_python_args}
    -DBUILD_SHARED_LIBS:BOOL=FALSE
     # ITK
    -DITK_DIR:PATH=${ITK_DIR}
    -DBUILD_TESTING:BOOL=${BUILD_TESTING}
    -DBUILD_DOCUMENTATION:BOOL=${BUILD_DOCUMENTATION}
    -DExternalData_OBJECT_STORES:STRING=${ExternalData_OBJECT_STORES}
  INSTALL_COMMAND ""
)

# Download and configure clang-format for style uniformity during development.
#
# This code helps download a version of clang-format binaries consistent with
# ITK's clang-format configuration. Git configuration is added during
# development to help automatically apply the formatting.
#
# Globally, the ITK/.clang-format file provides the base style configuration.
# For more information on ITK coding style, see the ITK Coding Style Guide in
# the ITK Software Guide.
option(ITKSphinxExamples_USE_CLANG_FORMAT "Enable the use of clang-format for coding style formatting." ${BUILD_TESTING})
mark_as_advanced(ITKSphinxExamples_USE_CLANG_FORMAT)

if(BUILD_TESTING AND ITKSphinxExamples_USE_CLANG_FORMAT AND NOT CMAKE_CROSSCOMPILING)
  include(${CMAKE_SOURCE_DIR}/External-ClangFormat.cmake)
endif()
