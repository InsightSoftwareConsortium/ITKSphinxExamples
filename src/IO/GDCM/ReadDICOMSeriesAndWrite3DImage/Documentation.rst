Read DICOM Series and Write 3D Image
====================================

.. index::
   pair: GDCMSeriesFileNames; GDCMImageIO

Synopsis
--------

This example reads all the DICOM series in a given folder argv[1]
and writes them in the same folder with following file pattern:
seriesIdentifier.nrrd

if output file name argv[2] and series name argv[3] are given,
then it behaves like DicomSeriesReadImageWrite2.cxx
(writing just the requested series with the specified name).

Based on DicomSeriesReadImageWrite2.cxx

Author: Dženan Zukić <dzenan.zukic@kitware.com>


Code
----

Python
......

.. literalinclude:: Code.py
   :language: python
   :lines: 1, 16-

C++
...

.. literalinclude:: Code.cxx
   :lines: 18-


Classes demonstrated
--------------------

.. breathelink:: itk::GDCMSeriesFileNames
.. breathelink:: itk::GDCMImageIO
.. breathelink:: itk::ImageSeriesReader
