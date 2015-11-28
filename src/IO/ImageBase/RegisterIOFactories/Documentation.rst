Register IO Factories
=====================

.. index::
   single: ImageFileReader
   single: ObjectFactoryBase
   single: MetaImageIOFactory
   single: PNGImageIOFactory

Synopsis
--------

When CMake is not used to build an executable or library against ITK, the
Image and Transform IO format objects are not automatically registered to
ITK's object factory system, so they must be manually registered. There is not
a static list of IO classes because the classes available depend on which
modules are enabled when ITK is configured.  This examples shows how to
register the ImageIOBase objects so the ImageFileReader can read the
formats corresponding to the registered objects.


Results
-------

::

  When CMake is not used to register the IO classes, there are
  0 IO objects available to the ImageFileReader.

  When we try to read a MetaImage, we will fail.

  After registering the MetaImageIO object, there are
  1 IO objects available to the ImageFileReader.

  Now, when we try to read a MetaImage, we will succeed.

  Every format desired to be supported by the reader
  must be registered.


Code
----

C++
...

.. literalinclude:: Code.cxx
   :lines: 18-


Classes demonstrated
--------------------

.. breathelink:: itk::ImageFileReader

.. breathelink:: itk::ObjectFactoryBase

.. breathelink:: itk::MetaImageIOFactory

.. breathelink:: itk::PNGImageIOFactory
