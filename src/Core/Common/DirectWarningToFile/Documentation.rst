Direct Warning To File
======================

.. index::
   single: FileOutputWindow
   single: warning

Synopsis
--------

Direct itk warnings to a file.


Results
-------

Output::

  Look in itkMessageLog.txt for the output

.. figure:: itkMessageLog.png
  :scale: 70%
  :alt: itkMessageLog.txt

  itkMessageLog.txt

Code
----

C++
...

.. literalinclude:: Code.cxx
   :lines: 18-

Classes demonstrated
--------------------

.. breathelink:: itk::FileOutputWindow
