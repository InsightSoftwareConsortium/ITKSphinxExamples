#---------------------------------------------------------------------------
# Get a Python with the itk package installed on Windows or create a
# virtualenv to install the ITK package on Linux or Mac

if(WIN32)
  # python.org 64 bit Windows Python with the itk and sphinx packages installed
  set(_itk_python_dir "${CMAKE_CURRENT_BINARY_DIR}/itkpython")
  set(ITKPYTHON_EXECUTABLE "${_itk_python_dir}/python.exe" CACHE FILEPATH "Python executable with the ITK package installed" FORCE)
  ExternalProject_Add(ITKPython
    URL "https://data.kitware.com/api/v1/file/58c760808d777f0aef5d798e/download"
    URL_MD5 "440580cec3b86903da26f0246637024f"
    DOWNLOAD_NAME itkpython.zip
    DOWNLOAD_DIR ${CMAKE_CURRENT_BINARY_DIR}
    SOURCE_DIR ${_itk_python_dir}
    CONFIGURE_COMMAND ""
    BUILD_COMMAND ""
    INSTALL_COMMAND ""
    )
else()
  find_package(PythonInterp REQUIRED)

  set(_virtualenv_version 15.0.1)
  set(_virtualenv_SOURCE_DIR "virtualenv-${_virtualenv_version}")
  set(_virtualenv_script "${CMAKE_CURRENT_BINARY_DIR}/${_virtualenv_SOURCE_DIR}/virtualenv.py")
  set(_itk_venv "${CMAKE_CURRENT_BINARY_DIR}/itkpython")
  set(ITKPYTHON_EXECUTABLE "${_itk_venv}/bin/python" CACHE FILEPATH "Python executable with the ITK package installed" FORCE)
  ExternalProject_Add(ITKPython
    URL "https://pypi.python.org/packages/source/v/virtualenv/virtualenv-${_virtualenv_version}.tar.gz"
    URL_MD5 "28d76a0d9cbd5dc42046dd14e76a6ecc"
    DOWNLOAD_DIR ${CMAKE_CURRENT_BINARY_DIR}
    SOURCE_DIR ${_virtualenv_SOURCE_DIR}
    CONFIGURE_COMMAND ""
    BUILD_COMMAND ${PYTHON_EXECUTABLE} "${_virtualenv_script}" "${_itk_venv}"
    INSTALL_COMMAND ${ITKPYTHON_EXECUTABLE} -m pip install itk sphinx -f https://github.com/InsightSoftwareConsortium/ITKPythonPackage/releases/tag/nightly
    )
endif()
