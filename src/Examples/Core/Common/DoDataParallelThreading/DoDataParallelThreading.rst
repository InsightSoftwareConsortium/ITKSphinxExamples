Do data parallel threading
==========================

.. index::
  single: DomainThreader
  single: ThreadedIndexedContainerPartitioner

Synopsis
--------

In this example, we show how to do an operation on data across multiple threads to take advantage of multi-core processors.

In this example we have an `enum` of central nervous system cell types, a
`std::vector< CELL_TYPE >` that contains the cells that we have encountered, and
we want to count how many we have of each `CELL_TYPE`.

Results
-------

Output::

  Result of the multi-threaded cell count:
        NEURON:          3
        ASTROCYTE:       5
        OLIGODENDROCYTE: 2
  Result of the single-threaded cell count:
        NEURON:          3
        ASTROCYTE:       5
        OLIGODENDROCYTE: 2


Code
----

C++
...

.. literalinclude:: DoDataParallelThreading.cxx

Classes demonstrated
--------------------

.. doxygenclass:: itk::DomainThreader
  :no-link:

* :itkdox:`itk::DomainThreader`
