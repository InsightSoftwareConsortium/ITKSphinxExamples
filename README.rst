ITK Examples
============

.. image:: https://img.shields.io/badge/License-Apache%202.0-blue.svg?style=shield
   :target: https://github.com/InsightSoftwareConsortium/ITKExamples/blob/master/LICENSE

.. image:: https://dev.azure.com/InsightSoftwareConsortium/ITKExamples/_apis/build/status/InsightSoftwareConsortium.ITKExamples?branchName=master
   :target: https://dev.azure.com/InsightSoftwareConsortium/ITKExamples/_build/latest?definitionId=1

A set of cookbook examples for the Insight Toolkit, ITK_.

Download instructions
---------------------

Clone the repository using Git::

  $ git clone --recursive https://github.com/InsightSoftwareConsortium/ITKExamples.git


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
- GitHub community development.
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

- CMake_ ( >= 3.10.2 )
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

Run the bash script ``SetupForDevelopment.sh``::

  $ ./Utilities/SetupForDevelopment.sh

.. _Breathe: https://github.com/michaeljones/breathe
.. _build instructions in the documentation: https://itk.org/ITKExamples/Documentation/Build/index.html
.. _CMake: https://cmake.org/
.. _Git: http://git-scm.com/
.. _ITK: https://itk.org/
.. _Sphinx: http://sphinx.pocoo.org/
.. _Github Issues: https://github.com/InsightSoftwareConsortium/ITKExamples/issues
.. _Python: http://python.org/
.. _gnuplot: http://www.gnuplot.info/
.. _TeX Live: http://www.tug.org/texlive/
.. _MiKTeX: http://miktex.org/
.. _dvipng: http://sourceforge.net/projects/dvipng/
