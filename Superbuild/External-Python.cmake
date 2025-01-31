set(MIN_PYTHON_VERSION 3.9)
find_package(Python3 ${MIN_PYTHON_VERSION} COMPONENTS Interpreter REQUIRED)

set(_itk_venv "${CMAKE_CURRENT_BINARY_DIR}/itkpython")
if(WIN32)
  set(ITKPython3_EXECUTABLE "${_itk_venv}/python.exe" CACHE FILEPATH "Python executable with the ITK package installed" FORCE)
  set(SPHINX_EXECUTABLE "${_itk_venv}/Scripts/sphinx-build.exe" CACHE FILEPATH "Sphinx executable" FORCE)
  set(BLACK_EXECUTABLE "${_itk_venv}/Scripts/black.exe" CACHE FILEPATH "black executable" FORCE)
else()
  set(ITKPython3_EXECUTABLE "${_itk_venv}/bin/python" CACHE FILEPATH "Python executable with the ITK package installed" FORCE)
  set(SPHINX_EXECUTABLE "${_itk_venv}/bin/sphinx-build" CACHE FILEPATH "Sphinx executable" FORCE)
  set(BLACK_EXECUTABLE "${_itk_venv}/bin/black" CACHE FILEPATH "black executable" FORCE)
endif()
configure_file("${CMAKE_CURRENT_SOURCE_DIR}/ITKBlackConfig.cmake.in"
               "${CMAKE_CURRENT_BINARY_DIR}/ITKBlackConfig.cmake" @ONLY)

ExternalProject_Add(ITKPython
  DOWNLOAD_COMMAND ""
  CONFIGURE_COMMAND ${Python3_EXECUTABLE} -m venv "${_itk_venv}"
  BUILD_COMMAND ${ITKPython3_EXECUTABLE} -m pip install --upgrade pip
  INSTALL_COMMAND ${ITKPython3_EXECUTABLE} -m pip install --ignore-installed itk>=5.4.0 sphinx==7.2.6 six black nbsphinx ipywidgets sphinx-contributors ipykernel matplotlib itkwidgets[lab,notebook]>=1.0a51 pydata-sphinx-theme
  COMMAND ${CMAKE_COMMAND} -P ${CMAKE_CURRENT_BINARY_DIR}/ITKBlackConfig.cmake
  )
