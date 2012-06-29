How to build and visualize
==========================

Build individual examples
-------------------------

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

    cmake -DITK_DIR=/home/luis/itk_build ..

Build the project, and run the test::

  make
  ctest -V


.. _building-examples:

Build all examples and the documentation
----------------------------------------

Download the tarball. Unpack the example::

  tar xvzf ITKExamples.tar.gz

Move to the build directory::

  cd ITKExamples/build

Run CMake to configure the project.

- If ITK (Version 4.0.0 or above) is installed::

    cmake ..

- If ITK (Version 4.0.0 or above) is not installed but compiled on your
  system, you will need to specify the path to your ITK build::

    cmake -DITK_DIR=/home/luis/itk_build ..

- If ITK is not installed nor compiled, you can then make use of the superbuild functionality::

    cmake ../Superbuild/

The superbuild will download and build all required dependencies.  If you are
building the documentation and not using superbuild functionality, then you must
have all the required dependencies installed, which are listed in the
*readme.rst* file located at the root of the source tree.  If you just want to
build the examples and not their documentation, set *BUILD_DOCUMENTATION* to
*OFF* in your CMake configuration.

Build the project (will generate the documentation and all examples)::

  make

Run the tests::

  ctest -V

Run an example
--------------

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


.. _visualize:

Visualize the results
---------------------

ITK is a library limited in scope to image analysis, and it purposely does not
attempt to perform image visualization.  Visualizing the results of analysis is
possible with a number of third-party applications.  Note that these packages
are specially suited for medical images, which often have anisotropic spacing
and can span three or more dimensions.  All applications listed are open source
and cross-platform.


3DSlicer
  3DSlicer_ is an open-source software platform for the analysis and
  visualization of medical images and for research in image guided therapy.
  The platform provides functionality for segmentation, registration and
  three-dimensional visualization of multi-modal image data, as well as advanced
  image analysis algorithms for diffusion tensor imaging, functional magnetic
  resonance imaging and image-guided therapy. Standard image file formats are
  supported, and the application integrates interface capabilities to biomedical
  research software and image informatics frameworks.

.. figure:: slicer.png
  :alt: 3DSlicer
  :align: center

  3DSlicer_


ImageViewer
  An FLTK_-based *ImageViewer* is available in the ITKApps_ repository.  This
  simple yet effect slice-based viewer works on 2D and 3D images and supports
  probing of data values.

.. figure:: imageviewer.png
  :alt: ITKApps ImageViewer
  :align: center

  ImageViewer


ITK-SNAP
  ITK-SNAP_ is segmentation application, but it is also a nice general
  resource for visualization of the results of analysis.

.. figure:: itksnap.png
  :alt: ITK-SNAP
  :align: center

  ITK-SNAP_


Paraview
  Paraview_ is a full-featured scientific visualizion GUI written with Qt_/VTK_.
  It has extensive parallel processing capabilities.

.. figure:: paraview.png
  :alt: Paraview
  :align: center

  Paraview_


QGoImageCompare
  QGoImageCompare_ is a simple Qt_/VTK_ application capable of comparing multiple
  images simultaneous by coupling the cameras views.  It is also possible to
  interactively probe the location and value of pixels for both 2D and 3D
  datasets.

.. figure:: qgoimagecompare.png
  :alt: QGoImageCompare
  :align: center

  QGoImageCompare_


VV
  VV_ is an image viewer designed for fast and simple visualization of
  spatio-temporal images: 2D, 2D+t, 3D and 3D+t (or 4D) images.

.. figure:: vv.png
  :alt: VV
  :align: center

  VV_


.. _3DSlicer:              http://www.slicer.org/
.. _CMake:                 http://cmake.org/
.. _FLTK:                  http://www.fltk.org/
.. _ITKApps:               http://itk.org/ITKApps.git
.. _ITK-SNAP:              http://www.itksnap.org/pmwiki/pmwiki.php
.. _Paraview:              http://paraview.org/
.. _QGoImageCompare:       https://github.com/gofigure2/QGoImageCompare
.. _Qt:                    http://qt.nokia.com/
.. _VTK:                   http://vtk.org/
.. _VV:                    http://www.creatis.insa-lyon.fr/rio/vv 
