find_package(PythonInterp 3 REQUIRED)

set(_itk_venv "${CMAKE_CURRENT_BINARY_DIR}/itkpython")
if(WIN32)
  set(ITKPYTHON_EXECUTABLE "${_itk_venv}/python.exe" CACHE FILEPATH "Python executable with the ITK package installed" FORCE)
  set(SPHINX_EXECUTABLE "${_itk_venv}/Scripts/sphinx-build.exe" CACHE FILEPATH "Sphinx executable" FORCE)
  set(BLACK_EXECUTABLE "${_itk_venv}/Scripts/black.exe" CACHE FILEPATH "black executable" FORCE)
else()
  set(ITKPYTHON_EXECUTABLE "${_itk_venv}/bin/python" CACHE FILEPATH "Python executable with the ITK package installed" FORCE)
  set(SPHINX_EXECUTABLE "${_itk_venv}/bin/sphinx-build" CACHE FILEPATH "Sphinx executable" FORCE)
  set(BLACK_EXECUTABLE "${_itk_venv}/bin/black" CACHE FILEPATH "black executable" FORCE)
endif()
configure_file("${CMAKE_CURRENT_SOURCE_DIR}/ITKBlackConfig.cmake.in"
               "${CMAKE_CURRENT_BINARY_DIR}/ITKBlackConfig.cmake" @ONLY)

ExternalProject_Add(ITKPython
  DOWNLOAD_COMMAND ""
  CONFIGURE_COMMAND ${PYTHON_EXECUTABLE} -m venv "${_itk_venv}"
  BUILD_COMMAND ${ITKPYTHON_EXECUTABLE} -m pip install --upgrade pip
  INSTALL_COMMAND ${ITKPYTHON_EXECUTABLE} -m pip install --ignore-installed itk>=5.2rc3 sphinx==3.0.4 six black
  COMMAND ${CMAKE_COMMAND} -P ${CMAKE_CURRENT_BINARY_DIR}/ITKBlackConfig.cmake
  )
