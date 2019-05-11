{{ cookiecutter.example_title }}
================================

.. index::
   single: {{ cookiecutter.class_name }}

Synopsis
--------


{{ cookiecutter.example_synopsis }}


Results
-------

.. figure:: cthead1.png
  :scale: 50%
  :alt: Input image

  Input image

.. figure:: OutputBaseline.png
  :scale: 50%
  :alt: Output image

  Output image


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
   :lines: 1,18-


Classes demonstrated
--------------------

.. breathelink:: itk::{{ cookiecutter.class_name }}
