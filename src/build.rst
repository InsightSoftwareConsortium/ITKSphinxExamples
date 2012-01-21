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


.. _building all the examples:

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

If not build the documentation and not using superbuild functionality, then you
must have all the required dependencies installed, which are listed in the
*readme.rst* file located at the root of the source tree.  If you just want to
build the examples and not their documentation, set *BUILD_DOCUMENTATION* to
*OFF* in your CMake configuration.

Build the project (would generate the documentation and all examples)::

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

Submit results to CDash
=======================

Quality control of the examples is maintained with a dashboard that collects
configuration, build, and testings results in a CDash_ dashboard.  The
`ITKExamples dashboard`_ collects builds on a nightly, continuous, and
experimental basis from a variety of platforms.

Experimental submission
-----------------------

To submit testing results after `building all the examples`_, simply run::

  ctest -D Experimental

Nightly submission
------------------

You can volunteer to submit nightly testing results that ensure repository
activity during the day will allow breakage on your system to go unnoticed.

Step 1: Setup you build directory
..................................

You will need a directory with sufficient disk space to hold the project source
code, build tree, and testing scripts.  This can be placed anywhere on your
system where you have write access::

  mkdir ~/dashboards
  cd ~/dashboards

Copy the testing support script into your dashboard directory.

::

  cp ~/src/ITKExamples/scripts/itkexamples_common.cmake .

Step 2: Setup a script describing your system
.............................................

We will write a CTest script that will update the repository, configure, build,
and test the project, and then upload the results to the CDash server.  Most of
work in this script will be performed by `itkexamples_common.cmake`, but we need
to configure the settings unique to our system.

Create a file, `itkexamples_dashboard.cmake`, to hold these settings::

  cp ~/src/ITKExamples/scripts/itkexamples_dashboard.cmake.example itkexamples_dashboard.cmake

You *must* edit this file to describe your local system.

.. literalinclude:: ../scripts/itkexamples_dashboard.cmake.example

Step 3: Configure your system to run the script on a daily basis
................................................................

First, test the script to ensure that it runs correctly::

  ctest -S ./itkexamples_dashboard.cmake -V

Did everything work?  Do you see your build on the `ITKExamples dashboard`_?
If so, continue to setup a cronjob that will run the script daily.  Edit your
cron-file::

  crontab -e

The following line will run the script every day at 3 AM::

  0 3 * * * ctest -S /home/luis/dashboards/itkexamples_dashboard.cmake &> /dev/null
  
Thank you for contributing to the quality of the ITK Examples!

.. _CDash:                 http://cdash.org/
.. _CMake:                 http://cmake.org/
.. _ITKExamples dashboard: http://mmmccormick.com/CDash/index.php?project=ITKExamples
.. _ITK-SNAP:              http://www.itksnap.org/pmwiki/pmwiki.php
.. _Paraview:              http://paraview.org/
.. _QGoImageCompare:       https://github.com/gofigure2/QGoImageCompare
.. _Qt:                    http://qt.nokia.com/
.. _VTK:                   http://vtk.org/
