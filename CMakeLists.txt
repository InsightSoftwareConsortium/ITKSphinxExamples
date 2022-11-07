# ==== Define cmake build policies that affect compilation and linkage default behaviors
#
# Set the ITKEX_NEWEST_VALIDATED_POLICIES_VERSION string to the newest cmake version
# policies that provide successful builds. By setting ITKEX_NEWEST_VALIDATED_POLICIES_VERSION
# to a value greater than the oldest policies, all policies between
# ITKEX_OLDEST_VALIDATED_POLICIES_VERSION and CMAKE_VERSION (used for this build)
# are set to their NEW behaivor, thereby suppressing policy warnings related to policies
# between the ITKEX_OLDEST_VALIDATED_POLICIES_VERSION and CMAKE_VERSION.
#
# CMake versions greater than the ITKEX_NEWEST_VALIDATED_POLICIES_VERSION policies will
# continue to generate policy warnings "CMake Warning (dev)...Policy CMP0XXX is not set:"
#
set(ITKEX_OLDEST_VALIDATED_POLICIES_VERSION "3.10.2")
set(ITKEX_NEWEST_VALIDATED_POLICIES_VERSION "3.14.0")
cmake_minimum_required(VERSION ${ITKEX_OLDEST_VALIDATED_POLICIES_VERSION} FATAL_ERROR)
if("${CMAKE_VERSION}" VERSION_LESS_EQUAL "${ITKEX_NEWEST_VALIDATED_POLICIES_VERSION}")
  #Set and use the newest available cmake policies that are validated to work
  set(ITK_CMAKE_POLICY_VERSION "${CMAKE_VERSION}")
else()
  set(ITK_CMAKE_POLICY_VERSION "${ITKEX_NEWEST_VALIDATED_POLICIES_VERSION}")
endif()
cmake_policy(VERSION ${ITK_CMAKE_POLICY_VERSION})
#
# Now enumerate specific policies newer than ITKEX_NEWEST_VALIDATED_POLICIES_VERSION
# that may need to be individually set to NEW/OLD
#
foreach(pnew "") # Currently Empty
  if(POLICY ${pnew})
    cmake_policy(SET ${pnew} NEW)
  endif()
endforeach()
foreach(pold "") # Currently Empty
  if(POLICY ${pold})
    cmake_policy(SET ${pold} OLD)
  endif()
endforeach()

# ==== Define language standard configurations requiring at least c++14 standard
if(CMAKE_CXX_STANDARD EQUAL "98" OR CMAKE_CXX_STANDARD LESS "14")
  message(FATAL_ERROR "C++98 to C++11 are no longer supported in ITK version 5.3 and greater.")
endif()

#####
##  Set the default target properties for ITK
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 14) # Supported values are ``14``, ``17``, and ``20``.
endif()
if(NOT CMAKE_CXX_STANDARD_REQUIRED)
  set(CMAKE_CXX_STANDARD_REQUIRED ON)
endif()
if(NOT CMAKE_CXX_EXTENSIONS)
  set(CMAKE_CXX_EXTENSIONS OFF)
endif()

project(ITKSphinxExamples)

if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
  set(CMAKE_CXX_FLAGS  "-Qunused-arguments ${CMAKE_CXX_FLAGS}")
  set(CMAKE_C_FLAGS    "-Qunused-arguments ${CMAKE_C_FLAGS}")
endif()

if(CMAKE_HOST_WIN32)
  string(LENGTH "${ITKSphinxExamples_SOURCE_DIR}" source_len)
  if(${source_len} GREATER 30)
    message(FATAL_ERROR
    "The source directory is currently too long, ${source_len} characters. "
    "Please move the Examples source directory to a shorter path."
    )
  endif()
  string(LENGTH "${ITKSphinxExamples_BINARY_DIR}" binary_len)
  if(${binary_len} GREATER 30)
    message(FATAL_ERROR
    "The build directory is currently too long, ${binary_len} characters. "
    "Please set the Examples build directory to a shorter path."
    )
  endif()
endif()

#Optional if we are building as an ITK module, these variables will be pre-defined
if(NOT ITK_VERSION)
  # To get the ITK version information from external package when building
  # stand alone, ITK is required.
  find_package(ITK 5.2.0 REQUIRED)
endif()
set(ITKSphinxExamples_VERSION_MAJOR ${ITK_VERSION_MAJOR})
set(ITKSphinxExamples_VERSION_MINOR ${ITK_VERSION_MINOR})
set(ITKSphinxExamples_VERSION_PATCH ${ITK_VERSION_PATCH})

set(ITKSphinxExamples_VERSION
  "${ITKSphinxExamples_VERSION_MAJOR}.${ITKSphinxExamples_VERSION_MINOR}"
  )

set(ITKSphinxExamples_RELEASE_VERSION
   "${ITKSphinxExamples_VERSION_MAJOR}.${ITKSphinxExamples_VERSION_MINOR}.${ITKSphinxExamples_VERSION_PATCH}"
  )

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${ITKSphinxExamples_BINARY_DIR}/bin)

include(CTest)
# Tests are added with add_test() can be run with the 'ctest' command line program.
enable_testing()
configure_file(CMake/CTestCustom.cmake.in CTestCustom.cmake)

# ExternalData setup.  We use the CMake ExternalData features to download binary
# files from a configurable location(s) -- including the local filesystem -- to
# avoid storing the potentially large files in the Git history.
set(CMAKE_MODULE_PATH ${ITKSphinxExamples_SOURCE_DIR}/CMake ${CMAKE_MODULE_PATH})
# The CMake magic to download the data.
set(ExternalData_SOURCE_ROOT "${ITKSphinxExamples_SOURCE_DIR}")
set(ExternalData_BINARY_ROOT "${ITKSphinxExamples_BINARY_DIR}")

include(ITKSphinxExamplesExternalData)
set(_RootSubDirs
  CMake
  Formatting
  Utilities
  src
  Documentation
  Superbuild
  )

set(content_links)

# By default we copy all the content links in the source tree to their
# corresponding locations in the binary tree.
foreach(_dir ${_RootSubDirs})
  file(GLOB_RECURSE ${_dir}_content_links
    RELATIVE "${ITKSphinxExamples_SOURCE_DIR}" "${_dir}/*.cid")
  set(content_links ${content_links} ${${_dir}_content_links})
endforeach()

foreach(link ${content_links})
  string(REGEX REPLACE "\\.cid$" "" link ${link})
  ExternalData_Expand_Arguments(ITKSphinxExamplesData
    link_location
    DATA{${link}}
    )
endforeach()
ExternalData_Add_Target(ITKSphinxExamplesData)

if(${ITK_WRAP_PYTHON})
  # Use the same Python interpreter as ITK to run the tests.
  find_package(PythonInterp ${ITK_WRAP_PYTHON_VERSION} REQUIRED)
  mark_as_advanced(PYTHON_EXECUTABLE)
endif()
find_package(PythonInterp)
if(PYTHON_EXECUTABLE AND NOT ITK_WRAP_PYTHON)
  execute_process(COMMAND ${PYTHON_EXECUTABLE} -c "import itk"
    RESULT_VARIABLE _have_itk_return_code
    OUTPUT_QUIET
    ERROR_QUIET
    )
  if(_have_itk_return_code EQUAL 0)
    set(ITK_WRAP_PYTHON 1)
  endif()
endif()
if(BUILD_TESTING OR ITK_BUILD_DOCUMENTATION OR ITK_WRAP_PYTHON)
  # Prefer to use more robust FindPython3 module if greater than cmake 3.12.0
  if("${CMAKE_VERSION}" VERSION_LESS_EQUAL "3.12.0")
    # Use of PythonInterp and PythonLibs is deprecated since cmake version 3.12.0
    # Only use deprecated mechanisms for older versions of cmake
    set(Python_ADDITIONAL_VERSIONS 3.9 3.8 3.7 3.6 3.5)
    find_package(PythonInterp)
    if(ITK_WRAP_PYTHON)
      find_package(PythonLibs REQUIRED)
      # check for version mismatch.
      if(PYTHONLIBS_FOUND AND PYTHONINTERP_FOUND
          AND NOT(PYTHON_VERSION_STRING VERSION_EQUAL PYTHONLIBS_VERSION_STRING))
        message(FATAL_ERROR "Python executable (\"${PYTHON_VERSION_STRING}\") and library (\"${PYTHONLIBS_VERSION_STRING}\") version mismatch.")
      endif()
    endif()
    if(PYTHON_VERSION_STRING VERSION_LESS 3.5)
      # if python version is less than 3.5, unset so that it appears that no python version is found.
      # to emulate the same behavior as find(Python3 ..) from cmake 3.12.0+
      unset(PYTHON_EXECUTABLE)
      unset(PYTHONINTERP_FOUND)
      unset(PYTHON_VERSION_STRING)
      unset(PYTHON_INCLUDE_DIRS)
    else()
      ## For forward compatibility with cmake 3.12.0 or greater, emulate variable names from FindPython3.cmake
      set(Python3_EXECUTABLE ${PYTHON_EXECUTABLE})
      set(Python3_Interpreter_FOUND ${PYTHONINTERP_FOUND})
      set(Python3_VERSION ${PYTHON_VERSION_STRING})

      set(Python3_Development_FOUND ${PYTHONLIBS_FOUND})
      set(Python3_INCLUDE_DIRS ${PYTHON_INCLUDE_DIRS})
      set(Python3_LIBRARIES    ${PYTHON_LIBRARIES})
    endif()
  else()
    if(ITK_WRAP_PYTHON)
      if(DEFINED Python3_EXECUTABLE)
        set(_specified_Python3_EXECUTABLE ${Python3_EXECUTABLE})
      endif()
      find_package(Python3 COMPONENTS Interpreter Development)
      set(Python3_EXECUTABLE ${_specified_Python3_EXECUTABLE} CACHE INTERNAL
        "Path to the Python interpreter" FORCE)
    else()
      find_package(Python3 COMPONENTS Interpreter)
    endif()
    if(NOT Python3_EXECUTABLE AND _Python3_EXECUTABLE)
      set(Python3_EXECUTABLE ${_Python3_EXECUTABLE} CACHE INTERNAL
        "Path to the Python interpreter" FORCE)
    endif()
  endif()

  if(ITK_WRAP_PYTHON AND Python3_VERSION VERSION_LESS 3.5)
    message(FATAL_ERROR "Python versions less than 3.5 are not supported for wrapping. Python version: \"${Python3_VERSION}\".")
  endif()
  if(ITK_WRAP_PYTHON AND NOT Python3_INCLUDE_DIRS)
    message(FATAL_ERROR "Python version ${Python3_VERSION} development environment not found for wrapping.")
  endif()
endif()

# Build the documentation?
option(BUILD_DOCUMENTATION "Build the examples documentation." OFF)
if(BUILD_DOCUMENTATION)
  # -------------------------------------------------------------------------
  # Check to make sure the submodules are available
  find_package(Git)
  # The UPDATING_SUBMODULES variable can be set to prevent CMake from running
  # 'git submodule update' when attempting change the commit a submodule points
  # to.
  option(UPDATING_SUBMODULES
    "Set to ON when updating one of the Git submodules." OFF)
  if(EXISTS "${ITKSphinxExamples_SOURCE_DIR}/.git" AND GIT_EXECUTABLE AND NOT "${UPDATING_SUBMODULES}")
    execute_process(COMMAND ${GIT_EXECUTABLE} submodule update --init --recursive
    WORKING_DIRECTORY "${ITKSphinxExamples_SOURCE_DIR}"
    OUTPUT_QUIET
    )
  endif()
  if(NOT EXISTS "${ITKSphinxExamples_SOURCE_DIR}/Utilities/SphinxExtensions/breathelink/.git")
    message(SEND_ERROR "The git submodules are not available.  Please run
    git submodule update --init --recursive"
    )
  endif()
  # -------------------------------------------------------------------------

  # We must also duplicate the source tree since the images need to be present
  # with the source.
  add_custom_target(copy_sources ALL
    COMMAND ${CMAKE_COMMAND} -E copy_directory "${ITKSphinxExamples_SOURCE_DIR}/src" "${ITKSphinxExamples_BINARY_DIR}/src"
    COMMAND ${CMAKE_COMMAND} -E copy_directory "${ITKSphinxExamples_SOURCE_DIR}/Documentation" "${ITKSphinxExamples_BINARY_DIR}/Documentation"
    COMMAND ${CMAKE_COMMAND} -E copy "${ITKSphinxExamples_SOURCE_DIR}/index.rst" "${ITKSphinxExamples_BINARY_DIR}/index.rst"
    COMMAND ${CMAKE_COMMAND} -E copy_directory "${ITKSphinxExamples_SOURCE_DIR}/Formatting"
    "${ITKSphinxExamples_BINARY_DIR}/Formatting"
    COMMAND ${CMAKE_COMMAND} -E copy_directory "${ITKSphinxExamples_SOURCE_DIR}/Utilities"
    "${ITKSphinxExamples_BINARY_DIR}/Utilities"
    COMMENT "Copying sources"
    )
  # For unknown reasons, this was the only effective way to ensure ITKSphinxExamplesData
  # was built before build_html.
  add_dependencies(copy_sources ITKSphinxExamplesData)

  # A high level target that the individual targets depend on.
  add_custom_target(CreateDownloadableArchives ALL
    ${CMAKE_COMMAND} -E echo "Done creating individual example downloadable archives..."
    )

  if(NOT ITKDoxygenXML_DIR)
    include(${ITKSphinxExamples_SOURCE_DIR}/CMake/ITKDoxygenXML.cmake)
  endif()

  if(NOT ITKDoxygenTAG_DIR)
    include(${ITKSphinxExamples_SOURCE_DIR}/CMake/ITKDoxygenTAG.cmake)
  endif()

  # Builds the documentation.
  find_package(PythonInterp REQUIRED)
  find_package(Sphinx REQUIRED)
  find_program(PANDOC_BIN pandoc REQUIRED)

  set(SPHINX_CONF_DIR ${ITKSphinxExamples_BINARY_DIR}/Formatting)
  set(SPHINX_INPUT_DIR ${ITKSphinxExamples_BINARY_DIR})
  set(SPHINX_DESTINATION ${ITKSphinxExamples_BINARY_DIR})
  set(SPHINX_DEPENDENCIES ITKDoxygenXML ITKSphinxExamplesData ITKDoxygenTAG CreateDownloadableArchives)

  option(DOC_WITH_LOCAL_DOXYGEN "Generate documentation with local doxygen" OFF)
  mark_as_advanced(DOC_WITH_LOCAL_DOXYGEN)

  set(sphinx_target_base_name build)
  Sphinx_add_targets(${sphinx_target_base_name} ${SPHINX_CONF_DIR} ${SPHINX_INPUT_DIR} ${SPHINX_DESTINATION} ${SPHINX_DEPENDENCIES})

  if(${SPHINX_HTML_OUTPUT})
    install(DIRECTORY ${SPHINX_DESTINATION}/html
      DESTINATION share/ITKSphinxExamples/doc
      COMPONENT Doc
      PATTERN "${SPHINX_DESTINATION}/html/*"
      )
    add_custom_command(TARGET ${sphinx_target_base_name}_html
      POST_BUILD
      COMMAND ${PYTHON_EXECUTABLE}
        ${ITKSphinxExamples_SOURCE_DIR}/Utilities/DocumentationTarball.py
        ${SPHINX_DESTINATION}/html
        ${ITKSphinxExamples_BINARY_DIR}/ITKSphinxExamples-${ITKSphinxExamples_RELEASE_VERSION}-html
      WORKING_DIRECTORY ${ITKSphinxExamples_BINARY_DIR}/html
      COMMENT "Creating html tarballs..."
      )
    install(FILES
      ${ITKSphinxExamples_BINARY_DIR}/ITKSphinxExamples-${ITKSphinxExamples_RELEASE_VERSION}-html.tar.gz
      ${ITKSphinxExamples_BINARY_DIR}/ITKSphinxExamples-${ITKSphinxExamples_RELEASE_VERSION}-html.zip
      DESTINATION share/ITKSphinxExamples/doc/html
      COMPONENT Doc
      )
  endif()

  if(${SPHINX_LATEX_OUTPUT})
    set(DOC_WITH_LOCAL_DOXYGEN OFF)

    # Build the PDF with pdflatex
    find_package(LATEX)
    if(NOT PDFLATEX_COMPILER)
      message("pdflatex compiler was not found. Please pass to advanced mode and provide its full path")
    else()
      # Needs to be executed twice to get table of contents.
      add_custom_command(TARGET ${sphinx_target_base_name}_latex
        POST_BUILD
        COMMAND ${PDFLATEX_COMPILER}
          ${SPHINX_DESTINATION}/latex/ITKSphinxExamples.tex
          -output-directory ${SPHINX_DESTINATION}/latex
        COMMAND ${MAKEINDEX_COMPILER}
          ITKSphinxExamples.idx
        COMMAND ${PDFLATEX_COMPILER}
          ${SPHINX_DESTINATION}/latex/ITKSphinxExamples.tex
          -output-directory ${SPHINX_DESTINATION}/latex
        COMMAND ${CMAKE_COMMAND} -E copy
          ${SPHINX_DESTINATION}/latex/ITKSphinxExamples.pdf
          ${SPHINX_DESTINATION}/html/Documentation/Download/ITKSphinxExamples-${ITKSphinxExamples_RELEASE_VERSION}.pdf
        WORKING_DIRECTORY ${SPHINX_DESTINATION}/latex
        COMMENT "Building PDF"
        )
      install(FILES ${SPHINX_DESTINATION}/html/Documentation/Download/ITKSphinxExamples-${ITKSphinxExamples_RELEASE_VERSION}.pdf
        DESTINATION share/ITKSphinxExamples/doc/pdf
        COMPONENT Doc
        )
    endif()
  endif()

  if(${SPHINX_EPUB_OUTPUT})
    add_custom_command(TARGET ${sphinx_target_base_name}_epub
      POST_BUILD
      COMMAND ${CMAKE_COMMAND} -E copy
        ${SPHINX_DESTINATION}/epub/sphinx.epub
        ${SPHINX_DESTINATION}/html/Documentation/Download/ITKSphinxExamples-${ITKSphinxExamples_RELEASE_VERSION}.epub
        COMMENT "Copying EPUB"
        )
    install(FILES ${SPHINX_DESTINATION}/html/Documentation/Download/ITKSphinxExamples-${ITKSphinxExamples_RELEASE_VERSION}.epub
      DESTINATION share/ITKSphinxExamples/doc/epub
      COMPONENT Doc
      )
  endif()

  if(DOC_WITH_LOCAL_DOXYGEN)
    set(ITKDoxygen_LINK_ADDRESS ${ITKDoxygen_DIR})
    set(SPHINX_DEPENDENCIES ${SPHINX_DEPENDENCIES} ITKDoxygen)
    if(NOT ITKDoxygen_DIR)
      include(${CMAKE_SOURCE_DIR}/CMake/ITKDoxygen.cmake)
    endif()
  else()
    set(ITKDoxygen_LINK_ADDRESS "https://itk.org/Doxygen/html")
  endif()

  add_subdirectory(Formatting)
  add_subdirectory(Documentation)
else()
  # Copy the cookiecutter directory
  # Achieved with copy_sources target when BUILD_DOCUMENTATION enabled
  add_custom_target(copy_cookiecutter ALL
    COMMAND ${CMAKE_COMMAND} -E copy_directory
      "${ITKSphinxExamples_SOURCE_DIR}/Utilities/CookieCutter"
      "${ITKSphinxExamples_BINARY_DIR}/Utilities/CookieCutter"
    COMMENT "Copy CookieCutter"
    )
endif()

# Configure the CreateNewExamples.py Python Script
configure_file("${ITKSphinxExamples_SOURCE_DIR}/Utilities/CreateNewExample.py.in"
  "${ITKSphinxExamples_BINARY_DIR}/Utilities/CreateNewExample.py"
  @ONLY)

# Build the example executables?
option(BUILD_EXECUTABLES "Build the example executables." ON)
if(COMMAND itk_module_impl)
  itk_module_impl()
else()
  if(BUILD_EXECUTABLES)
    add_subdirectory(src)
  endif()
  add_subdirectory(Utilities)

  include(CPack)
endif()
