:name: PerformRegistrationOnVectorImages

Perform Registration on Vector Images
=====================================

.. index::
   single: VectorImageToImageMetricTraitsv4

Synopsis
--------

Register images that have multi-component pixels like an itk::VectorImage or
an itk::Image< itk::Vector, Dimension >.


Results
-------

.. |fixedImage| image:: orange.jpg
  :scale: 50%
  :alt: Fixed image.

.. |movingImage| image:: apple.jpg
  :scale: 50%
  :alt: Moving image.

.. |resampledMovingImage| image:: OutputBaseline.jpg
  :scale: 50%
  :alt: Resampled moving image.

.. |fixedImageCaption| replace:: Fixed image.

.. |movingImageCaption| replace:: Moving image.

.. |resampledMovingImageCaption| replace:: Resampled, registered moving image.

+---------------------+----------------------+-------------------------------+
|     |fixedImage|    |     |movingImage|    |      |resampledMovingImage|   |
+                     +                      +                               +
| |fixedImageCaption| | |movingImageCaption| | |resampledMovingImageCaption| |
+---------------------+----------------------+-------------------------------+

Code
----

C++
...

.. literalinclude:: Code.cxx
   :lines: 18-



Classes demonstrated
--------------------

.. breathelink:: itk::VectorImageToImageMetricTraitsv4
