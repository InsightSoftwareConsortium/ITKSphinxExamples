ITK Examples
============

A set of cookbook examples for the Insight Toolkit, ITK_.

Download instructions
---------------------

  $ git clone https://itk.org/ITKExamples.git


Build instructions
------------------

See the `build instructions in the documentation`_.

Features
--------

Implemented
^^^^^^^^^^^

- Stored and editable in Git_ version control.
- HTML / PDF / EPUB output.
- CTest unit testing.
- CMake ExternalData for binary data storage.
- Individual examples can be downloaded independently, and easily built/executed/hacked.
- Download the entire docs for offline viewing.
- Inline Doxygen class descriptions and links to Doxygen class documentation.
- Nightly generated Gitstats for contributors.
- Software quality dashboard.
- Index of examples that apply to given terms and classes.
- Quick search.
- Script to create a new examples from a template.
- Gerrit Code Review.
- Selectable light/dark colorscheme.

Todo
^^^^

- Anonymous online editing.
- Editable online with CodeMirror.

- See `Github Issues`_ for a complete list of actions to be performed, bugs, *etc.*

Build dependencies
------------------

Required
^^^^^^^^

- CMake_ ( >= 2.8.5 )
- ITK_  ( >= 4.0.0 )

Optional
^^^^^^^^

If building the documentation:

- Python_ ( >= 2.7 )
- Sphinx_
- gnuplot_
- dvipng_ ( for rendered equations )

PDF generation requires a TeX distribution like `TeX Live`_ or MiKTeX_.

Development setup
------------------

Run the bash scipt SetupForDevelopment.sh::

  $ ./Utilities/SetupForDevelopment.sh

.. _Breathe: https://github.com/michaeljones/breathe
.. _build instructions in the documentation: http://itk.org/ITKExamples/Documentation/Build/index.html
.. _CMake: http://cmake.org/
.. _Gerrit: http://code.google.com/p/gerrit/
.. _Git: http://git-scm.com/
.. _ITK: http://itk.org/
.. _Sphinx: http://sphinx.pocoo.org/
.. _Github Issues: https://itk.org/ITKExamples/issues?milestone=&labels=&state=open
.. _Python: http://python.org/
.. _gnuplot: http://www.gnuplot.info/
.. _TeX Live: http://www.tug.org/texlive/
.. _MiKTeX: http://miktex.org/
.. _dvipng: http://sourceforge.net/projects/dvipng/
