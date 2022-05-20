:name: ConvertNumPyArrayToitkImage

Interface ITK with NumPy Array
===============================

.. index::
   single: Image

Synopsis
--------

This example illustrates interfacing ITK Image data with NumPy array.
While doing this, there are two key issues to keep in mind. One, the order of
indexes is different between ITK image data class and NumPy array.
Second, there are two ways to access ITK image data as a NumPy array.
i) Get direct access to memory with the data called"View" functions, or
ii) Copy the data using array_from_image function. If the view functions are used,
the data can't be modified.

Results
-------
The size of the ITK image data read from the input file  = itkSize2 ([221, 257])

The size of the NumPy array viewed from itk::Image = (257, 221)
The size of the NumPy array copied from itk::Image = (257, 221)
ITK image data size after convesion from NumPy = itkSize2 ([221, 257])

ITK image data pixel value at [2,1] = 6
NumPy array pixel value at [2,1] = 8


Code
----

Python
......

.. literalinclude:: Code.py
   :language: python
   :lines: 1, 16-



Classes demonstrated
--------------------

.. breathelink:: itk::Image
