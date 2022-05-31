How to write a new example
==========================

In this section we describe how to write an example by walking through the
sections of an example's reStructuredText_ file.  The mechanics of submitting an
example via Git are :ref:`covered in other sections <text-editor-submission>`.


General guidelines
------------------

All lines should be wrapped to 80 characters or less.  This improves readability
in text editors.  It is generally ITK's policy to format code lines without
wrapping up to 200 characters, but the 80 character limit keeps code readable in
the PDF output.

Please remove all trailing whitespace.  Use two newlines between section
headings.

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

The examples live inside the *src* directory of the repository.  They
are organized by the dominant class demonstrated in the example.  There
are two directories of organization which mirror the directory layout in ITKv4,
*Group* followed by *Module*.  Therefore, place the example in the directory
corresponding to the Module of one of the prominant classes used in the example.

For instance, an examples that demonstrates the *BinaryDilateImageFilter* would
be placed in the *src/Filtering/BinaryMathematicalMorphology/*
directory.

Note that when adding new examples, both *CMakeLists.txt* and *index.rst* files
for the tree should be updated (to enforce the examples to be compiled, tested
and to appear in the sphinx documentation). For this reason, we recommend to
use the provided python script *CreateNewExample.py* see :ref:`CreateNewExample`

Title
-----

The ITK Sphinx Examples are intended to be a set of cookbook recipes that concisely
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

  .. seealso:: dilation; erosion


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

Images
......

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

Text
....

Text output should be placed in a `literal block`_ by inserting two colons
followed by indentation.  For instance::

  ::

    Registration done !
    Number of iterations = 27
    Translation along X  = 25.0966
    Translation along Y  = 22.3275
    Optimal metric value = 4597.96

PolyData
........

For data structures rendered as a PolyData, such as meshes, a screenshot of the
input and output rendering is insightful and motivating.  The screenshot can
be rendered with your favorite visualization, then included like the image
renderings per above.

As a supplement to the renderings, an interactive 3D WebGL can be included in
HTML output.  This can be produced with the `--webgl` flag to the VTK_ Python
script in the repository at `Utilities/Visualization/VTKPolyData.py`.  In
recent releases of Paraview_, it can be produced by clicking *File*, *Export
Scene*, *WEBGL files*.  In the reStructuredText file, add::

   .. raw:: html

     <div class="figure">
       <iframe src="InputMesh.html" width="200" height="225" seamless></iframe>
       <p class="caption">Interactive input mesh</p>
     </div>

Classes demonstrated
--------------------

At the end of the example, provide quick reference and a link to the doxygen
documentation for the important classes or structs used in the example.  To do this, use
the ``breathelink`` directive for C++ classes or ``breathelinkstruct`` directive for C++ structs, as follows::

  .. breathelink:: itk::BinaryDilateImageFilter
  .. breathelinkstruct:: itk::Index

Note that ``breathelink`` and ``breathelinkstruct`` are custom directives which make the use of:

- the `doxygenclass directive`_ or `doxygenstruct directive`_ provided by Breathe_ with the *:no-link:*
  option.
- the `doxylink`_ directive which provides a link to the full doxygen
  documentation with an `external hyperlink target`_. Note that Doxygen URL's
  follow a predictable pattern.

.. _Breathe:                   https://github.com/michaeljones/breathe
.. _external hyperlink target: http://docutils.sourceforge.net/docs/user/rst/quickref.html#external-hyperlink-targets
.. _doxygenclass directive:    https://breathe.readthedocs.io/en/latest/class.html
.. _doxygenstruct directive:   https://breathe.readthedocs.io/en/latest/struct.html
.. _figure directive:          http://docutils.sourceforge.net/docs/ref/rst/directives.html#figure
.. _literalinclude directive:  https://www.sphinx-doc.org/en/master/usage/restructuredtext/directives.html#directive-literalinclude
.. _literal block:             http://docutils.sourceforge.net/docs/user/rst/quickref.html#literal-blocks
.. _Pygments:                  https://pygments.org/
.. _Sphinx index directive:    https://www.sphinx-doc.org/en/master/usage/restructuredtext/directives.html#index-generating-markup
.. _reStructuredText:          http://docutils.sourceforge.net/rst.html
.. _doxylink:                  https://pythonhosted.org/sphinxcontrib-doxylink/
.. _VTK:                       https://vtk.org
.. _Paraview:                  https://www.paraview.org
