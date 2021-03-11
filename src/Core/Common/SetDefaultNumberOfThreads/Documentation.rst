Set the Default Number of Threads
=================================

.. index::
   single: MultiThreaderBase

Synopsis
--------

Set the default number of threads for multi-threading.

The default number of threads can also be set via the environment variable,
`ITK_GLOBAL_DEFAULT_NUMBER_OF_THREADS`.


Results
-------

.. code-block:: none

  Filter's default number of threads: 3



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

.. breathelink:: itk::MultiThreaderBase
