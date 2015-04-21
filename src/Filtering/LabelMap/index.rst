LabelMap
========

.. toctree::
  :maxdepth: 1

  MaskOneImageGivenLabelMap/Documentation.rst
  RemoveHolesNotConnectedToImageBoundaries/Documentation.rst
  ExtractGivenLabelObject/Documentation.rst
  ApplyMorphologicalClosingOnAllLabelObjects/Documentation.rst
  ApplyMorphologicalClosingOnSpecificLabelObject/Documentation.rst

Note about this module:
-----------------------

This module contains the infrastructure to store the label images in an efficient and convenient way, including label images with overlapping objects.
All the objects contained in the LabelMap can be associated to values called attributes.
Some filters are available to compute the usual attributes values related to the shape of the objects or the pixels values in the objects and to manipulate the objects based on these values.


Implementations were taken from the `Insight Journal paper`_ or  here_.

.. _here: http://hdl.handle.net/1926/584
.. _Insight Journal paper: http://www.insight-journal.org/browse/publication/176
