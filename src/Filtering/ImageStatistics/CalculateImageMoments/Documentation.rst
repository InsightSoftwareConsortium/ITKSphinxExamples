Calculate Image Moments
================================

.. index::
   single: ImageMomentsCalculator

Synopsis
--------


Calculate image moments from binary images and an interactive ellipse.


Results
-------

.. figure:: ellipse.mha
  :scale: 50%
  :alt: Input image

  Input Image
::
Output
 ImageMomentsCalculator (000002037138BE90)
   RTTI typeinfo:   class itk::ImageMomentsCalculator<class itk::Image<unsigned short,2> >
   Reference Count: 1
   Modified Time: 249
   Debug: Off
   Object Name:
   Observers:
     none
   Image: 000002037138FDD0
   Valid: 1
   Zeroth Moment about origin: 153
   First Moment about origin: [30, 50]
   Second Moment about origin: 15.0458 -8.8366
 -8.8366 15.0458

   Center of Gravity: [30, 50]
   Second central moments: 15.0458 -8.8366
 -8.8366 15.0458

   Principal Moments: [950, 3654]
   Principal axes: 0.707107 0.707107
 -0.707107 0.707107
::


Jupyter Notebook
-----------------

.. image:: https://mybinder.org/badge_logo.svg
   :target: https://mybinder.org/v2/gh/InsightSoftwareConsortium/ITKExamples/master?filepath=src%2FFiltering%2FImageStatistics%2FImageMomentsCalculator%2FCalculateEllipseMoments.ipynb

Code
----

C++
...

.. literalinclude:: Code.cxx
   :language: c++
   :lines: 18-

Python
......

.. literalinclude:: Code.py
   :language: python
   :lines: 1,16-


Classes demonstrated
--------------------

.. breathelink:: itk::ImageMomentsCalculator
