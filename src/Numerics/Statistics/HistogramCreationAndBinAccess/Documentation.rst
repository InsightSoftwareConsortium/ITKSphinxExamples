Histogram Creation And Bin Access
=================================

.. index::
   single: Histogram

Synopsis
--------

This example shows how to create a ``Histogram`` object and use it.

We call an instance in a ``Histogram`` object a *bin*.
The Histogram differs from the :itkdox:`itk::Statistics::ListSample`,
:itkdox:`itk::Statistics::ImageToListSampleAdaptor`, or
:itkdox:`itk::Statistics::PointSetToListSampleAdaptor` in significant
ways.  Histograms can have a variable number of values (``unsigned
long`` type) for each measurement vector, while the three other
classes have a fixed value (one) for all measurement vectors.  Also
those array-type containers can have multiple instances (data
elements) with identical measurement vector values. However, in a
Histogram object, there is one unique instance for any given
measurement vector.

Here we create a histogram with dense frequency containers.  In this
example we will not have any zero-frequency measurements, so the dense
frequency container is the appropriate choice.  If the histogram is
expected to have many empty (zero) bins, a sparse frequency container
would be the better option.  Note that this is not configurable in
Python.  Here we also set the size of the measurement vectors to be 2
components.

Output from the code below:

.. code-block:: none

   Frequency of the bin at index [0, 2] is 5 and the bin's instance identifier is 6


Code
----

C++
...

.. literalinclude:: Code.cxx
   :lines: 18-

Python
......

.. literalinclude:: Code.py
   :language: python
   :lines: 1, 18-


Classes demonstrated
--------------------

.. breathelink:: itk::Statistics::Histogram
