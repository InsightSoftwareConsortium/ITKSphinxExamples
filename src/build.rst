=====
Build
=====

Build individual examples
=========================

Download the *example.tar.gz* or *example.zip* file from the link in the left
hand column of the example's webpage.  Unpack the example::

  tar xvzf example.tar.gz

Move to the build directory::

  cd example/build

Run CMake to configure the project.

- If ITK (Version 4.0.0 or above) is installed::

    cmake ..

- If ITK (Version 4.0.0 or above) is not installed but compiled on your
  system, you will need to specify the path to your ITK build::

    cmake -DITK_DIR=/home/prince/itk_build ..


Build the project, and run the test::

  make
  ctest -V


Build all examples and the documentation
========================================

Download the tarball. Unpack the example::

  tar xvzf ITKExamples.tar.gz

Move to the build directory::

  cd ITKExamples/build

Run CMake to configure the project.

- If ITK (Version 4.0.0 or above) is installed::

    cmake ..

- If ITK (Version 4.0.0 or above) is not installed but compiled on your
  system, you will need to specify the path to your ITK build::

    cmake -DITK_DIR=/home/prince/itk_build ..

- If ITK is not installed nor compiled, you can then make use of the superbuild functionality::
  
    cmake ../superbuild/

Build the project (would generate the documentatin and all examples)::

  make

Run the tests::

  ctest -V

Run an example
==============

After building the examples, you can run an example by using `cd` to move to
the example's directory.  Then, directly run the executable.

Alternatively, the `ctest` command line program that comes with CMake_ can be
used to drive the examples as unit test.  Running::

  ctest

in the binary tree will run all unit tests found in the current directory and
below.

::

  ctest -R Binary

will run all tests whose name matches the regular expression *Binary*.

::

  ctest -V

will run *ctest* in verbose mode, which prints out the command executed and all
of the resulting text output.


Visualize the results
=====================

ITK is a library limited in scope to image analysis, and it purposely does not
attempt to perform image visualization.  Visualizing the results of analysis
can is possible with a number of third party applications.  Note that these
packages are specially suited for medical images, which often have anisotropic
spacing and can span three or more dimensions.  All applications listed are
cross-platform.

ITK-SNAP_
  ITK-SNAP is an application segmentation tools, but is also a nice general
  resource for visualizing analysis results.

Paraview_
  Paraview is a full-featured scientific visualizion GUI written with Qt_/VTK_.
  It has extensive parallel processing capabilities.

QGoImageCompare_
  QGoImageCompare is a simple Qt_/VTK_ application capable of comparing multiple
  images simultaneous by coupling the cameras views.  It is also possible to
  interactively probe the location and value of pixels for both 2D and 3D
  datasets.

.. todo::

  screenshots
  ITKApps FLTK ImageViewer
  VV
  3DSlicer

.. _CMake:           http://cmake.org/
.. _ITK-SNAP:        http://www.itksnap.org/pmwiki/pmwiki.php
.. _Paraview:        http://paraview.org/
.. _QGoImageCompare: https://github.com/gofigure2/QGoImageCompare
.. _Qt:              http://qt.nokia.com/
.. _VTK:             http://vtk.org/
