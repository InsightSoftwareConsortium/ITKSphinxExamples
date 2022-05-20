:name: ConvertNumPyArrayToitkImage

Interface ITK with NumPy Array
=============================

.. index::
   single: Image
   single: instantiate

Synopsis
--------

This example illustrates interfacing ITK Image data with NumPy array. While doing this, there are two key issues to
to keep in mind. One, the order of indexes is different between ITK image data class and NumPy array.
Second, there are two ways to access ITK image data as a NumPy array. i) Get direct access to memory with the data called
"View" functions (array_view_from_image and image_view_from_array), or ii) Copy the data (array_from_image and image_from_array).
If the view functions are used, the data can't be modified.

Results
-------

NA


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
