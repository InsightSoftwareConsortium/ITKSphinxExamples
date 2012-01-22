How to write a new example
==========================

In this section we describe how to write an example by walking through the
sections of an example's reStructuredText_ file.  The mechanics of submitting
an example through the :ref:`web interface <web-submission>` or :ref:`Git/Gerrit
directly <text-editor-submission>` are covered in other sections.


General guidelines
------------------

All lines should be wrapped to 80 characters or less.  This improves readability
in text editors.  It is generally ITK's policy to format code lines without
wrapping up to 200 characters, but the 80 character limit keep code readable in
the PDF output.

Please remove all trailing whitespace.

The characters used to define reStructuredText_ sections are as follows::

  Title
  =====

  Subsection
  ----------

  Subsubsection
  .............


Directory placement
-------------------

The examples live inside the *src/Examples* directory of the repository.  They
are organized by the dominant class demonstrated in the example.  There
are two directories of organization which mirror the directory layout in ITKv4,
*Group* followed by *Module*.  Therefore, place the example in the directory
corresponding to the Module of one of the prominant classes used in the example.  

For instance, an examples that demonstrates the *BinaryDilateImageFilter* would
be placed in the *src/Examples/Filtering/BinaryMathematicalMorphology/*
directory.


Title
-----

The ITK Examples are intended to be a set of cookbook recipes that concisely
demonstrate how to achieve a single objective.  In general, they are intended to
provide an answer to the question, "How do I ...?"  The title for an example can
be derived by placing the example in the question format, i.e. Trebek format.

For instance, an example that answers, *"How do I dilate a binary image?"* would
be called *Dilate a binary image*.  This determines the title in the
reStructuredText_ file::

  Dilate a binary image
  =====================

and it also determines the name of the directory, file, and test
associated with the example.  These names are determined by CamelCase conversion
of the title.  For instance, in this case, the corresponding CamelCase title is
*DilateABinaryImage*.  All files for the examples are placed in a directory
called *DilateABinaryImage*, the C++ code is placed in *DilateABinaryImage.cxx*,
Python code in *DilateABinaryImage.py*, reStructuredText_ documentation in
*DilateABinaryImage.rst*, and the test will be named *DilateABinaryImageTest*.


Index entries
-------------

Index entries follow the title entry.  They are entered with the `Sphinx index
directive`_; see that documentation for more information on how to specify index
entries.  Important classes for the example or terms associated with the example
should be *single* entries.  Term index entries should be lower case to
distinguish them from classes or methods in the index.  Terms with sub-terms or
classes with important methods demonstrated should be used as *pair* entries.
Use *seealso* instead of *see* to add a *see also* entry.  For instance, with
our dilate a binary image example::

  .. index::
    single: BinaryBallStructuringElement
    single: BinaryDilateImageFilter
    pair: mathematical morphology; dilation
    pair: BinaryBallStructuringElement; SetRadius
    seealso: dilation; erosion

Synopsis
--------

Code 
----

.. _Sphinx index directive:  http://sphinx.pocoo.org/markup/misc.html#directive-index
.. _reStructuredText:        http://docutils.sourceforge.net/rst.html
