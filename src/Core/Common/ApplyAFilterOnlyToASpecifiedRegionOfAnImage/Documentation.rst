:name: ApplyAFilterOnlyToASpecifiedRegionOfAnImage

Apply a Filter Only to a Specified Region of an Image
=====================================================

.. index::
   single: Image
   pair: Image; SetRequestedRegion

Synopsis
--------


The key of using SetRequestedRegion to tell a filter to only operate on a specified ImageRegion is to call SetRequestedRegion on the filters GetOutput().
That is, to tell the DerivativeImageFilter to only operate on a small region, you must do ::

  derivativeFilter->GetOutput()->SetRequestedRegion(smallRegion);
  derivativeFilter->Update();

.. figure:: FilterImageRegion.png
  :scale: 70%
  :alt: FilterImageRegion.png


Results
-------

.. figure:: Relationship.png
  :scale: 70%
  :alt: relationship.png


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

.. breathelink:: itk::Image
