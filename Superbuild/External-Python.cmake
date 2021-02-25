find_package(PythonInterp 3 REQUIRED)

set(_itk_venv "${CMAKE_CURRENT_BINARY_DIR}/itkpython")
if(WIN32)
  set(ITKPYTHON_EXECUTABLE "${_itk_venv}/python.exe" CACHE FILEPATH "Python executable with the ITK package installed" FORCE)
  set(SPHINX_EXECUTABLE "${_itk_venv}/Scripts/sphinx-build.exe" CACHE FILEPATH "Sphinx executable" FORCE)
else()
  set(ITKPYTHON_EXECUTABLE "${_itk_venv}/bin/python" CACHE FILEPATH "Python executable with the ITK package installed" FORCE)
  set(SPHINX_EXECUTABLE "${_itk_venv}/bin/sphinx-build" CACHE FILEPATH "Sphinx executable" FORCE)
endif()

ExternalProject_Add(ITKPython
  DOWNLOAD_COMMAND ""
  CONFIGURE_COMMAND ""
  BUILD_COMMAND ${PYTHON_EXECUTABLE} -m venv "${_itk_venv}"
  INSTALL_COMMAND ${ITKPYTHON_EXECUTABLE} -m pip install --ignore-installed --pre itk>=5.2rc2 sphinx==3.0.4 six
  )
