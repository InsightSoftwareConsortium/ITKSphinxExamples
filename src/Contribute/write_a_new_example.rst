How to write a new example
==========================

In this section we describe how to write an example by walking through the
sections of an example's reStructuredText_ file.  The mechanics of submitting an
example via the :ref:`web interface <web-submission>` or :ref:`Git/Gerrit
directly <text-editor-submission>` are covered in other sections.


General guidelines
------------------

All lines should be wrapped to 80 characters or less.  This improves readability
in text editors.  It is generally ITK's policy to format code lines without
wrapping up to 200 characters, but the 80 character limit keeps code readable in
the PDF output.

Please remove all trailing whitespace.

Follow ITK conventions for coding; do not use TABs, and use two spacing for
indentation.

The characters used to define reStructuredText_ sections are as follows::

  Title
  =====

  Section
  -------

  Subsection
  ..........


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
be derived by placing the example in the question format; we call this the
Trebek Title Method.

For instance, an example that answers the question, *"How do I dilate a binary
image?"* would be called *Dilate a binary image*.  This determines the title in
the reStructuredText_ file::

  Dilate a binary image
  =====================

and it also determines the name of the directory, file, and test associated with
the example.  These names come from a CamelCase conversion of the title.  For
instance, in this case, the corresponding CamelCase title is
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

This section contains a short summary of the example.


Code
----

This section sources the relevant code for inclusion in the documentation with
syntax highlighting care of Pygments_.  The `literalinclude directive`_ performs
this function.  This ensures that all the code that is documented is also
tested.  Each program should be included in a subsection corresponding to its
language; one of *C++*, *Python*, or *Java*.  For instance::

  C++
  ...

  .. literalinclude:: DilateABinaryImage.cxx

Follow ITK style guidelines when writing code.  Keep the example as simple as
possible, and follow the best practices layed out in the rest of the examples.
Do basic argument checking and parsing.  Wrap *Update()* calls in a *try /
catch* for C++ code, etc.


Results
-------

Include images or text output here that results from the example.

If there was an input image, display it for reference.  The images displayed
here should be rendered in the PNG format for display either by directly outputing
to PNG format or by rendering with your favorite :ref:`visualization application
<visualize>` and saving a screenshot.  Display the image with the `figure
directive`_.  Provide alt text with the *:alt:* option and a brief descriptive
caption.  For instance::

  .. figure:: DilateABinaryImageOutputBaseline.png
    :scale: 50%
    :alt: Dilated output.

    Dilated output.

Text output should be placed in a `literal block`_ by inserting two colons
followed by indentation.  For instance::

  ::

    Registration done !
    Number of iterations = 27
    Translation along X  = 25.0966
    Translation along Y  = 22.3275
    Optimal metric value = 4597.96


Classes demonstrated
--------------------

At the end of the example, provide quick reference and a link to the doxygen
documentation for the important classes used in the example.  To do this, use
the `doxygenclass directive`_ provided by Breathe_ with the *:no-link:* option.
Also, provide a link to the full doxygen documentation with an `external
hyperlink target`_. Note that Doxygen URL's follow a predictable pattern.  For
instance::

  .. doxygenclass:: itk::BinaryDilateImageFilter
    :no-link:

  * `BinaryDilateImageFilter detailed doxygen documentation`_

  .. doxygenclass:: itk::BinaryBallStructuringElement
    :no-link:

  * `BinaryBallStructuringElement detailed doxygen documentation`_

  .. _BinaryDilateImageFilter detailed doxygen documentation:
    http://www.itk.org/Doxygen/html/classitk_1_1BinaryDilateImageFilter.html
  .. _BinaryBallStructuringElement detailed doxygen documentation:
    http://www.itk.org/Doxygen/html/classitk_1_1BinaryBallStructuringElement.html


.. _Breathe:                   https://github.com/michaeljones/breathe
.. _external hyperlink target: http://docutils.sourceforge.net/docs/user/rst/quickref.html#external-hyperlink-targets
.. _doxygenclass directive:    http://michaeljones.github.com/breathe/class.html
.. _figure directive:          http://docutils.sourceforge.net/docs/ref/rst/directives.html#figure
.. _literalinclude directive:  http://sphinx.pocoo.org/markup/code.html?highlight=literalinclude#directive-literalinclude
.. _literal block:             http://docutils.sourceforge.net/docs/user/rst/quickref.html#literal-blocks
.. _Pygments:                  http://pygments.org/
.. _Sphinx index directive:    http://sphinx.pocoo.org/markup/misc.html#directive-index
.. _reStructuredText:          http://docutils.sourceforge.net/rst.html
