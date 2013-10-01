Re-Run Pipeline With Changing Largest Possible Region
=====================================================

.. index::
   single: ProcessObject
   single: ImageSeriesReader
   single: pipeline

Synopsis
--------

Re-run a pipeline where the LargestPossibleRegion in the pipeline is expected to change on consecutive runs. The pipeline does not detect this condition, and it will throw an exception,

::

   Requested region is (at least partially) outside the largest possible region.

In this case, an `UpdateLargestPossibleRegion()` call is required instead of `Update()`.

Results
-------

Output::

  Initial LargestPossibleRegion: ImageRegion (0x7fff11257330)
  Dimension: 3
  Index: [0, 0, 0]
  Size: [256, 256, 3]


  Trying to call Update() after shrinking the LargestPossibleRegion...

  Error:
  itk::InvalidRequestedRegionError (0x28cd880)
  Location: "unknown"
  File: /home/matt/bin/ITKExamples-Clang-RelWithDebInfo/ITK/Modules/Core/Common/src/itkDataObject.cxx
  Line: 411
  Description: Requested region is (at least partially) outside the largest possible region.


  Trying to call UpdateLargestPossibleRegion() after shrinking the LargestPossibleRegion...

  Shrunk LargestPossibleRegion: ImageRegion (0x7fff11257330)
    Dimension: 3
    Index: [0, 0, 0]
    Size: [256, 256, 2]


Code
----

C++
...

.. literalinclude:: Code.cxx


Classes demonstrated
--------------------

.. breathelink:: itk::ProcessObject

.. breathelink:: itk::ImageSeriesReader
